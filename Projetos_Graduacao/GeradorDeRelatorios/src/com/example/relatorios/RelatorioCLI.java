package src.com.example.relatorios;

import src.com.example.relatorios.model.Produto;
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

import java.util.Comparator;
import java.util.Scanner;

public class RelatorioCLI {

    // Exibe instruções de uso do programa.
    public static void exibirAjuda() {
        System.out.println("Uso passando args:");
        System.out.println("\tjava " + GeradorDeRelatorios.class.getName() + " ALG=<algoritmo> CRITERIO_ORD=<critério de ordenação> CRITERIO_FILTRO=<critério de filtragem> PARAMETRO_FILTRO=<parâmetro de filtragem> NOME_ARQUIVO=<nome do arquivo CSV>");
        System.out.println("Onde:");
        System.out.println("\talgoritmo: 'quick' ou 'insertion'");
        System.out.println("\tcriterio de ordenação: 'descricao_c', 'descricao_d', 'preco_c', 'preco_d', 'estoque_c' ou 'estoque_d'");
        System.out.println("\tcriterio de filtragem: 'todos', 'estoque_menor_igual', 'categoria_igual', 'preco_intervalo' ou 'descricao_contem'");
        System.out.println("\tparâmetro de filtragem: argumentos adicionais necessários para a filtragem (use '' para 'todos', 'quantidade' para estoque, 'categoria' para categoria, 'min-max' para preço, 'substring' para descrição)");
        System.out.println("\tnome do arquivo CSV: caminho para o arquivo de dados de produtos (ex: produtos.csv)");
        System.out.println("Valores padrões: ");
        System.out.println("\tALG: quick");
        System.out.println("\tCRITERIO_ORD: descricao_c");
        System.out.println("\tCRITERIO_FILTRO: todos");
        System.out.println("\tPARAMETRO_FILTRO: ");
        System.out.println("\tNOME_ARQUIVO: data/produtos.csv");
        System.out.println();
    }


    // Processa os argumentos da linha de comando ou solicita entrada interativa.
    public static String[] processarArgumentos(String[] args) {
        String opcao_algoritmo;
        String opcao_criterio_ord;
        String opcao_criterio_filtro;
        String opcao_parametro_filtro;
        String nomeArquivoCSV = "data/produtos.csv"; // Padrão

        // Verifica se os argumentos foram passados corretamente
        if (args.length < 5) {
            System.out.println("Parâmetros insuficientes. Vamos obter as informações interativamente.");
            Scanner scanner = new Scanner(System.in);
            
            // Obter algoritmo
            System.out.print("Qual algoritmo de ordenação? (quick ou insertion): ");
            opcao_algoritmo = scanner.nextLine().trim();
            
            // Obter critério de ordenação
            System.out.print("Qual critério de ordenação? (descricao_c, descricao_d, preco_c, preco_d, estoque_c ou estoque_d): ");
            opcao_criterio_ord = scanner.nextLine().trim();
            
            // Obter critério de filtragem
            System.out.print("Qual critério de filtragem? (todos, estoque_menor_igual, categoria_igual, preco_intervalo ou descricao_contem): ");
            opcao_criterio_filtro = scanner.nextLine().trim();
            
            // Obter parâmetro de filtragem
            System.out.print("Qual o parâmetro de filtragem? (use '' para 'todos', quantidade para 'estoque', categoria para 'categoria', min-max para 'preço', substring para 'descrição'): ");
            opcao_parametro_filtro = scanner.nextLine().trim();
            
            scanner.close();
        } else {
            // Se tiver argumentos suficientes, use-os diretamente
            opcao_algoritmo = args[0];
            opcao_criterio_ord = args[1];
            opcao_criterio_filtro = args[2];
            opcao_parametro_filtro = args[3];
            nomeArquivoCSV = args[4];
        }
        
        // Validação básica dos argumentos
        boolean algoritmoValido = opcao_algoritmo.equals("quick") || opcao_algoritmo.equals("insertion");
        boolean criterioOrdValido = opcao_criterio_ord.matches("(descricao|preco|estoque)_(c|d)");
        boolean criterioFiltroValido = opcao_criterio_filtro.equals("todos") || 
                                      opcao_criterio_filtro.equals("estoque_menor_igual") ||
                                      opcao_criterio_filtro.equals("categoria_igual") ||
                                      opcao_criterio_filtro.equals("preco_intervalo") ||
                                      opcao_criterio_filtro.equals("descricao_contem");
        
        if (!algoritmoValido || !criterioOrdValido || !criterioFiltroValido) {
            System.out.println("Um ou mais parâmetros inválidos foram fornecidos.");
            exibirAjuda();
            System.exit(1);
        }
        
        // Continuar com a execução normal do programa usando os argumentos obtidos
        System.out.println("\nExecutando com os seguintes parâmetros:");
        System.out.println("Algoritmo: " + opcao_algoritmo);
        System.out.println("Critério de ordenação: " + opcao_criterio_ord);
        System.out.println("Critério de filtragem: " + opcao_criterio_filtro);
        System.out.println("Parâmetro de filtragem: " + opcao_parametro_filtro);
        System.out.println("Arquivo CSV: " + nomeArquivoCSV);
        
        return new String[] {opcao_algoritmo, opcao_criterio_ord, opcao_criterio_filtro, opcao_parametro_filtro, nomeArquivoCSV};
    }
    

    // Cria o algoritmo de ordenação com base na opção selecionada.
    public static AlgoritmoOrdenacao criarAlgoritmoOrdenacao(String opcao_algoritmo) {
        if ("quick".equalsIgnoreCase(opcao_algoritmo)) {
            return new QuickSort();
        } else if ("insertion".equalsIgnoreCase(opcao_algoritmo)) {
            return new InsertionSort();
        } else {
            System.err.println("Erro: Algoritmo de ordenação inválido: " + opcao_algoritmo);
            System.exit(1);
            return null;
        }
    }
    
    // Cria o critério de ordenação com base na opção selecionada.
    public static Comparator<Produto> criarCriterioOrdenacao(String opcao_criterio_ord) {
        switch (opcao_criterio_ord.toLowerCase()) {
            case "descricao_c":
                return new CriterioDescricaoCrescente();
            case "descricao_d":
                return new CriterioDescricaoDecrescente();
            case "preco_c":
                return new CriterioPrecoCrescente();
            case "preco_d":
                return new CriterioPrecoDecrescente();
            case "estoque_c":
                return new CriterioEstoqueCrescente();
            case "estoque_d":
                return new CriterioEstoqueDecrescente();
            default:
                System.err.println("Erro: Critério de ordenação inválido: " + opcao_criterio_ord);
                System.exit(1);
                return null;
        }
    }
    
    // Cria o critério de filtragem com base nas opções selecionadas.
    public static CriterioFiltragem criarCriterioFiltragem(String opcao_criterio_filtro, String opcao_parametro_filtro) {
        switch (opcao_criterio_filtro.toLowerCase()) {
            case "todos":
                return new FiltroTodos();
            case "estoque_menor_igual":
                try {
                    int quantidade = Integer.parseInt(opcao_parametro_filtro);
                    return new FiltroEstoqueMenorIgual(quantidade);
                } catch (NumberFormatException e) {
                    System.err.println("Erro: Parâmetro de filtro 'estoque_menor_igual' inválido. Esperado um número inteiro. Detalhe: " + e.getMessage());
                    System.exit(1);
                }
                break;
            case "categoria_igual":
                return new FiltroCategoriaIgual(opcao_parametro_filtro);
            case "preco_intervalo":
                try {
                    String[] precos = opcao_parametro_filtro.split("-");
                    if (precos.length != 2) {
                        throw new IllegalArgumentException("Formato inválido. Use 'min-max'.");
                    }
                    double precoMin = Double.parseDouble(precos[0]);
                    double precoMax = Double.parseDouble(precos[1]);
                    return new FiltroPrecoIntervalo(precoMin, precoMax);
                } catch (Exception e) {
                    System.err.println("Erro: Parâmetro de filtro 'preco_intervalo' inválido. Esperado 'min-max' numérico. Ex: 100.0-200.0. Detalhe: " + e.getMessage());
                    System.exit(1);
                }
                break;
            case "descricao_contem":
                return new FiltroDescricaoContem(opcao_parametro_filtro);
            default:
                System.err.println("Erro: Critério de filtragem inválido: " + opcao_criterio_filtro);
                System.exit(1);
        }
        return null; // Nunca deve chegar aqui
    }
}