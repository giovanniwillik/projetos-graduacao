package src.com.example.relatorios.strategy.sorting;

import src.com.example.relatorios.model.Produto;
import java.util.List;
import java.util.Comparator;

public interface AlgoritmoOrdenacao {
    void ordenar(List<Produto> produtos, Comparator<Produto> criterio);
}