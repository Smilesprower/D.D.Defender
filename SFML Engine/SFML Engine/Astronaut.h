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

	Astronaut(sf::Texture & tex, int xPos);
	~Astronaut();

	void init(sf::Texture & tex, int xPos);
	void update(sf::Time deltaTime);
	void abducted(sf::Time deltaTime);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	AnimatedSprite draw();

	void setAbducted();
	int isAbducted();
	int getRadius();

	//	DEBUGGING
	sf::CircleShape drawCollisionRadius();
	sf::CircleShape m_collisionRadius;

private:
	bool m_alive;
	int m_direction;
	int m_state;
	sf::Vector2f m_velocity;

	int GROUND = 925;
	int RADIUS = 25;
	int GRAVITY = 100;
	int MAX_SPEED = 500;
	int NUM_OF_ANIMS = 3;
	int MAX_ABDUCTED_SPEED = -100;

	sf::Vector2f m_abductedVelocity;

	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
};