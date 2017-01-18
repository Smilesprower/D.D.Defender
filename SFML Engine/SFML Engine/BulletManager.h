/*! \brief This contains a reference to every bullet and is responsible for their generation.
*
*
*
*/
#pragma once
#include "Bullet.h"
#include <iostream>

class BulletManager
{
public:

	enum BulletType {
		Default,
		Lazer,
		Missile,
		Explosion,
		Ball,
	};

	static BulletManager * Instance();

	void init(sf::Texture tex, int maxBullets);
	void update(sf::Time deltaTime, sf::Vector2f playerPos);
	bool createMissile(sf::Vector2f position, sf::Vector2f playerPos, int type);
	bool createLaser(sf::Vector2f pos, float xSpeed, int direction, int type, bool playerBullet);
	bool createEBullet(sf::Vector2f pos, sf::Vector2f playerPos, int type, bool playerBullet);
	void resetBullets();
	std::vector<Bullet*> getBullets();

private:
	static BulletManager *m_inst;

	const int MAX_MISSILES = 2;
;

	// Disallow Copying
	BulletManager(const BulletManager&);
	BulletManager& operator=(const BulletManager&);

	BulletManager();
	~BulletManager();

	sf::Texture m_tex;
	int m_maxBullets;
	int m_missileCount;
	std::vector<Bullet*> m_bullets;
};

