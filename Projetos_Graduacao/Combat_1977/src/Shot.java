/**
 * Esta classe representa um dos disparos ativos usado no jogo. Essa classe
 * sempre deve ser
 * instanciada quando um disparo for feito por algum dos jogadores.
 */
public class Shot implements ISolid {
	private Player owner;
	private double cx, cy, size, vx, vy, speed;
	private boolean active;

	/**
	 * Construtor da classe Shot.
	 * 
	 * @param player    dono do disparo.
	 * @param cx        coordenada x da posição inicial do disparo (centro do
	 *                  quadrado que a representa).
	 * @param cy        coordenada y da posição inicial do disparo (centro do
	 *                  quadrado que a representa).
	 * @param size      tamanho do quadrado que representa o disparo
	 * @param direction ângulo do disparo em graus
	 * @param speed     velocidade da bola (em pixels por milissegundo).
	 */
	public Shot(Player player, double cx, double cy, double size, double direction, double speed) {
		this.owner = player;
		this.cx = cx;
		this.cy = cy;
		this.size = size;
		this.speed = speed;
		active = true;

		vx = Math.cos(Math.toRadians(direction));
		vy = Math.sin(Math.toRadians(direction));
	}

	/**
	 * Método chamado sempre que o disparo precisa ser (re)desenhada.
	 */
	public void draw() {
		GameLib.setColor(owner.getColor());
		GameLib.fillRect(cx, cy, size, size);
	}

	/**
	 * Método chamado quando o estado (posição) do disparo precisa ser atualizado.
	 * 
	 * @param delta quantidade de milissegundos que se passou entre o ciclo anterior
	 *              de atualização do jogo e o atual.
	 */
	public void update(long delta) {
		if (!active)
			return;

		cx += vx * speed * delta;
		cy += vy * speed * delta;

		if (cx < 0 || cx > GameLib.WIDTH || cy < 0 || cy > GameLib.HEIGHT) {
			active = false;
		}
	}

	/**
	 * Método chamado quando detecta-se uma colisão do disparo com um jogador.
	 * 
	 * @param player o jogador que foi acertado.
	 */
	public void onPlayerCollision(Player player) {
		if (player.isDead())
			return;
		if (!player.equals(owner)) {
			active = false;
			player.die();
		}
	}

	/**
	 * Método chamado quando detecta-se uma colisão do disparo com alguma parede.
	 */
	public void onWallCollision() {
		active = false;
	}

	/**
	 * Método que verifica se houve colisão ou não do disparo com uma parede.
	 * 
	 * @param wall referência para uma instância de Wall contra a qual será
	 *             verificada a ocorrência de colisão da bola.
	 * @return um valor booleano que indica a ocorrência (true) ou não (false) de
	 *         colisão.
	 */
	public boolean checkCollision(Wall wall) {
		return !(cx < wall.getCx() - wall.getWidth() / 2 ||
				cx > wall.getCx() + wall.getWidth() / 2 ||
				cy < wall.getCy() - wall.getHeight() / 2 ||
				cy > wall.getCy() + wall.getHeight() / 2);
	}

	/**
	 * Método que verifica se houve colisão do disparo algum jogador.
	 * 
	 * @param player referência para uma instância de Player contra o qual será
	 *               verificada a ocorrência de colisão do disparo.
	 * @return um valor booleano que indica a ocorrência (true) ou não (false) de
	 *         colisão.
	 */
	public boolean checkCollision(Player player) {
		if (player.isDead())
			return false;
		return !(cx < player.getCx() - player.getWidth() / 2 ||
				cx > player.getCx() + player.getWidth() / 2 ||
				cy < player.getCy() - player.getHeight() / 2 ||
				cy > player.getCy() + player.getHeight() / 2)
				&& !player.equals(owner);
	}

	/**
	 * Esse método diz se o disparo está ativo ainda ou não. Um disparo ativo ainda
	 * interage com os
	 * elementos do jogo.
	 */
	public boolean isActive() {
		return active;
	}

	/**
	 * Método que devolve a coordenada x do centro do quadrado que representa o
	 * disparo.
	 * 
	 * @return o valor double da coordenada x.
	 */
	public double getCx() {
		return cx;
	}

	/**
	 * Método que devolve a coordenada y do centro do quadrado que representa o
	 * disparo.
	 * 
	 * @return o valor double da coordenada y.
	 */
	public double getCy() {
		return cy;
	}

	/**
	 * Método que devolve a velocidade do disparo.
	 * 
	 * @return o valor double da velocidade.
	 * 
	 */
	public double getSpeed() {
		return speed;
	}

	/** Obtém a largura do retângulo que representa o disparo. */
	public double getWidth() {
		return size;
	}

	/** Obtém a altura do retângulo que representa o disparo. */
	public double getHeight() {
		return size;
	}

	/**
	 * Obtém o dono desse disparo.
	 * 
	 * @return o player que efetuou o disparo
	 */
	public Player getOwner() {
		return owner;
	}
}
