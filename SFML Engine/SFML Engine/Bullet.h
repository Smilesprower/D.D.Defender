#pragma once
#include "AnimatedSprite.h"
#include "Helper.h"
#include <SFML\Graphics.hpp>

class Bullet
{
public:
	enum Type
	{
		Default,
		Lazer,
		Missile,
		Explosion,
		Ball,
		Ball2
	};

	Bullet(sf::Texture & tex);
	Bullet();
	~Bullet();
	void setUpEBullet(sf::Vector2f position, sf::Vector2f targetPosition, int type, bool playerBullet);
	void setUpBullet(sf::Vector2f position, float xSpeed, int direction, int type, bool playerBullet);
	void setUpMissile(sf::Vector2f position, sf::Vector2f playerPos, int type);
	void update(sf::Time deltaTime, sf::Vector2f playerPos, int &missleCount);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	bool isEnabled();
	void setEnabled(bool);
	void collided(bool);
	int getType();
	void setTTL(int ttl);
	int getRadius();
	void reset();
	AnimatedSprite draw();
	sf::CircleShape drawMissileCollider();

private:
	const float MAX_ROTATION = 2.f;
	const int MAX_FRAMES_EXPLOSION = 3;
	const int MISSILE_SPEED = 350;
	const int BULLET_SPEED = 1000;
	const int BULLET_TTL = 2;
	const int MISSILE_TTL = 5;
	const int MISSILE_RADIUS = 20;
	const int NUM_OF_EXP_FRAMES = 8;
	const double ANGLE_TO_RADS = 180 / (atan(1) * 4);
	const int NUM_OF_ANIMS = 6;

	int m_type;
	int m_speed;
	int m_direction;
	bool m_enabled;
	bool m_playerBullet;
	float m_ttl;
	float m_rotation;
	float m_prevRotation;


	sf::Vector2f m_velocity;
	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;

	sf::CircleShape m_missileCollider;
};

