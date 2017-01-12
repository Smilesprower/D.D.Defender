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
	sf::Vector2f getPosition();
	sf::Vector2f getAbductPosition();
	void setPosition(sf::Vector2f position);
	AnimatedSprite draw();

	void setAbducted();
	int isAbducted();

	void setTargeted(bool targeted);
	bool isTargeted();

	int getRadius();

	void setFalling();
	//	DEBUGGING
	sf::CircleShape drawCollisionRadius();
	sf::CircleShape m_collisionRadius;

private:
	bool m_targeted;
	bool m_alive;
	int m_direction;
	int m_state;
	sf::Vector2f m_velocity;
	sf::Vector2f m_abductPos;

	int GROUND = 925;
	int RADIUS = 25;
	int GRAVITY = 100;
	int MAX_SPEED = 2000;
	int NUM_OF_ANIMS = 3;
	int MAX_ABDUCTED_SPEED = -100;
	const int TIME_TO_SWITCH_DIRECTION = 10;

	float m_wanderTime;

	sf::Vector2f m_abductedVelocity;

	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
};