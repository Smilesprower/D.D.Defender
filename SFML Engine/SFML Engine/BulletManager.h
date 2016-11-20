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
	};

	static BulletManager * Instance();

	void init(sf::Texture tex, int maxBullets);
	void update(sf::Time deltaTime);
	void fireMissile();
	bool createLaser(sf::Vector2f pos, float xSpeed, int direction, int type, bool playerBullet);
	std::vector<Bullet*> getBullets();

private:
	static BulletManager *m_inst;

	// Disallow Copying
	BulletManager(const BulletManager&);
	BulletManager& operator=(const BulletManager&);

	BulletManager();
	~BulletManager();

	sf::Texture m_tex;
	int m_bulletCount;
	int m_maxBullets;
	std::vector<Bullet*> m_bullets;
};

