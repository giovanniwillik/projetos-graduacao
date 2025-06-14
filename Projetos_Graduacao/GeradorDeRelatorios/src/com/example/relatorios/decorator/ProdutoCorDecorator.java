package src.com.example.relatorios.decorator;

import src.com.example.relatorios.model.Produto;

public class ProdutoCorDecorator extends ProdutoDecorator {
    private String corHex;

    public ProdutoCorDecorator(Produto produtoDecorado, String corHex) {
        super(produtoDecorado);
        this.corHex = corHex;
    }

    @Override
    public String formataParaImpressao() {
        return "<span style=\"color:" + corHex + "\">" + produtoDecorado.formataParaImpressao() + "</span>";
    }
}