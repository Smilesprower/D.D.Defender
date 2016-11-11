#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"

class Player
{
public:
	enum Anims
	{
		MoveUp,
		MoveDown,
		MoveSideways,
	};
	enum Direction
	{
		Left,
		Right,
		Up,
		Down
	};

	Player();
	~Player();

	void init(sf::Texture & tex, sf::Vector2f pos, sf::Vector2i tpBounds);
	void update(sf::Time deltaTime);
	void Move(sf::Time deltaTime);
	AnimatedSprite draw();
	void teleport();
	AnimatedSprite m_animatedSprite;
private:

	bool m_health;
	bool m_teleported;

	int m_directionX;
	int m_directionY;
	sf::Vector2f m_accel;
	const float DE_ACCEL = 4.f;
	const int MAX_SPEED = 700;
	sf::Vector2f m_velocity;
	sf::Vector2i m_teleportingBounds;

	int NUM_OF_ANIMS = 4;

	sf::Time m_frameTime;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
};