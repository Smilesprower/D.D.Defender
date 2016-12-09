#include "stdafx.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::checkCollision(Player *player, std::vector<Bullet*> bullets)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		// If its a missile
		if(bullets[i]->isEnabled() && bullets[i]->getType() == bullets[i]->Missile)
		{
			int dx = player->getPosition().x - bullets[i]->getPosition().x;
			int dy = player->getPosition().y - bullets[i]->getPosition().y;
			int distanceSquared = (dx*dx) + (dy*dy);
			if (distanceSquared < player->getRadius() * bullets[i]->getRadius())
			{
				// Collision
				bullets[i]->setTTL(5);
				// Minus player health
			}
		}
	}

}
