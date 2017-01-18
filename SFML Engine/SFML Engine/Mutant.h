/*! \brief Handles all the properties of the Mutant.
*
*
*
*/

#pragma once
#include "AnimatedSprite.h"
#include "Pvector.h"
#include "BulletManager.h"

#include <math.h>

class Mutant
{
public:
	enum Anims
	{
		Default,
		Explode,
	};
	enum States
	{
		Start, 
		Dying,
		FormationA,
		FormationB,
		FormationC,
	};

	Mutant(sf::Texture & tex, sf::Vector2i screenBounds, sf::Vector2i worldBounds);
	~Mutant();

	void update(int mutantSize, int currentMutant, sf::Time deltaTime, sf::Vector2f playerPos, sf::Vector2f playerVel);
	void init(sf::Vector2f pos);
	void checkBounds();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	AnimatedSprite draw();

	void setDamage(int damage);
	int getHealth();
	int getRadius();

	bool isAlive();
	void setAlive(bool alive);

	int getCurrentState();

	//void applyForce(Pvector force);
	//Pvector seek(sf::Vector2f playerpos);
	//Pvector getVelocity();
private:
	float m_maxSpeed, m_maxForce;
	//Pvector m_location;
	//Pvector m_velocity;
	//Pvector m_acceleration;


	int NUM_OF_ANIMS = 3;
	const int COLLISION_RADIUS = 50;
	const int BULLET_COOLDOWN_TIMER = 2;
	const int BULLET_RANGE = 700;
	float m_bulletReloadTimer;
	float m_kamikazeTimer;
	int m_health;
	bool m_alive;
	int m_state;
	sf::Vector2i m_screenBounds;
	sf::Vector2i m_worldBounds;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	//sf::Vector2f m_acceleration;

	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
};

