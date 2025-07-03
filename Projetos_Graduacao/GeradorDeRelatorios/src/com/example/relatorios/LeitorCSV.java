package src.com.example.relatorios;

import src.com.example.relatorios.model.Produto;
import src.com.example.relatorios.model.ProdutoPadrao;
import src.com.example.relatorios.decorator.ProdutoCorDecorator;
import src.com.example.relatorios.decorator.ProdutoItalicoDecorator;
import src.com.example.relatorios.decorator.ProdutoNegritoDecorator;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class LeitorCSV {
    
    // Carrega produtos de um arquivo CSV.
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
}