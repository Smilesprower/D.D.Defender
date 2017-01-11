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

	Alien();
	~Alien();
	void init(sf::Texture & tex, sf::Vector2f position, sf::Vector2f velocity);

	void applyForce(Pvector force);

	Pvector separation(std::vector<Alien*> *alien);
	Pvector alignment(std::vector<Alien*> *alien);
	Pvector cohesion(std::vector<Alien*> *alien);
	Pvector seek(Pvector v);

	void run(std::vector<Alien*> *alien, sf::Time deltaTime);
	void update(sf::Time deltaTime);
	void borders();
	void flock(std::vector<Alien*> *alien);

	AnimatedSprite draw();
	sf::CircleShape drawCirc();

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
	///////////////////////////////////

	int NUM_OF_ANIMS = 3;
	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
	sf::CircleShape m_circ;

};

