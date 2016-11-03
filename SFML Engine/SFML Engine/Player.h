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

	void init(sf::Texture & pTex, sf::Vector2f pPos);
	void update(sf::Time deltaTime);
	void Move(sf::Time deltaTime);
	AnimatedSprite draw();


	AnimatedSprite m_animatedSprite;
private:

	bool m_health;
	float m_ACCELERATION;
	int m_directionX;
	int m_directionY;
	const int MAX_SPEED = 5;
	sf::Vector2f m_velocity;

	int NUM_OF_ANIMS = 4;

	sf::Time m_frameTime;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
};