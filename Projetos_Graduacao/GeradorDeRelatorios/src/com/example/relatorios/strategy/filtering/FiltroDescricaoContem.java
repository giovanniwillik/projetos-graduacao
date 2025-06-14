package src.com.example.relatorios.strategy.filtering;

import src.com.example.relatorios.model.Produto;

public class FiltroDescricaoContem implements CriterioFiltragem {
    private String substringAlvo;

    public FiltroDescricaoContem(String substringAlvo) {
        this.substringAlvo = substringAlvo;
    }

    @Override
    public boolean selecionar(Produto produto) {
        return produto.getDescricao().toLowerCase().contains(substringAlvo.toLowerCase());
    }
}