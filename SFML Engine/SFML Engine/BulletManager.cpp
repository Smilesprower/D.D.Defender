#include "stdafx.h"
#include "BulletManager.h"

BulletManager * BulletManager::m_inst = nullptr;
BulletManager::BulletManager()
{
}
BulletManager::~BulletManager()
{
}
BulletManager * BulletManager::Instance()
{
	if (!m_inst)
	{
		m_inst = new BulletManager();
	}
	return m_inst;
}

void BulletManager::init(sf::Texture tex, int MAX_BULLETS)
{
	m_tex = tex;
	m_maxBullets = MAX_BULLETS;
	for (int i = 0; i < m_maxBullets; i++)
	{
		m_bullets.push_back(new Bullet(m_tex));
	}
}

void BulletManager::update(sf::Time deltaTime)
{
	// Check if the bullet is enabled
	for (int i = 0; i < m_maxBullets; i++)
	{
		if (m_bullets[i]->getType() == Missile)
		{
		}
		else
		{
			m_bullets.at(i)->update(deltaTime);
		}
	}
}

bool BulletManager::createLaser(sf::Vector2f pos, float xSpeed, int direction, int type, bool playerBullet)
{
	for (int i = 0; i < m_maxBullets; i++)
	{
		if (!m_bullets.at(i)->isEnabled())
		{
			m_bullets.at(i)->setUpBullet(pos, xSpeed, direction, type, playerBullet);
			return true;
		}
	}
	return false;
}

std::vector<Bullet*> BulletManager::getBullets()
{
	return m_bullets;
}
