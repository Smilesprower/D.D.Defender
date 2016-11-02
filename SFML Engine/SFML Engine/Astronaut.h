#pragma once
#include <SFML\Graphics.hpp>
#include "Helper.h"

class Astronaut
{
public:

	enum State
	{
		Flee,
		Wander,
		Falling,
		Abducted
	};

	Astronaut();
	~Astronaut();

	void init(sf::Texture & tex, int xPos);
	void update(sf::Time deltaTime);
	sf::Sprite draw();

private:

	bool m_alive;
	int m_direction;
	int m_state;

	sf::Vector2f m_velocity;

	sf::Sprite m_sprite; 
	sf::IntRect m_dimensions;


	sf::Vector2f target;
	sf::Text m_text;

	 int GROUND = 934;
	 int RADIUS = 100;
	 int GRAVITY = 100;
	 int MAX_SPEED = 50;
};