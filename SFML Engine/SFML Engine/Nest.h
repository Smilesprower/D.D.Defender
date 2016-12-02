#pragma once
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"
class Nest
{
	enum Anims
	{
		Default,
		Explode,
	};
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
	Nest();
	~Nest();
	void update(sf::Time deltaTime, sf::Vector2f playerPos);
	void init(sf::Texture & tex, sf::Vector2f pos, sf::Vector2i screenBounds);
	void checkBounds(sf::Vector2f playerPos);
	AnimatedSprite draw();

private:
	const int MAX_MISSILES = 2;
	const int COOLDOWN_TIMER = 0;
	const int NUM_OF_ANIMS = 2;
	const int MAX_VELOCITY = 200;
	const int MAX_HEALTH = 500;
	const int TIME_TO_SWITCH_DIRECTION = 10;

	float m_wanderTime;
	int m_health;
	bool m_alive;
	int m_state;
	int m_direction;
	sf::Vector2i m_screenBounds;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
};

