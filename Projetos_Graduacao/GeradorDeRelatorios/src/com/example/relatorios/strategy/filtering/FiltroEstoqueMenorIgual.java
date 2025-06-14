package src.com.example.relatorios.strategy.filtering;

import src.com.example.relatorios.model.Produto;

public class FiltroEstoqueMenorIgual implements CriterioFiltragem {
    private int quantidadeMaxima;

    public FiltroEstoqueMenorIgual(int quantidadeMaxima) {
        this.quantidadeMaxima = quantidadeMaxima;
    }

    @Override
    public boolean selecionar(Produto produto) {
        return produto.getQtdEstoque() <= quantidadeMaxima;
    }
}