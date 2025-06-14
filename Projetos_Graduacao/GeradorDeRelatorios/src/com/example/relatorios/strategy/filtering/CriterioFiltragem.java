package src.com.example.relatorios.strategy.filtering;

import src.com.example.relatorios.model.Produto;

public interface CriterioFiltragem {
    boolean selecionar(Produto produto);
}