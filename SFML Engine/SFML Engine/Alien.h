/*! \brief Handles all the properties of the Abductor.
*
*
*
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "BulletManager.h"
#include "Astronaut.h"
#include "Helper.h"
#include "Pvector.h"
class Alien
{
public:
	enum Anims
	{
		Default,
		Explode,
		Abduct,
	};
	enum State
	{
		Blank,
		Target,
		Capture,
		Flock,
		Dying,
	};

	Alien(sf::Texture & tex, sf::Vector2i screenBounds, sf::Vector2i worldBounds);
	~Alien();
	void init(sf::Vector2f position);


	sf::Vector2f separation(std::vector<Alien*> *alien, int index);
	sf::Vector2f alignment(std::vector<Alien*>* alien, int index);
	sf::Vector2f cohesion(std::vector<Alien*> *alien, int index);

	bool run(std::vector<Alien*> *alien, sf::Time deltaTime, sf::Vector2f playerPos, int index);
	void updateFlocking(sf::Time deltaTime, sf::Vector2f playerPos);
	bool updateTargetCapture(sf::Time dt);
	void updateDying(sf::Time dt);
	void borders();
	void flock(std::vector<Alien*> *alien, int index);

	bool getAlive();
	void setAlive(bool alive);

	int getState();
	void setState(int state);

	int getRadius();
	int getAbductRadius();

	void setDamage(int damage);
	int getHealth();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	void setAstro(Astronaut* astro);
	AnimatedSprite draw();

	void checkBounds();
	int getCurrentState();

private:
	// AI SHTUFF
	///////////////////////////////////
	float m_maxSpeed, m_maxForce;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	sf::Vector2i m_screenBounds;
	sf::Vector2i m_worldBounds;
	///////////////////////////////////
	const int BULLET_COOLDOWN_TIMER = 2;
	const int BULLET_RANGE = 700;
	float m_bulletReloadTimer;

	int m_health;
	const int RADIUS = 50;
	const int ABDUCT_RADIUS = 400;
	const int TARGET_SPEED = 200;
	bool m_alive;
	int m_currentState;
	int NUM_OF_ANIMS = 3;
	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
	Astronaut * m_astro;
};

