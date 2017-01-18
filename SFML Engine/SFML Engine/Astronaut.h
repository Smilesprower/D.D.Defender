/*! \brief Handles all the properties of the astronaut.
*
*
*
*/
#pragma once
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"


class Astronaut
{
public:
	enum Anims			/*!< Enum for Animation types*/
	{
		WalkLeft,
		WalkRight,
		Falling_Abducted,
	};
	enum State			/*!< Enum for States*/
	{
		Flee,
		Wander,
		Falling,
		Abducted
	};

	Astronaut(sf::Texture & tex, int xPos);
	~Astronaut();

	void init(sf::Vector2f pos);					/*!< Initialise ready for the current game*/
	void update(sf::Time deltaTime);				/*!<Update*/
	sf::Vector2f getPosition();						/*!< Returns position*/
	sf::Vector2f getAbductPosition();				/*!< Returns abduction position*/
	void setPosition(sf::Vector2f position);		/*!<Sets position*/
	AnimatedSprite draw();							/*!< Returns sprite ready to be drawn*/

	void setAbducted();								/*!<Sets currentstate to abducted*/
	int getState();									/*!<Gets currentstate*/
	void setTargeted(bool targeted);				/*!<Sets targeted*/
	bool isTargeted();								/*!<Gets targeted*/
	int getRadius();								/*!<Gets collision radius/bounds*/
	void setFalling();								/*!<Sets current state to falling*/
	void setAlive(bool alive);						/*!<Sets is alive*/
	bool isAlive();									/*!<Gets is alive*/


private:
	bool m_targeted;								/*!<Contains targeted state*/
	bool m_alive;									/*!<Contains alive state*/
	int m_direction;								/*!<Contains current direction*/
	int m_state;									/*!<Contains current state*/
	sf::Vector2f m_velocity;						/*!<Contains current velocity*/
	sf::Vector2f m_abductPos;						/*!<Contains current abductPosition "Alien uses this position"*/

	int GROUND = 925;								/*!<Astros ground collision value */
	int RADIUS = 25;								/*!<Collision radius/ounds*/
	int GRAVITY = 100;								/*!<Fall Speed*/
	int MAX_SPEED = 2000;							/*!<Walking Speed*/
	int NUM_OF_ANIMS = 3;							/*!<Number of animations*/
	int MAX_ABDUCTED_SPEED = -100;					/*!<Speeds which Astro is adbucted at*/
	const int TIME_TO_SWITCH_DIRECTION = 10;		
	float m_wanderTime;								/*!<Contains current time wandering*/
	sf::Vector2f m_abductedVelocity;				/*!<Contains abduction velocity*/

	sf::Time m_frameTime;
	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
};