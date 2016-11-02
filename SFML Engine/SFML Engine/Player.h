#include <SFML\Graphics.hpp>

class Player
{
public:

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
	sf::Sprite draw();

private:

	bool m_health;
	float m_ACCELERATION;
	int m_directionX;
	int m_directionY;

	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;

	const int MAX_SPEED = 5;
};