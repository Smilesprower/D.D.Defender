#include "stdafx.h"
#include "CollisionManager.h"
#include "Obstacle.h"
#include "Alien.h"
#include "Astronaut.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::checkCollision(Player *player, std::vector<Bullet*> *bullets, std::vector<Obstacle*> *gasClouds, std::vector<Obstacle*> *healthPacks, std::vector<Nest*> *nests, std::vector<Alien*> *aliens, std::vector<Astronaut*> *astronauts, std::vector<Mutant*> *mutants)
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
		// If its a alien bullet
		if (bullets->at(i)->isEnabled() && (bullets->at(i)->getType() == bullets->at(i)->Ball  || bullets->at(i)->getType() == bullets->at(i)->Ball2))
		{
			int dx = player->getPosition().x - bullets->at(i)->getPosition().x;
			int dy = player->getPosition().y - bullets->at(i)->getPosition().y;
			int distanceSquared = (dx*dx) + (dy*dy);
			if (distanceSquared < (player->getRadius() + bullets->at(i)->getRadius()) * (player->getRadius() + bullets->at(i)->getRadius()))
			{
				bullets->at(i)->setEnabled(false);
				player->setDamage(10);
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

			// if bullet collides with a mutant enemy
			for (int j = 0; j < mutants->size(); j++)
			{
				if (mutants->at(j)->isAlive())
				{
					int dx = bullets->at(i)->getPosition().x - mutants->at(j)->getPosition().x;
					int dy = bullets->at(i)->getPosition().y - mutants->at(j)->getPosition().y;
					int distanceSquared = (dx*dx) + (dy*dy);
					if (distanceSquared < ((bullets->at(i)->getRadius() + mutants->at(j)->getRadius()) * (bullets->at(i)->getRadius() + mutants->at(j)->getRadius())))
					{
						bullets->at(i)->setEnabled(false);
						mutants->at(j)->setDamage(10);
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
	for (int i = 0; i < healthPacks->size(); i++)
	{
		if (healthPacks->at(i)->isEnabled() == true)
		{
			int dx = player->getPosition().x - healthPacks->at(i)->getPosition().x;
			int dy = player->getPosition().y - healthPacks->at(i)->getPosition().y;
			int distanceSquared = (dx*dx) + (dy*dy);
			if (distanceSquared < ((player->getRadius() + healthPacks->at(i)->getRadius()) * (player->getRadius() + healthPacks->at(i)->getRadius())))
			{
				player->setDamage(-25);
				healthPacks->at(i)->setEnabled(false);

			}
		}
			
	}
	for (int i = 0; i < aliens->size(); i++)
	{
		// Check if the alien isn't mid explosion
		if (aliens->at(i)->getCurrentState() != 4 && aliens->at(i)->getAlive())
		{
			int dx = player->getPosition().x - aliens->at(i)->getPosition().x;
			int dy = player->getPosition().y - aliens->at(i)->getPosition().y;
			int distanceSquared = (dx*dx) + (dy*dy);
			if (distanceSquared < ((player->getRadius() + aliens->at(i)->getRadius()) * (player->getRadius() + aliens->at(i)->getRadius())))
			{
				player->setDamage(50);
				aliens->at(i)->setDamage(100);
			}
		}
	}
	for (int i = 0; i < nests->size(); i++)
	{
		if (nests->at(i)->isAlive())
		{
			int dx = player->getPosition().x - nests->at(i)->getPosition().x;
			int dy = player->getPosition().y - nests->at(i)->getPosition().y;
			int distanceSquared = (dx*dx) + (dy*dy);
			if (distanceSquared < ((player->getRadius() + nests->at(i)->getRadius()) * (player->getRadius() + nests->at(i)->getRadius())))
			{
				player->setDamage(100);
				nests->at(i)->setDamage(20);
			}
		}
	}
	for (int i = 0; i < mutants->size(); i++)
	{
		if (mutants->at(i)->getCurrentState() != 1 && mutants->at(i)->isAlive())
		{
			int dx = player->getPosition().x - mutants->at(i)->getPosition().x;
			int dy = player->getPosition().y - mutants->at(i)->getPosition().y;
			int distanceSquared = (dx*dx) + (dy*dy);
			if (distanceSquared < ((player->getRadius() + mutants->at(i)->getRadius()) * (player->getRadius() + mutants->at(i)->getRadius())))
			{
				player->setDamage(50);
				mutants->at(i)->setDamage(100);
			}
		}

	}
	for (int i = 0; i < astronauts->size(); i++)
	{
		for (int j = 0; j < aliens->size(); j++)
		{
			if (aliens->at(j)->getAlive())
			{
				int dx = astronauts->at(i)->getPosition().x - aliens->at(j)->getPosition().x;
				int dy = astronauts->at(i)->getPosition().y - aliens->at(j)->getPosition().y;
				int distanceSquared = (dx*dx) + (dy*dy);
				if (distanceSquared < ((astronauts->at(i)->getRadius() + aliens->at(j)->getAbductRadius()) * (astronauts->at(i)->getRadius() + aliens->at(j)->getAbductRadius())))
				{
					// If astro is not targeted
					if (!astronauts->at(i)->isTargeted())
					{
						aliens->at(j)->setState(aliens->at(j)->Target);
						aliens->at(j)->setAstro(astronauts->at(i));
						astronauts->at(i)->setTargeted(true);
					}
				}
			}
		}
	}

	//	PLAYER BOUNDRIES
	if (player->getPosition().y < 0)
	{
		sf::Vector2f temp;
		temp.x = player->getPosition().x;
		temp.y = 0;
		player->setPosition(temp);
	}
	else if (player->getPosition().y > 900)
	{
		sf::Vector2f temp;
		temp.x = player->getPosition().x;
		temp.y = 900;
		player->setPosition(temp);
	}


}
