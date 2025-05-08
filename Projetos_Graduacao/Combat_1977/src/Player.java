import java.awt.*;
import java.awt.image.BufferedImage;

/**
 * Esta classe representa os jogadores (players) do jogo. A classe principal do
 * jogo
 * instancia dois objetos deste tipo quando a execução é iniciada.
 */
public class Player implements ISolid {
	private double direction;
	private double cx, cy, width, height, speed;
	private Color color;
	private String id;
	private BufferedImage img;

	private boolean dead = false;
	private long deathTime = 0;
	private long lastFireTime = 0;

	private static final long RESPAWN_DELAY = 1000; // 1 segundo
	private static final long FIRE_INTERVAL = 300; // 300 ms entre disparos
	private static final double ROTATION_SPEED = Math.PI / 20; // rad/ms

	private static final double SHOT_SIZE = 5;
	private static final double SHOT_SPEED = 0.3; // pixels/ms

	/**
	 * Construtor da classe Player.
	 * 
	 * @param cx     coordenada x da posição inicial do player (centro do retângulo
	 *               que o representa).
	 * @param cy     coordenada y da posição inicial do player (centro do retângulo
	 *               que o representa).
	 * @param width  largura do retângulo que representa o player.
	 * @param height altura do retângulo que representa o player.
	 * @param angle  direção apontada pelo player
	 * @param sprite gráfico do player
	 * @param color  cor do player.
	 * @param id     uma string que identifica o player
	 * @param speed  velocidade do movimento do player.
	 */
	public Player(double cx, double cy, double width, double height, double angle, BufferedImage sprite, Color color,
			String id, double speed) {
		this.cx = cx;
		this.cy = cy;
		this.width = width;
		this.height = height;
		this.color = color;
		this.id = id;
		this.direction = angle;
		this.speed = speed;
		this.img = sprite;
	}

	/**
	 * Método chamado sempre que o player precisa ser (re)desenhado.
	 */
	public void draw() {
		GameLib.setColor(color);

		if (isDead()) {
			long now = System.currentTimeMillis();
			GameLib.drawImage(img, cx, cy, direction + now % 60 * 60, width / img.getWidth());
			return;
		}

		GameLib.drawImage(img, cx, cy, direction, width / img.getWidth());
	}

	/**
	 * Método chamado quando se deseja mover para a frente na direção atual.
	 * Este método é chamado sempre que a tecla associada à ação
	 * de mover o player para frente estiver pressionada.
	 * 
	 * @param delta quantidade de milissegundos que se passou entre o ciclo anterior
	 *              de atualização do jogo e o atual.
	 */
	public void moveForwards(long delta) {
		if (isDead())
			return;

		double dx = Math.cos(Math.toRadians(direction)) * speed * delta;
		double dy = Math.sin(Math.toRadians(direction)) * speed * delta;

		cx += dx;
		cy += dy;
	}

	/**
	 * Método chamado quando se deseja mover o player para trás na direção atual.
	 * Este método é chamado sempre que a tecla associada à ação
	 * de mover o player para trás estiver pressionada.
	 * 
	 * @param delta quantidade de milissegundos que se passou entre o ciclo anterior
	 *              de atualização do jogo e o atual.
	 */
	public void moveBackwards(long delta) {
		if (isDead())
			return;

		double dx = Math.cos(Math.toRadians(direction)) * speed * delta;
		double dy = Math.sin(Math.toRadians(direction)) * speed * delta;

		cx -= dx;
		cy -= dy;
	}

	/**
	 * Método chamado quando se deseja girar o player para a esquerda (sentido
	 * anti-horário).
	 * Este método é chamado sempre que a tecla associada à ação
	 * de rotacionar o player à esquerda estiver pressionada.
	 * 
	 * @param delta quantidade de milissegundos que se passou entre o ciclo anterior
	 *              de atualização do jogo e o atual.
	 */
	public void rotateLeft(long delta) {
		if (isDead())
			return;

		direction -= delta * ROTATION_SPEED;
		direction = direction % Math.toDegrees(2 * Math.PI);
	}

	/**
	 * Método chamado quando se deseja girar o player para a direita (sentido
	 * horário).
	 * Este método é chamado sempre que a tecla associada à ação
	 * de rotacionar o player à direita estiver pressionada.
	 * 
	 * @param delta quantidade de milissegundos que se passou entre o ciclo anterior
	 *              de atualização do jogo e o atual.
	 */
	public void rotateRight(long delta) {
		if (isDead())
			return;

		direction += delta * ROTATION_SPEED;
		direction = direction % Math.toDegrees(2 * Math.PI);
	}

	/**
	 * Retorna se o jogador pode realizar um disparo ou não. Chamado sempre que a
	 * ação de disparar
	 * desse player for acionada.
	 */
	public boolean canFire() {
		if (isDead())
			return false;

		long now = System.currentTimeMillis();
		return (now - lastFireTime) > FIRE_INTERVAL;
	}

	/**
	 * Cria um disparo vindo desse player na mesma direção apontada pelo player.
	 * Esse método cria o disparo e o adiciona ao jogo.
	 */
	public void fire() {
		if (isDead())
			return;

		lastFireTime = System.currentTimeMillis();
		Shot shot = new Shot(this, cx, cy, SHOT_SIZE, direction, SHOT_SPEED);

		Combat.addShot(shot);
		// Adiciona o disparo à lista de disparos do jogo
	}

	/**
	 * Retorna se o player acabou de ser destruído. Enquanto o player estiver
	 * destruído, ele não
	 * poderá ser danificado novamente.
	 */
	public boolean isDead() {
		if (dead) {
			long now = System.currentTimeMillis();
			if (now - deathTime > RESPAWN_DELAY) {
				dead = false;
				deathTime = 0;
				lastFireTime = 0;
				return false;
			}
		}
		return dead;
	}

	/**
	 * Chamado sempre que o player for destruído com um disparo.
	 */
	public void die() {
		dead = true;
		deathTime = System.currentTimeMillis();
		cx = Map.getRandomRespawn()[0];
		cy = Map.getRandomRespawn()[1];
	}

	/**
	 * Método que devolve a string de identificação do player.
	 * 
	 * @return a String de identificação.
	 */
	public String getId() {
		return id;
	}

	/**
	 * Teleporta o player para essa coordenada do mapa.
	 */
	public void setPosition(double cx, double cy) {
		this.cx = cx;
		this.cy = cy;
	}

	/**
	 * Método que devolve a largura do retângulo que representa o player.
	 * 
	 * @return um double com o valor da largura.
	 */
	public double getWidth() {
		return width;
	}

	/**
	 * Método que devolve a altura do retângulo que representa o player.
	 * 
	 * @return um double com o valor da altura.
	 */
	public double getHeight() {
		return height;
	}

	/**
	 * Método que devolve a coordenada x do centro do retângulo que representa o
	 * player.
	 * 
	 * @return o valor double da coordenada x.
	 */
	public double getCx() {
		return cx;
	}

	/**
	 * Método que devolve a coordenada y do centro do retângulo que representa o
	 * player.
	 * 
	 * @return o valor double da coordenada y.
	 */
	public double getCy() {
		return cy;
	}

	/**
	 * Obtém a cor do player.
	 */
	public Color getColor() {
		return color;
	}
}
