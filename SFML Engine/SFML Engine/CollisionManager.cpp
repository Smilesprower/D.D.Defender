#include "stdafx.h"
#include "CollisionManager.h"
#include "Obstacle.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::checkCollision(Player *player, std::vector<Bullet*> bullets, std::vector<Obstacle*> gasClouds, std::vector<Nest*> nests)
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
				bullets[i]->setTTL(5);
				player->setDamage(100);
			}
		}
		// if its a lazer
		else if (bullets[i]->isEnabled() && bullets[i]->getType() == bullets[i]->Lazer)
		{
			// if bullet collides with a nest enemy
			for (int j = 0; j < nests.size(); j++)
			{
				if (nests[j]->isAlive())
				{
					int dx = bullets[i]->getPosition().x - nests[j]->getPosition().x;
					int dy = bullets[i]->getPosition().y - nests[j]->getPosition().y;
					int distanceSquared = (dx*dx) + (dy*dy);
					if (distanceSquared < ((bullets[i]->getRadius() + nests[j]->getRadius()) * (bullets[i]->getRadius() + nests[j]->getRadius())))
					{
						bullets[i]->setEnabled(false);
						nests[j]->setDamage(20);
					}
				}
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
			player->setDamage(1);
		}
	}



}
