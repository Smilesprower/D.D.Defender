/*! \brief Handles all the properties of the bullet, and sets up each type of bullet.
*
*
*
*/
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
	void setUpEBullet(sf::Vector2f position, sf::Vector2f targetPosition, int type, bool playerBullet);		/*!< Set up Alien and Mutant bullets*/
	void setUpBullet(sf::Vector2f position, float xSpeed, int direction, int type, bool playerBullet);		/*!< Set up player bullet*/
	void setUpMissile(sf::Vector2f position, sf::Vector2f playerPos, int type);								/*!< Set up Nest Missile*/
	void update(sf::Time deltaTime, sf::Vector2f playerPos, int &missleCount);								/*!< Update all bullets*/
	void setPosition(sf::Vector2f position);																/*!< Set bullet position*/
	sf::Vector2f getPosition();																				/*!< Get bullet position*/
	bool isEnabled();																						/*!< Returns is bullet active*/
	void setEnabled(bool);																					/*!< Sets if bullet is active*/
	int getType();																							/*!< Returns bullet type*/
	void setTTL(int ttl);																					/*!< Set bullets Time to Live*/
	int getRadius();																						/*!< Gets bullets collision radius/bounds*/
	void reset();																							/*!< Resets bullet to be used again as different types*/
	AnimatedSprite draw();																					/*!< Returns bullet sprite to be drawn*/
	sf::CircleShape drawMissileCollider();

private:

	const float MAX_ROTATION = 2.f;							/*!< Number of frames for explosion animation*/							
	const int MAX_FRAMES_EXPLOSION = 3;						/*!< Max missile speed*/
	const int MISSILE_SPEED = 350;							/*!< Max bullet speed*/
	const int BULLET_SPEED = 1000;							/*!< Bullets time to live as seconds*/
	const int BULLET_TTL = 2;								/*!< Missiles time to live as seconds*/
	const int MISSILE_TTL = 5;								/*!< Missiles collision radius/bounds*/
	const int MISSILE_RADIUS = 20;							/*!< Number of frames for explosion animation*/
	const int NUM_OF_EXP_FRAMES = 8;						/*!< Angle to Rads converter*/
	const double ANGLE_TO_RADS = 180 / (atan(1) * 4);		/*!< Number of bullet animations*/
	const int NUM_OF_ANIMS = 6;

	int m_type;					/*!< Contains current type*/
	int m_speed;				/*!< Contains current speed*/
	int m_direction;			/*!< Contains current direction "Player only"*/
	bool m_enabled;				/*!< Contains bullet enabled*/
	bool m_playerBullet;		/*!< Is the bullet from the player state*/
	float m_ttl;				/*!< Contains bullets time to live*/							
	sf::Vector2f m_velocity;    /*!< Contains velocity*/
	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;

	sf::CircleShape m_missileCollider;
};