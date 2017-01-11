#include "stdafx.h"
#include "Flock.h"


Flock::Flock()
{
}


Flock::~Flock()
{
}

Alien Flock::getAlien(int i)
{
	return m_flock[i];
}

void Flock::addAlien(Alien alien)
{
	m_flock.push_back(Alien(alien));
}

void Flock::flocking(sf::Time deltaTime)
{
	for (int i = 0; i < m_flock.size(); i++)
	{
		// Check type of enemy
		// Check state of enemy
		// Run
	}
}

void Flock::swarming(sf::Time deltaTime)
{
	for (int i = 0; i < m_flock.size(); i++)
	{
		// Check type of enemy
		// Check state of enemy
		// Run
	}
}
