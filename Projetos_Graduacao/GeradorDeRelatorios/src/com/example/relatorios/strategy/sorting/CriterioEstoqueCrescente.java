package src.com.example.relatorios.strategy.sorting;

import src.com.example.relatorios.model.Produto;
import java.util.Comparator;

public class CriterioEstoqueCrescente implements Comparator<Produto> {
    @Override
    public int compare(Produto p1, Produto p2) {
        return Integer.compare(p1.getQtdEstoque(), p2.getQtdEstoque());
    }
}