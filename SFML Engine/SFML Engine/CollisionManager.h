#pragma once
#include "Player.h"
#include "nest.h"
#include "Bullet.h"
#include "Obstacle.h"
#include "Alien.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void checkCollision(Player * player, std::vector<Bullet*> *bullets, std::vector<Obstacle*> *gasClouds, std::vector<Nest*> *nests, std::vector<Alien*> *aliens);
};

