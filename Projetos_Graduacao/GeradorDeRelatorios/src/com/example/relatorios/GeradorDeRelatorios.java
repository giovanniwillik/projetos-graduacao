package src.com.example.relatorios;

import src.com.example.relatorios.model.Produto;
import src.com.example.relatorios.strategy.sorting.AlgoritmoOrdenacao;
import src.com.example.relatorios.strategy.filtering.CriterioFiltragem;

import java.io.PrintWriter;
import java.io.IOException;
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
                               CriterioFiltragem criterioFiltragem) {
        this.produtos = new ArrayList<>(produtos);
        this.algoritmoOrdenacao = algoritmoOrdenacao;
        this.criterioOrdenacao = criterioOrdenacao;
        this.criterioFiltragem = criterioFiltragem;
    }

    public void debug() {
        System.out.println("Gerando relatório para lista contendo " + produtos.size() + " produto(s)");
    }


    // Gera um relatório HTML com os produtos filtrados e ordenados.
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

        for(Produto p : produtos) {
            if(criterioFiltragem.selecionar(p)) {
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

    public static void main(String[] args) {
        // Processar argumentos da linha de comando
        String[] opcoes = RelatorioCLI.processarArgumentos(args);
        String opcao_algoritmo = opcoes[0];
        String opcao_criterio_ord = opcoes[1];
        String opcao_criterio_filtro = opcoes[2];
        String opcao_parametro_filtro = opcoes[3];
        String nomeArquivoCSV = opcoes[4];

        // Criar componentes necessários
        AlgoritmoOrdenacao algoritmoOrdenacao = RelatorioCLI.criarAlgoritmoOrdenacao(opcao_algoritmo);
        Comparator<Produto> criterioOrdenacao = RelatorioCLI.criarCriterioOrdenacao(opcao_criterio_ord);
        CriterioFiltragem criterioFiltragem = RelatorioCLI.criarCriterioFiltragem(opcao_criterio_filtro, opcao_parametro_filtro);

        // Carregar produtos do CSV
        List<Produto> produtos = null;
        try {
            produtos = LeitorCSV.carregaProdutosDoCSV(nomeArquivoCSV);
        } catch (IOException e) {
            System.err.println("Erro ao carregar produtos do arquivo CSV: " + nomeArquivoCSV + ". Verifique o caminho e permissões. Detalhe: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }

        // Criar e executar o gerador de relatórios
        GeradorDeRelatorios gdr = new GeradorDeRelatorios(
                                        produtos,
                                        algoritmoOrdenacao,
                                        criterioOrdenacao,
                                        criterioFiltragem
                                    );

        try {
            gdr.geraRelatorio("saida.html");
            System.out.println("Relatório gerado com sucesso em saida.html");
        } catch(IOException e) {
            System.err.println("Erro ao gerar o relatório: " + e.getMessage());
            e.printStackTrace();
        }
    }
}