package src.com.example.relatorios.strategy.sorting;

import src.com.example.relatorios.model.Produto;
import java.util.Comparator;

public class CriterioDescricaoDecrescente implements Comparator<Produto> {
    @Override
    public int compare(Produto p1, Produto p2) {
        return p2.getDescricao().compareToIgnoreCase(p1.getDescricao());
    }
}