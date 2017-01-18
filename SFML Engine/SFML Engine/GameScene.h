/*! \brief Handles everything that occurs during the game.
*
*
*
*/
#pragma once
#include "Scene.h"
#include "AnimatedSprite.h"
#include "Bullet.h"
#include "Astronaut.h"
#include "nest.h"
#include "Camera.h"
#include "HUD.h"
#include "CollisionManager.h"
#include "Obstacle.h"
#include "Alien.h"
#include "Mutant.h"


class GameScene : public Scene
{
public:
	GameScene(SceneStack& stack, Context context);
	~GameScene();
	virtual void draw();								/*!< Manages drawing all game entities in the gamescene*/
	virtual bool update(sf::Time deltaTime);			/*!< Manages the update of all game entities in the gamescene*/
	virtual bool handleEvent(const sf::Event& event);	/*!< Manages handle input for the gamescene*/

	bool checkEnemiesAlive();	/*!< Check to see if all enemies have been killed, complete game when all enemies are dead*/

	void setupShockwave(sf::Vector2f playerPos);	/*!<Sets up the shockwave/smartbomb shader effect using players current position*/
	void setupRipple(sf::Vector2f playerPos);		/*!<Sets up the ripple/teleporting shader effect using players current position*/
	void screenSwitch(std::vector<Bullet*> bullets);/*!<When the player screen swap from onside to the other any enemy with in the players view gets swapped also*/

private:
	const int OFFSET = 2;				/*!< Screen offset count for worldsize*/
	const int MAX_GAS_CLOUDS = 7;		/*!< Max number of gas cloud obstacles*/
	int m_numOfScreens;					/*!< Number of screens in the game*/
	sf::Vector2i m_screenSize;			/*!< Contains screensize*/
	sf::Vector2i m_halfScreenSize;		/*!< Contains 1/2 screensize*/
	sf::Vector2i m_worldSize;			/*!< Contains worldsize*/
	sf::Vector2i m_boundries;			/*!< Contains boundaries*/
									
	Camera m_camera;					/*!< Contains camera object*/

	sf::Sprite m_sprite;				/*!< Contains background sprite*/
	ShaderHolder m_shaders;				/*!< Map that holds all loaded shader files*/
	sf::Shader * m_shockwave;			/*!< shockwave shader*/
	sf::Shader * m_ripple;				/*!< ripple shader*/
	sf::Clock m_clock;					/*!< Clock for timing shader effects*/
	bool m_playShockwave;				/*!< Allows shockwave to be played*/
	bool m_playRipple;					/*!< Allows ripple to be played*/

	Player * m_playo;								/*!< Contains Player object*/
	CollisionManager m_collisionManager;			/*!< Collision Manager Object*/
	HUD m_hud;										/*!< HUD object*/
	std::vector<Astronaut*> m_astronauts;			/*!< Vector of Astronaut objects*/
	std::vector<Nest*> m_nests;						/*!< Vector of Nest objects*/
	std::vector<Alien*> m_aliens;					/*!< Vector of Alien objects*/
	std::vector<Mutant*> m_mutants;					/*!< Vector of Mutant objects*/
	std::vector<Obstacle*> m_gasClouds;				/*!< Vector of Gascloud Obstacle objects*/
	std::vector<Obstacle*> m_healthPacks;			/*!< Vector of Pick up Obstacle objects*/
	sf::Vector2f m_currPlayerPos;					/*!< Current players position*/
	const int MAX_SMARTBOMB_DAMAGE = 100000;		/*!< Max smartbomb damage*/
	const int MAX_BULLETS = 50;						/*!< Max amount of bullets the game uses*/
	const int NUM_OF_ASTROS = 20;					/*!< Max amount of Astronauts created*/
	const int NUM_OF_ALIENS = 20;					/*!< Max amount of Aliens created*/
	const int NUM_OF_MUTANTS = 20;					/*!< Max amount of Mutants created*/
	const int NUM_OF_HEALTH_PACKS = 10;				/*!< Max amount of HealthPacks created*/
	float m_shaderValue1;							/*!< Varying shader values, amplitude, distortion, refraction etc*/
	float m_shaderValue2;							/*!< Varying shader values, amplitude, distortion, refraction etc*/
	int m_streakCount;								/*!< Kill streak*/
	sf::RectangleShape m_screenView;
	sf::RectangleShape m_playerCutOff;
	sf::RectangleShape m_enemyCutOff;

	int m_score;									/*!< Contains current score*/
	sf::Text m_scoreText;							/*!< Contains Text for score*/
	sf::Text m_aliveAstrosText;						/*!< Contains Text for num of Astronauts alive*/
	float m_displayingAstroText;					
													
													
	std::vector<sf::CircleShape> m_radarIcons;		/*!< Contains radar icons for astronauts*/
	sf::RectangleShape m_radarScreen;				/*!< Contains radar itself*/
	sf::CircleShape m_playerRadar;					/*!< Contains players radar icon*/
	bool m_canUpdateRadar;
	float m_radarTime;
};
