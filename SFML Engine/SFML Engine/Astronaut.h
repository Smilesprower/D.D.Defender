#pragma once
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"


class Astronaut
{
public:
	enum Anims
	{
		WalkLeft,
		WalkRight,
		Falling_Abducted,
	};
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
	void setPosition(sf::Vector2f);
	AnimatedSprite draw();


private:
	bool m_alive;
	int m_direction;
	int m_state;
	sf::Vector2f m_velocity;

	int GROUND = 500;
	int RADIUS = 100;
	int GRAVITY = 100;
	int MAX_SPEED = 500;
	int NUM_OF_ANIMS = 3;

	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;

};