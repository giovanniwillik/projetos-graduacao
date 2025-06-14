package src.com.example.relatorios.strategy.sorting;

import src.com.example.relatorios.model.Produto;
import java.util.Comparator;
import java.util.List;

public class InsertionSort implements AlgoritmoOrdenacao {
    @Override
    public void ordenar(List<Produto> produtos, Comparator<Produto> criterio) {
        if (produtos == null || produtos.isEmpty()) {
            return;
        }
        for (int i = 0; i < produtos.size(); i++) {
            Produto x = produtos.get(i);
            int j = i - 1;

            while (j >= 0 && criterio.compare(x, produtos.get(j)) < 0) {
                produtos.set(j + 1, produtos.get(j));
                j--;
            }
            produtos.set(j + 1, x);
        }
    }
}