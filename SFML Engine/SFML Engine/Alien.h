#pragma once
#include <SFML/Graphics.hpp>
#include "Helper.h"
class Alien
{
public:
	Alien(sf::Texture & tex, sf::Vector2f position);
	~Alien();

	void applyForce(sf::Vector2f force);

	// Three Laws that boids follow
	sf::Vector2f separation(std::vector<Alien> alien);
	sf::Vector2f alignment(std::vector<Alien> alien);
	sf::Vector2f cohesion(std::vector<Alien> alien);

	//Functions involving SFML and visualisation linking
	sf::Vector2f seek(sf::Vector2f v);

	void run(std::vector<Alien> alien, sf::Time deltaTime);
	void update(sf::Time deltaTime);
	void borders();

	void flock(std::vector<Alien> alien);
	void swarm(std::vector<Alien> alien);

private:
	const float STRENGHT_ATT = 1;
	const float STRENGHT_REP = 2;
	const float ATTENUATION_ATT = 4;
	const float ATTENUATION_REP = 5;

	bool predator;
	float m_maxSpeed, m_maxForce;
	sf::Vector2f m_position, m_velocity, m_accel;
};

