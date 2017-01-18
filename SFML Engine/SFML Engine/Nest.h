/*! \brief The Nest Class. Handles all the properties and responsibilities of the Nest.
*
*
*
*/

#pragma once
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"
#include "BulletManager.h"

class Nest
{
	enum Anims
	{
		Default,
		Explode,
		Electricity,
	};
	enum States
	{
		Wander,
		Evade,
	};
	enum Direction
	{
		Left = -1,
		Right = 1,
	};

public:
	Nest(sf::Texture & tex, sf::Vector2i screenBounds);
	~Nest();
	bool update(sf::Time deltaTime, sf::Vector2f playerPos);
	void init(sf::Vector2f pos);
	void checkBounds();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	AnimatedSprite draw();
	AnimatedSprite drawElectricity();
	sf::CircleShape drawEvade();
	sf::CircleShape drawFire();

	void setDamage(int damage);
	int getHealth();
	int getRadius();
	bool isAlive();
	void setAlive(bool alive);

private:
	const int COOLDOWN_TIMER = 10;
	const int NUM_OF_ANIMS = 2;
	const int MAX_VELOCITY = 200;
	const int MAX_EVADE_VELOCITY = 400;
	const int MAX_HEALTH = 500;
	const int TIME_TO_SWITCH_DIRECTION = 10;
	const int MISSILE_RANGE = 750;
	const int EVADE_RANGE = 1000;
	const int NEST_RADIUS = 150;

	float m_missileReloadTimer;
	float m_wanderTime;
	int m_health;
	bool m_alive;
	int m_state;
	int m_direction;
	float m_spawnTimer;
	sf::Vector2i m_screenBounds;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	sf::CircleShape m_missileRadius;
	sf::CircleShape m_evadeRadius;

	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	AnimatedSprite m_animatedSprite1;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
	std::vector<Animation> m_animations1;
	Animation* m_currAnimation1;
};

