#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "Helper.h"
#include "Pvector.h"
class Alien
{
public:
	enum Anims
	{
		Default,
		Explode,
	};
	enum State
	{
		Blank,
		Capture,
		Flock,
		Dying,
	};

	Alien(sf::Texture & tex, sf::Vector2i screenBounds);
	~Alien();
	void init(sf::Vector2f position);

	void applyForce(Pvector force);

	Pvector separation(std::vector<Alien*> *alien);
	Pvector alignment(std::vector<Alien*> *alien);
	Pvector cohesion(std::vector<Alien*> *alien);
	Pvector seek(Pvector v);

	void run(std::vector<Alien*> *alien, sf::Time deltaTime);
	void updateFlocking(sf::Time deltaTime);
	void updateCapture(sf::Time dt);
	void updateDying(sf::Time dt);
	void borders();
	void flock(std::vector<Alien*> *alien);

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

	AnimatedSprite draw();

	//	DEBUGGING
	sf::CircleShape drawCollisionRadius();
	sf::CircleShape m_collisionRadius;

private:
	// AI SHTUFF
	///////////////////////////////////
	const float STRENGHT_ATT = 1;
	const float STRENGHT_REP = 2;
	const float ATTENUATION_ATT = 4;
	const float ATTENUATION_REP = 5;
	float m_maxSpeed, m_maxForce;
	Pvector m_location;
	Pvector m_velocity;
	Pvector m_acceleration;
	sf::Vector2i m_screenBounds;
	///////////////////////////////////

	int m_health;
	const int RADIUS = 50;
	const int ABDUCT_RADIUS = 200;
	bool m_alive;
	int m_currentState;
	int NUM_OF_ANIMS = 3;
	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;

};

