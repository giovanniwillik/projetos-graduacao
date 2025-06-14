package src.com.example.relatorios.strategy.sorting;

import src.com.example.relatorios.model.Produto;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class QuickSort implements AlgoritmoOrdenacao {
    @Override
    public void ordenar(List<Produto> produtos, Comparator<Produto> criterio) {
        if (produtos == null || produtos.isEmpty()) {
            return;
        }
        quickSort(produtos, 0, produtos.size() - 1, criterio);
    }

    private void quickSort(List<Produto> produtos, int ini, int fim, Comparator<Produto> criterio) {
        if (ini < fim) {
            int q = particiona(produtos, ini, fim, criterio);
            quickSort(produtos, ini, q, criterio);
            quickSort(produtos, q + 1, fim, criterio);
        }
    }

    private int particiona(List<Produto> produtos, int ini, int fim, Comparator<Produto> criterio) {
        Produto x = produtos.get(ini);
        int i = ini - 1;
        int j = fim + 1;

        while (true) {
            do {
                j--;
            } while (criterio.compare(produtos.get(j), x) > 0);

            do {
                i++;
            } while (criterio.compare(produtos.get(i), x) < 0);

            if (i < j) {
                Collections.swap(produtos, i, j);
            } else {
                return j;
            }
        }
    }
}