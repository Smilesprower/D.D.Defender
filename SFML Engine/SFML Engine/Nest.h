#pragma once
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"
class Nest
{

	enum States
	{
		Wander,
		Flee,
	};
	enum Direction
	{
		Left = -1,
		Right = 1,
	};

public:
	Nest(sf::Texture & tex, sf::Vector2f pos, sf::Vector2i screenBounds);
	~Nest();
	void update(sf::Time deltaTime);
	AnimatedSprite draw();

private:
	const int MAX_MISSILES = 2;
	const int COOLDOWN_TIMER = 0;

	bool m_alive;
	int m_state;
	int m_direction;
	sf::Vector2i m_screenBounds;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	AnimatedSprite m_sprite;
};

