import java.awt.*;

/**
	Esta classe representa um placar no jogo. A classe principal do jogo instancia dois objetos deste
	tipo, cada um responsável por gerenciar a pontuação de um player, quando a execução é iniciada.
*/
public class Score {
	private int counter;
	private String playerId;

	/**
		Construtor da classe Score.

		@param playerId uma string que identifica o player ao qual este placar está associado.
	*/
	public Score(String playerId){
		this.playerId = playerId;
		this.counter = 0;
	}

	/**
		Método de desenho do placar.
	*/
	public void draw(){
		if(playerId.equals(Combat.PLAYER1)){
			GameLib.setColor(Color.GREEN);
			GameLib.drawText(Combat.PLAYER1 + ": " + counter, 40, GameLib.ALIGN_LEFT);			
		} else if(playerId.equals(Combat.PLAYER2)){
			GameLib.setColor(Color.BLUE);
			GameLib.drawText(Combat.PLAYER2 + ": " + counter, 40, GameLib.ALIGN_RIGHT);			
		}
	}

	/**
		Método que incrementa em 1 unidade a contagem de pontos.
	*/
	public void inc(){
		counter++;
	}

	/**
		Método que devolve a contagem de pontos mantida pelo placar.

		@return o valor inteiro referente ao total de pontos.
	*/
	public int getScore(){
		return counter;
	}

	/**
	 * Obtém o ID do player associado a este placar.
	 */
	public String getPlayerId() {
		return playerId;
	}
}
