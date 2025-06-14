package src.com.example.relatorios.strategy.filtering;

import src.com.example.relatorios.model.Produto;

public class FiltroTodos implements CriterioFiltragem {
    @Override
    public boolean selecionar(Produto produto) {
        return true;
    }
}