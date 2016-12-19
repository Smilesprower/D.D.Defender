#include "stdafx.h"
#include "CollisionManager.h"
#include "Obstacle.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::checkCollision(Player *player, std::vector<Bullet*> bullets, std::vector<Obstacle*> gasClouds)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		// If its a missile
		if(bullets[i]->isEnabled() && bullets[i]->getType() == bullets[i]->Missile)
		{
			int dx = player->getPosition().x - bullets[i]->getPosition().x;
			int dy = player->getPosition().y - bullets[i]->getPosition().y;
			int distanceSquared = (dx*dx) + (dy*dy);
			if (distanceSquared < (player->getRadius() + bullets[i]->getRadius()) * (player->getRadius() + bullets[i]->getRadius()))
			{
				// Collision
				bullets[i]->setTTL(5);
				// Minus player health
				player->setDamage(100);
				// Set player state to explode
				// game over after explosion

			}
		}
	}

	for (int i = 0; i < gasClouds.size(); i++)
	{
		int dx = player->getPosition().x - gasClouds[i]->getPosition().x;
		int dy = player->getPosition().y - gasClouds[i]->getPosition().y;
		int distanceSquared = (dx*dx) + (dy*dy);
		if (distanceSquared < ((player->getRadius() + gasClouds[i]->getRadius()) * (player->getRadius() + gasClouds[i]->getRadius())))
		{
			// Minus player health
			player->setDamage(10);
			// Set player state to explode
			// game over after explosion

		}
	}

}
