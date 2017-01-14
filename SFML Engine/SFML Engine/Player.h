#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"
#include "BulletManager.h"

class Player
{
public:
	
	enum SmartBomb
	{
		Ready,
		Charging,
		Fired,
		Disable,
	};
	Player();
	~Player();

	void init(sf::Texture & tex, sf::Vector2f pos, sf::Vector2i tpBounds);
	void update(sf::Time deltaTime);
	void Move(sf::Time deltaTime);
	AnimatedSprite draw();
	void teleport(sf::Time deltaTime);
	int getTeleport();
	void disableTeleporter();
	int getSmartBombState();
	void chargeSmartBomb();
	void updateSmartBomb(sf::Time deltaTime);
	void setDamage(int damage);
	int getHealth();
	int getRadius();
	bool gameOver();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
	sf::CircleShape drawPlayerOutline();
	AnimatedSprite m_animatedSprite;
	float m_smartBombTimer;

private:
	enum Anims
	{
		MoveUp,
		MoveDown,
		MoveSideways,
		Explosion,
	};
	enum Direction
	{
		Left = -1,
		Right = 1,
		Up,
		Down
	};
	const int MAX_SPEED = 700;
	const int SMART_BOMB_RELOAD_TIME = 1;
	const int PLAYER_RADIUS = 35;
	const int MAX_FRAMES_EXPLOSION = 7;
	const float DE_ACCEL = 4.f;
	const float BULLET_RELOAD_TIME = 100.f;

	bool m_gameOver;
	int m_health;
	int m_teleportedState;
	int m_smartBombState;
	float m_bulletTimer;

	int m_directionX;
	int m_directionY;

	sf::Vector2f m_accel;
	sf::Vector2f m_velocity;
	sf::Vector2i m_teleportingBounds;

	int NUM_OF_ANIMS = 4;

	sf::Time m_frameTime;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
	sf::CircleShape m_playerCollider;
};