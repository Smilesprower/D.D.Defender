/*! \brief Handles all the properties and responsibilities of the Nest.
*
*
*
*/

#pragma once
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"
#include "BulletManager.h"

class Nest
{
	enum Anims
	{
		Default,
		Explode,
		Electricity,
	};
	enum States
	{
		Wander,				/*!<Randomly wanders around the world spawning alien abductors*/
		Evade,				/*!<Evades when player gets to close and shoots missile if player gets even closer*/
		Dying,
	};
	enum Direction
	{
		Left = -1,
		Right = 1,
	};

public:
	Nest(sf::Texture & tex, sf::Vector2i screenBounds);
	~Nest();
	bool update(sf::Time deltaTime, sf::Vector2f playerPos);		/*!<Update function for the nest*/
	void init(sf::Vector2f pos);									/*!<Initialises nest for for the game*/
	void checkBounds();												/*!<Checks boundaries*/
	sf::Vector2f getPosition();										/*!<Return current positions*/
	void setPosition(sf::Vector2f position);						/*!<Sets current position*/
	AnimatedSprite draw();											/*!<Returns sprite for drawing*/
	AnimatedSprite drawElectricity();								/*!<Returns sprite for drawing*/
	sf::CircleShape drawEvade();									
	sf::CircleShape drawFire();										
																	
	int getState();													/*!<Returns current state*/
	void setDamage(int damage);										/*!<Sets current health of nest with damage taken from it*/
	int getHealth();												/*!<Returns current health*/
	int getRadius();												/*!<Returns collision radius/bounds*/
	bool isAlive();													/*!<Returns alive state*/
	void setAlive(bool alive);										/*!<Sets alive state*/

private:
	const int COOLDOWN_TIMER = 10;				/*!<Time in seconds before nest can shoot again*/
	const int NUM_OF_ANIMS = 2;					/*!<Number of animations*/
	const int MAX_VELOCITY = 200;				/*!<Max velocity*/
	const int MAX_EVADE_VELOCITY = 300;			/*!<Max velocity while evading*/
	const int MAX_HEALTH = 500;					/*!<Max health*/
	const int TIME_TO_SWITCH_DIRECTION = 10;	/*!<time in seconds before switching direction*/
	const int MISSILE_RANGE = 750;				/*!<Distance Player must be with in before firing missile*/
	const int EVADE_RANGE = 1000;				/*!< Distance Player must be within before changing state to evade*/
	const int NEST_RADIUS = 150;				/*!<Initialises nest for for the game*/
												
	float m_missileReloadTimer;				
	float m_wanderTime;							
	int m_health;							
	bool m_alive;								
	int m_state;
	int m_direction;
	float m_spawnTimer;
	sf::Vector2i m_screenBounds;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	sf::CircleShape m_missileRadius;
	sf::CircleShape m_evadeRadius;

	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	AnimatedSprite m_animatedSprite1;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
	std::vector<Animation> m_animations1;
	Animation* m_currAnimation1;
};

