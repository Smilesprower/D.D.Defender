/*! \brief Handles all the properties of the Mutant.
*
*
*
*/

#pragma once
#include "AnimatedSprite.h"
#include "BulletManager.h"

#include <math.h>

class Mutant
{
public:
	enum Anims
	{
		Default,
		Explode,
	};	
	enum States					/*!< Enum for current mutant state*/
	{
		Start,					/*!< Starting state moves mutant downwards into game world */
		Dying,
		FormationA,				/*!< Unused State "time issues" */
		FormationB,				/*!< Swarming with circle formation around the Player*/
		FormationC,				/*!< Kamikazee */
	};
	
	Mutant(sf::Texture & tex, sf::Vector2i screenBounds, sf::Vector2i worldBounds);
	~Mutant();

	void update(int mutantSize, int currentMutant, sf::Time deltaTime, sf::Vector2f playerPos, sf::Vector2f playerVel); /*!< Updates mutant based on current state */
	void init(sf::Vector2f pos);																						/*!< Initialise ready for the current game*/
	void checkBounds();																									/*!< Check out of bounds*/
	sf::Vector2f getPosition();																							/*!< Returns current position*/
	void setPosition(sf::Vector2f position);																			/*!< Sets current position*/
	AnimatedSprite draw();																								/*!< Retuns sprite ready to be drawn*/
	void setDamage(int damage);																							/*!< Set damage to current health*/
	int getHealth();																									/*!< Returns current health*/
	int getRadius();																									/*!< Returns collision radius*/
	bool isAlive();																										/*!< Returns is alive*/
	void setAlive(bool alive);																							/*!< Sets if mutant is alive*/
	int getCurrentState();																								/*!< Returns current state*/

private:
	
	int NUM_OF_ANIMS = 3;							/*!<Max number of animations*/
	const float MAX_VELOCITY = 550.0f;				/*!<Max velocity*/
	const int COLLISION_RADIUS = 50;				/*!<Collision radius/bounds*/
	const int BULLET_COOLDOWN_TIMER = 2;			/*!<Time before shooting another Bullet in seconds*/
	const int BULLET_RANGE = 700;					/*!<Max range a Player has to be less than before firing a Bullet*/
	float m_bulletReloadTimer;						/*!<Contains current reloading time*/		
	int m_health;									/*!<Contains current health*/
	bool m_alive;									/*!<Contains current alive state*/
	int m_state;									/*!<Contains current state*/
	sf::Vector2i m_screenBounds;					/*!<Contains current screenbounds*/
	sf::Vector2i m_worldBounds;						/*!<Contains current worldbounds*/
	sf::Vector2f m_velocity;						/*!<Contains current velocity*/
	sf::Vector2f m_position;						/*!<Contains current position*/

	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
};

