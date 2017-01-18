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
	enum State		/*!< Enum for States*/
	{
		Blank,
		Target,
		Capture,
		Flock,
		Dying,
	};

	Alien(sf::Texture & tex, sf::Vector2i screenBounds, sf::Vector2i worldBounds);
	~Alien();
	void init(sf::Vector2f position);		/*!< Initialise ready for th current game*/


	sf::Vector2f separation(std::vector<Alien*> *alien, std::vector<Obstacle*> *obstacle, sf::Vector2f playerPos, int index);	 /*!< Seperation function for flocking*/
	sf::Vector2f alignment(std::vector<Alien*>* alien, int index);	/*!< Alignment function for flocking*/
	sf::Vector2f cohesion(std::vector<Alien*> *alien, int index);	/*!< Cohesion function for flocking*/

	bool run(std::vector<Alien*> *alien, std::vector<Obstacle*> *obstacle, sf::Time deltaTime, sf::Vector2f playerPos, int index); /*!< Handles update for differen Alien states*/
	void updateFlock(sf::Time deltaTime, sf::Vector2f playerPos);	/*!< Updates Flocking state*/
	bool updateTargetCapture(sf::Time dt);							/*!< Updates Target and Capture state*/				
	void updateDying(sf::Time dt);									/*!< Updates Dying state*/
	void borders();													/*!< Checks boundaries for Alien while in flocking state*/
	void flock(std::vector<Alien*> *alien, std::vector<Obstacle*> *obstacle, sf::Vector2f playerPos, int index);	/*!< Updates each of the 3 flocking functions "Cohesion, Speration, Alignment*/

	bool getAlive();				/*!< Returns alive state*/
	void setAlive(bool alive);		/*!< Sets alive state*/

	int getState();					/*!< Returns current state*/
	void setState(int state);		/*!< Sets current state*/

	int getRadius();				/*!< Returns radius/bounds*/
	int getAbductRadius();			/*!< Returns abduction radius/bounds*/

	void setDamage(int damage);		/*!< Sets health based on damage value passed in*/
	int getHealth();				/*!< Returns Alien health*/

	sf::Vector2f getPosition();					/*!< Returns position*/
	void setPosition(sf::Vector2f position);	/*!< Sets position*/
	void setAstro(Astronaut* astro);			/*!< Sets astronaut pointer to the current Astronaut its pursuing*/
	AnimatedSprite draw();						/*!< Returns sprite ready to be drawn*/

	void checkBounds();							/*!< Check screen bounds and repositions*/
	int getCurrentState();						/*!< Returns current state*/

private:
	// AI SHTUFF
	///////////////////////////////////
	sf::Vector2f m_position;					/*!<Contains position*/
	sf::Vector2f m_velocity;					/*!<Contains velocity*/

	sf::Vector2i m_screenBounds;				/*!<Contains Screen bounds 0 - 1980*/
	sf::Vector2i m_worldBounds;					/*!<Contains World Bounds bounds -1920 - 15630*/
	///////////////////////////////////
	const int BULLET_COOLDOWN_TIMER = 2;		/*!<Time before can shoot again*/
	const int BULLET_RANGE = 700;				/*!<Range player has to be less than before can shoot*/
	float m_bulletReloadTimer;					/*!<Contains total time reloading for*/

	int m_health;								/*!<Contains health*/
	const int RADIUS = 50;						/*!<Collision radius/bounds*/
	const int ABDUCT_RADIUS = 400;				/*!<Aabduction radius/bounds "Distance must be < in order to abduct Astronaut"*/
	const int TARGET_SPEED = 200;				/*!<Speed at which velocity is multiplied by when targeting Astronaut*/
	bool m_alive;								/*!<Contains alive state*/
	int m_currentState;							/*!<Contains current state*/
	int NUM_OF_ANIMS = 3;						/*!<Number of Animations has*/
	Astronaut * m_astro;						/*!<Contains pointer to an Astronaut */
	sf::Time m_frameTime;						
	AnimatedSprite m_animatedSprite;			
	std::vector<Animation> m_animations;		
	Animation* m_currAnimation;					

};

