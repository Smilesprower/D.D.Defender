/*! \brief Handles all the properties of the Abductor.
*
*
*
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "BulletManager.h"
#include "Astronaut.h"
#include "Obstacle.h"
#include "Helper.h"

class Alien
{
public:
	enum Anims		/*!< Enum for Animation types*/
	{
		Default,
		Explode,
		Abduct,
	};
	enum State		/*!< Enum for Enemy States*/
	{
		Blank,
		Target,
		Capture,
		Flock,
		Dying,
	};

	Alien(sf::Texture & tex, sf::Vector2i screenBounds, sf::Vector2i worldBounds);
	~Alien();
	void init(sf::Vector2f position);


	sf::Vector2f separation(std::vector<Alien*> *alien, std::vector<Obstacle*> *obstacle, sf::Vector2f playerPos, int index);	 /*!< Seperation function for flocking*/
	sf::Vector2f alignment(std::vector<Alien*>* alien, int index);	/*!< Alignment function for flocking*/
	sf::Vector2f cohesion(std::vector<Alien*> *alien, int index);	/*!< Cohesion function for flocking*/

	bool run(std::vector<Alien*> *alien, std::vector<Obstacle*> *obstacle, sf::Time deltaTime, sf::Vector2f playerPos, int index); /*!< Handles update for differen Alien states*/
	void updateFlock(sf::Time deltaTime, sf::Vector2f playerPos);	/*!< Updates Flocking state*/
	bool updateTargetCapture(sf::Time dt);							/*!< Updates Target and Capture state*/				
	void updateDying(sf::Time dt);									/*!< Updates Dying state*/
	void borders();													/*!< Checks boundaries for Alien while in flocking state*/
	void flock(std::vector<Alien*> *alien, std::vector<Obstacle*> *obstacle, sf::Vector2f playerPos, int index);	/*!< Updates each of the 3 flocking functions "Cohesion, Speration, Alignment*/

	bool getAlive();				/*!< Returns Aliens alive status*/
	void setAlive(bool alive);		/*!< Sets Aliens alive status*/

	int getState();					/*!< Returns Aliens current state*/
	void setState(int state);		/*!< Sets Aliens current state*/

	int getRadius();				/*!< Returns Aliens radius/bounds*/
	int getAbductRadius();			/*!< Returns Aliens abduction radius/bounds*/

	void setDamage(int damage);		/*!< Sets Aliens health based on damage value passed in*/
	int getHealth();				/*!< Returns Aliens health*/

	sf::Vector2f getPosition();					/*!< Returns Aliens position*/
	void setPosition(sf::Vector2f position);	/*!< Sets Aliens position*/
	void setAstro(Astronaut* astro);			/*!< Sets Aliens astronaut pointer to the current astronaut its pursuing*/
	AnimatedSprite draw();						/*!< Returns Aliens sprite ready to be drawn*/

	void checkBounds();							/*!< Check Aliens screen bounds and repositions*/
	int getCurrentState();						/*!< Returns current state of Alien*/

private:
	// AI SHTUFF
	///////////////////////////////////
	sf::Vector2f m_position;					/*!<Contains Alien position*/
	sf::Vector2f m_velocity;					/*!<Contains Alien velocity*/

	sf::Vector2i m_screenBounds;				/*!<Contains Screen bounds 0 - 1980*/
	sf::Vector2i m_worldBounds;					/*!<Contains World Bounds bounds -1920 - 15630*/
	///////////////////////////////////
	const int BULLET_COOLDOWN_TIMER = 2;		/*!<Time before Alien can shoot again*/
	const int BULLET_RANGE = 700;				/*!<Range player has to be less than before aAlien will shoot*/
	float m_bulletReloadTimer;					/*!<Contains total time Alien has been reloading for*/

	int m_health;								/*!<Contains Alien health*/
	const int RADIUS = 50;						/*!<Aliens collision radius/bounds*/
	const int ABDUCT_RADIUS = 400;				/*!<Aliens abduction radius/bounds "Distance an Alien must < in order to abduct astronaut"*/
	const int TARGET_SPEED = 200;				/*!<Speed at which Alien velocity is multiplied by when targeting astronauts*/
	bool m_alive;								/*!<Contains Aliens alive state*/
	int m_currentState;							/*!<Contains current Alien state*/
	int NUM_OF_ANIMS = 3;						/*!<Number of Animations Alien has*/
	Astronaut * m_astro;						/*!<Contains pointer to an astronaut */
	sf::Time m_frameTime;						
	AnimatedSprite m_animatedSprite;			
	std::vector<Animation> m_animations;		
	Animation* m_currAnimation;					

};

