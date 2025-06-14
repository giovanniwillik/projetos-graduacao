package src.com.example.relatorios.decorator;

import src.com.example.relatorios.model.Produto;

public class ProdutoItalicoDecorator extends ProdutoDecorator {

    public ProdutoItalicoDecorator(Produto produtoDecorado) {
        super(produtoDecorado);
    }

    @Override
    public String formataParaImpressao() {
        return "<span style=\"font-style:italic\">" + produtoDecorado.formataParaImpressao() + "</span>";
    }
}