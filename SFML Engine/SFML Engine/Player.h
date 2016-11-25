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
	void teleport();
	int getTeleport();
	void disableTeleporter();
	int getSmartBombState();
	void chargeSmartBomb();
	void updateSmartBomb(sf::Time deltaTime);
	int getHealth();
	AnimatedSprite m_animatedSprite;
	float m_smartBombTimer;

private:
	enum Anims
	{
		MoveUp,
		MoveDown,
		MoveSideways,
	};
	enum Direction
	{
		Left = -1,
		Right = 1,
		Up,
		Down
	};

	int m_health;
	int m_teleportedState;
	int m_smartBombState;
	float m_bulletTimer;

	int m_directionX;
	int m_directionY;
	sf::Vector2f m_accel;
	const float DE_ACCEL = 4.f;
	const int MAX_SPEED = 700;
	const int SMART_BOMB_RELOAD_TIME = 60;
	const float BULLET_RELOAD_TIME = 100.f;
	sf::Vector2f m_velocity;
	sf::Vector2i m_teleportingBounds;

	int NUM_OF_ANIMS = 4;

	sf::Time m_frameTime;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
};