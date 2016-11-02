#pragma once
#include <SFML\Graphics.hpp>

class Astronaut
{
public:

	enum Direction
	{
		Left,
		Right
	};

	Astronaut();
	~Astronaut();

	void init(sf::Texture & pTex, sf::Vector2f pPos);
	void update(sf::Time deltaTime);
	sf::Sprite draw();

private:

	bool m_alive;
	bool m_flee;
	bool m_abducted;
	int m_direction;

	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;

	const int RADIUS = 100;
	const int MAX_SPEED = 100;
};