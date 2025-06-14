package src.com.example.relatorios.decorator;

import src.com.example.relatorios.model.Produto;

public class ProdutoNegritoDecorator extends ProdutoDecorator {

    public ProdutoNegritoDecorator(Produto produtoDecorado) {
        super(produtoDecorado);
    }

    @Override
    public String formataParaImpressao() {
        return "<span style=\"font-weight:bold\">" + produtoDecorado.formataParaImpressao() + "</span>";
    }
}