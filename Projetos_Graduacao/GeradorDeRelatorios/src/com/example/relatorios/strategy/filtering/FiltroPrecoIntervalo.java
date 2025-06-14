package src.com.example.relatorios.strategy.filtering;

import src.com.example.relatorios.model.Produto;

public class FiltroPrecoIntervalo implements CriterioFiltragem {
    private double precoMinimo;
    private double precoMaximo;

    public FiltroPrecoIntervalo(double precoMinimo, double precoMaximo) {
        this.precoMinimo = precoMinimo;
        this.precoMaximo = precoMaximo;
    }

    @Override
    public boolean selecionar(Produto produto) {
        return produto.getPreco() >= precoMinimo && produto.getPreco() <= precoMaximo;
    }
}