#pragma once
#include "AnimatedSprite.h"
#include "Helper.h"
#include <SFML\Graphics.hpp>

class Bullet
{
	enum Type
	{
		Default,
		Lazer,
		Missile,
		Explosion
	};

public:
	Bullet();
	~Bullet();
	void init(sf::Texture & tex);
	void setUpBullet(sf::Vector2f position, int direction, int type, bool playerBullet);
	void setUpMissile(sf::Vector2f position, sf::Vector2f playerPos, int type);
	void update(sf::Time deltaTime, sf::Vector2f playerPos);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	bool isAlive();
	void collided(bool);
	int getType();
	AnimatedSprite draw();

private:
	const float MAX_ROTATION = 2.f;
	int x = 0;
	const int MAX_FRAMES_EXPLOSION = 3;
	const int MISSILE_SPEED = 500;
	const int BULLET_SPEED = 500;
	const int MISSILE_TTL = 40;
	const int NUM_OF_EXP_FRAMES = 8;
	const double ANGLE_TO_RADS = 180 / (atan(1) * 4);
	const int NUM_OF_ANIMS = 4;


	int m_type;
	int m_speed;
	int m_direction;
	bool m_alive;
	bool m_playerBullet;
	float m_ttl;
	float m_rotation;
	float m_prevRotation;


	sf::Vector2f m_velocity;

	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
};

