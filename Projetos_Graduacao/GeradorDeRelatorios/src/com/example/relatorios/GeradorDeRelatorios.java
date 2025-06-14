package src.com.example.relatorios;

import src.com.example.relatorios.model.Produto;
import src.com.example.relatorios.model.ProdutoPadrao;
import src.com.example.relatorios.strategy.sorting.AlgoritmoOrdenacao;
import src.com.example.relatorios.strategy.sorting.QuickSort;
import src.com.example.relatorios.strategy.sorting.InsertionSort;
import src.com.example.relatorios.strategy.sorting.CriterioDescricaoCrescente;
import src.com.example.relatorios.strategy.sorting.CriterioDescricaoDecrescente;
import src.com.example.relatorios.strategy.sorting.CriterioPrecoCrescente;
import src.com.example.relatorios.strategy.sorting.CriterioPrecoDecrescente;
import src.com.example.relatorios.strategy.sorting.CriterioEstoqueCrescente;
import src.com.example.relatorios.strategy.sorting.CriterioEstoqueDecrescente;
import src.com.example.relatorios.strategy.filtering.CriterioFiltragem;
import src.com.example.relatorios.strategy.filtering.FiltroTodos;
import src.com.example.relatorios.strategy.filtering.FiltroEstoqueMenorIgual;
import src.com.example.relatorios.strategy.filtering.FiltroCategoriaIgual;
import src.com.example.relatorios.strategy.filtering.FiltroPrecoIntervalo;
import src.com.example.relatorios.strategy.filtering.FiltroDescricaoContem;
import src.com.example.relatorios.decorator.ProdutoCorDecorator;
import src.com.example.relatorios.decorator.ProdutoItalicoDecorator;
import src.com.example.relatorios.decorator.ProdutoNegritoDecorator;


import java.io.PrintWriter;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class GeradorDeRelatorios {

    private List<Produto> produtos;
    private AlgoritmoOrdenacao algoritmoOrdenacao;
    private Comparator<Produto> criterioOrdenacao;
    private CriterioFiltragem criterioFiltragem;

    public GeradorDeRelatorios(List<Produto> produtos,
                               AlgoritmoOrdenacao algoritmoOrdenacao,
                               Comparator<Produto> criterioOrdenacao,
                               CriterioFiltragem criterioFiltragem){

        this.produtos = new ArrayList<>(produtos);
        this.algoritmoOrdenacao = algoritmoOrdenacao;
        this.criterioOrdenacao = criterioOrdenacao;
        this.criterioFiltragem = criterioFiltragem;
    }

    public void debug(){
        System.out.println("Gerando relatório para lista contendo " + produtos.size() + " produto(s)");
    }

    public void geraRelatorio(String arquivoSaida) throws IOException {
        debug();

        algoritmoOrdenacao.ordenar(produtos, criterioOrdenacao);

        PrintWriter out = new PrintWriter(arquivoSaida);

        out.println("<!DOCTYPE html><html>");
        out.println("<head><title>Relatorio de produtos</title><meta charset=\"UTF-8\"></head>");
        out.println("<body>");
        out.println("<h1>Relatório de Produtos</h1>");
        out.println("<ul>");

        int count = 0;

        for(Produto p : produtos){
            if(criterioFiltragem.selecionar(p)){
                out.print("<li>");
                out.print(p.formataParaImpressao());
                out.println("</li>");
                count++;
            }
        }

        out.println("</ul>");
        out.println("<p>" + count + " produtos listados, de um total de " + produtos.size() + ".</p>");
        out.println("</body>");
        out.println("</html>");

        out.close();
    }

    public static List<Produto> carregaProdutosDoCSV(String nomeArquivo) throws IOException {
        List<Produto> produtos = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(nomeArquivo))) {
            String line;
            br.readLine(); // Ignorar o cabeçalho do CSV

            while ((line = br.readLine()) != null) {
                String[] data = line.split(",");
                if (data.length != 8) {
                    System.err.println("Linha mal formatada no CSV (número de colunas inválido): " + line);
                    continue;
                }

                try {
                    int id = Integer.parseInt(data[0].trim());
                    String descricao = data[1].trim();
                    String categoria = data[2].trim();
                    int qtdEstoque = Integer.parseInt(data[3].trim());
                    double preco = Double.parseDouble(data[4].trim());
                    boolean negrito = Boolean.parseBoolean(data[5].trim());
                    boolean italico = Boolean.parseBoolean(data[6].trim());
                    String cor = data[7].trim();

                    Produto produtoBase = new ProdutoPadrao(id, descricao, categoria, qtdEstoque, preco);
                    Produto produtoFinal = produtoBase; 

                    if (!cor.isEmpty() && !cor.equalsIgnoreCase("null")) {
                        produtoFinal = new ProdutoCorDecorator(produtoFinal, cor);
                    }
                    if (italico) {
                        produtoFinal = new ProdutoItalicoDecorator(produtoFinal);
                    }
                    if (negrito) {
                        produtoFinal = new ProdutoNegritoDecorator(produtoFinal);
                    }

                    produtos.add(produtoFinal);

                } catch (NumberFormatException e) {
                    System.err.println("Erro de formato numérico ou booleano na linha: '" + line + "' - " + e.getMessage());
                }
            }
        }
        return produtos;
    }

    public static void main(String [] args) {
        if(args.length < 5){
            System.out.println("Uso:");
            System.out.println("\tjava " + GeradorDeRelatorios.class.getName() + " <algoritmo> <critério de ordenação> <critério de filtragem> <parâmetro de filtragem> <nome do arquivo CSV>");
            System.out.println("Onde:");
            System.out.println("\talgoritmo: 'quick' ou 'insertion'");
            System.out.println("\tcriterio de ordenação: 'descricao_c', 'descricao_d', 'preco_c', 'preco_d', 'estoque_c' ou 'estoque_d'");
            System.out.println("\tcriterio de filtragem: 'todos', 'estoque_menor_igual', 'categoria_igual', 'preco_intervalo' ou 'descricao_contem'");
            System.out.println("\tparâmetro de filtragem: argumentos adicionais necessários para a filtragem (use '' para 'todos', 'quantidade' para estoque, 'categoria' para categoria, 'min-max' para preço, 'substring' para descrição)");
            System.out.println("\tnome do arquivo CSV: caminho para o arquivo de dados de produtos (ex: produtos.csv)");
            System.out.println();
            System.exit(1);
        }

        String opcao_algoritmo = args[0];
        String opcao_criterio_ord = args[1];
        String opcao_criterio_filtro = args[2];
        String opcao_parametro_filtro = args[3];
        String nomeArquivoCSV = args[4];

        AlgoritmoOrdenacao algoritmoOrdenacao = null;
        if ("quick".equalsIgnoreCase(opcao_algoritmo)) {
            algoritmoOrdenacao = new QuickSort();
        } else if ("insertion".equalsIgnoreCase(opcao_algoritmo)) {
            algoritmoOrdenacao = new InsertionSort();
        } else {
            System.err.println("Erro: Algoritmo de ordenação inválido: " + opcao_algoritmo);
            System.exit(1);
        }

        Comparator<Produto> criterioOrdenacao = null;
        switch (opcao_criterio_ord.toLowerCase()) {
            case "descricao_c":
                criterioOrdenacao = new CriterioDescricaoCrescente();
                break;
            case "descricao_d":
                criterioOrdenacao = new CriterioDescricaoDecrescente();
                break;
            case "preco_c":
                criterioOrdenacao = new CriterioPrecoCrescente();
                break;
            case "preco_d":
                criterioOrdenacao = new CriterioPrecoDecrescente();
                break;
            case "estoque_c":
                criterioOrdenacao = new CriterioEstoqueCrescente();
                break;
            case "estoque_d":
                criterioOrdenacao = new CriterioEstoqueDecrescente();
                break;
            default:
                System.err.println("Erro: Critério de ordenação inválido: " + opcao_criterio_ord);
                System.exit(1);
        }

        CriterioFiltragem criterioFiltragem = null;
        switch (opcao_criterio_filtro.toLowerCase()) {
            case "todos":
                criterioFiltragem = new FiltroTodos();
                break;
            case "estoque_menor_igual":
                try {
                    int quantidade = Integer.parseInt(opcao_parametro_filtro);
                    criterioFiltragem = new FiltroEstoqueMenorIgual(quantidade);
                } catch (NumberFormatException e) {
                    System.err.println("Erro: Parâmetro de filtro 'estoque_menor_igual' inválido. Esperado um número inteiro. Detalhe: " + e.getMessage());
                    System.exit(1);
                }
                break;
            case "categoria_igual":
                criterioFiltragem = new FiltroCategoriaIgual(opcao_parametro_filtro);
                break;
            case "preco_intervalo":
                try {
                    String[] precos = opcao_parametro_filtro.split("-");
                    if (precos.length != 2) {
                        throw new IllegalArgumentException("Formato inválido. Use 'min-max'.");
                    }
                    double precoMin = Double.parseDouble(precos[0]);
                    double precoMax = Double.parseDouble(precos[1]);
                    criterioFiltragem = new FiltroPrecoIntervalo(precoMin, precoMax);
                } catch (Exception e) {
                    System.err.println("Erro: Parâmetro de filtro 'preco_intervalo' inválido. Esperado 'min-max' numérico. Ex: 100.0-200.0. Detalhe: " + e.getMessage());
                    System.exit(1);
                }
                break;
            case "descricao_contem":
                criterioFiltragem = new FiltroDescricaoContem(opcao_parametro_filtro);
                break;
            default:
                System.err.println("Erro: Critério de filtragem inválido: " + opcao_criterio_filtro);
                System.exit(1);
        }

        List<Produto> produtos = null;
        try {
            produtos = carregaProdutosDoCSV(nomeArquivoCSV);
        } catch (IOException e) {
            System.err.println("Erro ao carregar produtos do arquivo CSV: " + nomeArquivoCSV + ". Verifique o caminho e permissões. Detalhe: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }

        GeradorDeRelatorios gdr = new GeradorDeRelatorios(
                                        produtos,
                                        algoritmoOrdenacao,
                                        criterioOrdenacao,
                                        criterioFiltragem
                                    );

        try{
            gdr.geraRelatorio("saida.html");
            System.out.println("Relatório gerado com sucesso em saida.html");
        }
        catch(IOException e){
            System.err.println("Erro ao gerar o relatório: " + e.getMessage());
            e.printStackTrace();
        }
    }
}