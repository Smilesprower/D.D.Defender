#pragma once
#include "Bullet.h"

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
	void update(sf::Time deltaTime, sf::Vector2f xScreenBounds);
	void fireMissile();
	void createLaser(sf::Vector2f pos, int direction, int type, bool playerBullet);
	std::vector<Bullet*> getBullets();

private:
	static BulletManager *m_inst;

	// Disallow Copying
	BulletManager(const BulletManager&);
	BulletManager& operator=(const BulletManager&);

	BulletManager();
	~BulletManager();

	sf::Texture m_tex;
	int m_maxBullets;
	std::vector<Bullet*> m_bullets;
};

