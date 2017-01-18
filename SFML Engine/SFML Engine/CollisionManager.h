/*! \brief Handles all collision between each entity.
*
*
*
*/
#pragma once
#include "Player.h"
#include "nest.h"
#include "Bullet.h"
#include "Obstacle.h"
#include "Alien.h"
#include "Astronaut.h"
#include "Mutant.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void checkCollision(Player * player, std::vector<Bullet*> *bullets, std::vector<Obstacle*> *gasClouds,
		std::vector<Obstacle*> *healthPacks, std::vector<Nest*> *nests, std::vector<Alien*> *aliens, 
			std::vector<Astronaut*> *astronauts, std::vector<Mutant*> *mutants);/*!< Checks collision for all entities including "Player, Nets, Mutant, Obstacle, Bullet and Alien*/
};

