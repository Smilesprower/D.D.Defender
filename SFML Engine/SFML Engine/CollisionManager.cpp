#include "stdafx.h"
#include "CollisionManager.h"
#include "Obstacle.h"
#include "Alien.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::checkCollision(Player *player, std::vector<Bullet*> *bullets, std::vector<Obstacle*> *gasClouds, std::vector<Nest*> *nests, std::vector<Alien*> *aliens)
{
	for (int i = 0; i < bullets->size(); i++)
	{
		// If its a missile
		if(bullets->at(i)->isEnabled() && bullets->at(i)->getType() == bullets->at(i)->Missile)
		{
			int dx = player->getPosition().x - bullets->at(i)->getPosition().x;
			int dy = player->getPosition().y - bullets->at(i)->getPosition().y;
			int distanceSquared = (dx*dx) + (dy*dy);
			if (distanceSquared < (player->getRadius() + bullets->at(i)->getRadius()) * (player->getRadius() + bullets->at(i)->getRadius()))
			{
				bullets->at(i)->setTTL(5);
				player->setDamage(100);
			}
		}
		// if its a lazer
		else if (bullets->at(i)->isEnabled() && bullets->at(i)->getType() == bullets->at(i)->Lazer)
		{
			// if bullet collides with a nest enemy
			for (int j = 0; j < nests->size(); j++)
			{
				if (nests->at(j)->isAlive())
				{
					int dx = bullets->at(i)->getPosition().x - nests->at(j)->getPosition().x;
					int dy = bullets->at(i)->getPosition().y - nests->at(j)->getPosition().y;
					int distanceSquared = (dx*dx) + (dy*dy);
					if (distanceSquared < ((bullets->at(i)->getRadius() + nests->at(j)->getRadius()) * (bullets->at(i)->getRadius() + nests->at(j)->getRadius())))
					{
						bullets->at(i)->setEnabled(false);
						nests->at(j)->setDamage(20);
					}
				}
			}

			// if bullet collides with a nest enemy
			for (int j = 0; j < aliens->size(); j++)
			{
				if (aliens->at(j)->getAlive())
				{
					int dx = bullets->at(i)->getPosition().x - aliens->at(j)->getPosition().x;
					int dy = bullets->at(i)->getPosition().y - aliens->at(j)->getPosition().y;
					int distanceSquared = (dx*dx) + (dy*dy);
					if (distanceSquared < ((bullets->at(i)->getRadius() + aliens->at(j)->getRadius()) * (bullets->at(i)->getRadius() + aliens->at(j)->getRadius())))
					{
						bullets->at(i)->setEnabled(false);
						aliens->at(j)->setDamage(20);
					}
				}
			}
		}
	}

	for (int i = 0; i < gasClouds->size(); i++)
	{
		int dx = player->getPosition().x - gasClouds->at(i)->getPosition().x;
		int dy = player->getPosition().y - gasClouds->at(i)->getPosition().y;
		int distanceSquared = (dx*dx) + (dy*dy);
		if (distanceSquared < ((player->getRadius() + gasClouds->at(i)->getRadius()) * (player->getRadius() + gasClouds->at(i)->getRadius())))
		{
			player->setDamage(1);
		}
	}



}
