package src.com.example.relatorios.strategy.filtering;

import src.com.example.relatorios.model.Produto;

public class FiltroCategoriaIgual implements CriterioFiltragem {
    private String categoriaAlvo;

    public FiltroCategoriaIgual(String categoriaAlvo) {
        this.categoriaAlvo = categoriaAlvo;
    }

    @Override
    public boolean selecionar(Produto produto) {
        return produto.getCategoria().equalsIgnoreCase(categoriaAlvo);
    }
}