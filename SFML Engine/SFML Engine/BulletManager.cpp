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

void BulletManager::update(sf::Time deltaTime, sf::Vector2f xScreenBounds)
{
	// Check if the bullet is enabled
	for (int i = 0; i < m_maxBullets && m_bullets.at(i)->isEnabled(); i++)
	{
		if (m_bullets[i]->getType() == Missile)
		{
		}
		else
		{
			m_bullets.at(i)->update(deltaTime);
		}
		if (m_bullets.at(i)->getPosition().x < xScreenBounds.x || m_bullets.at(i)->getPosition().x > xScreenBounds.y)
		{
			m_bullets.at(i)->setEnabled(false);
		}
	}
}

void BulletManager::createLaser(sf::Vector2f pos, int direction, int type, bool playerBullet)
{
	for (int i = 0; i < m_maxBullets; i++)
	{
		if (!m_bullets.at(i)->isEnabled())
		{
			m_bullets.at(i)->setUpBullet(pos, direction, type, playerBullet);
			break;
		}
	}
}

std::vector<Bullet*> BulletManager::getBullets()
{
	return m_bullets;
}
