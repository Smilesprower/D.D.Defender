#pragma once
#include "AnimatedSprite.h"
#include "BulletManager.h"
class Mutant
{
public:
	enum Anims
	{
		Default,
		Explode,
	};
	enum States
	{
		Start, 
		Seek,
		FormationA,
		FormationB,
		FormationC,
	};

	Mutant(sf::Texture & tex, sf::Vector2i screenBounds, sf::Vector2i worldBounds);
	~Mutant();

	void update(sf::Time deltaTime, sf::Vector2f playerPos);
	void init(sf::Vector2f pos);
	void checkBounds();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	AnimatedSprite draw();

	void setDamage(int damage);
	int getHealth();
	int getRadius();
	bool isAlive();
	void setAlive(bool alive);


private:
	int NUM_OF_ANIMS = 3;
	const int COLLISION_RADIUS = 150;
	const int BULLET_COOLDOWN_TIMER = 2;
	const int BULLET_RANGE = 700;
	float m_bulletReloadTimer;
	int m_health;
	bool m_alive;
	int m_state;
	sf::Vector2i m_screenBounds;
	sf::Vector2i m_worldBounds;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
};

