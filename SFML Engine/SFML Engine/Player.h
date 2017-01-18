/*! \brief Handles all the properties and responsibilities of the player.
*
*
*
*/

#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"
#include "BulletManager.h"

class Player
{
public:
	
	enum SmartBomb
	{
		Ready,
		Charging,
		Fired,
		Disable,
	};
	Player();
	~Player();

	void init(sf::Texture & tex, sf::Vector2f pos, sf::Vector2i tpBounds);	/*!< Initialise the player*/
	void update(sf::Time deltaTime);				/*!< Update the player*/
	void Move(sf::Time deltaTime);					/*!< Move the player*/
	AnimatedSprite draw();							/*!< Draw the player sprite and animations*/
	void teleport(sf::Time deltaTime);				/*!< Function to teleport the player on key press*/

	int getTeleport();								/*!< Returns state of the teleport, enabled or disabled*/
	void disableTeleporter();						/*!< Disable the teleporter if already been used*/

	int getSmartBombState();						/*!< Returns state of the smart bomb, enabled or disabled*/
	void chargeSmartBomb();							/*!< Sets the state of the smart bomb to be charging*/
	void updateSmartBomb(sf::Time deltaTime);		/*!< Charges the smart bomb when not ready for use*/

	void setDamage(int damage);						/*!< Deduct health from player*/
	int getHealth();								/*!< Return the player's health*/

	int getRadius();								/*!< Get the collision radius of the player*/
	bool gameOver();								/*!< Return if game is over*/
	sf::Vector2f getPosition();						/*!< Get player's position*/
	void setPosition(sf::Vector2f pos);				/*!< Set player's position*/
	sf::CircleShape drawPlayerOutline();			/*!< Draw the players collision radius. used for debugging*/
	AnimatedSprite m_animatedSprite;				/*!< Animated sprite of the player*/
	float m_smartBombTimer;							/*!< Timer for smart bomb reload*/
	sf::Vector2f getVel();							/*!< Get player's velocity*/
	sf::Vector2f getAccel();						/*!< Get player's acceleration*/
private:
	enum Anims
	{
		MoveUp,
		MoveDown,
		MoveSideways,
		Explosion,
	};
	enum Direction
	{
		Left = -1,
		Right = 1,
		Up,
		Down
	};
	const int MAX_SPEED = 700;				/*!< Max speed player can move*/
	const int SMART_BOMB_RELOAD_TIME = 60;	/*!< Time it takes for smart bomb to reload*/
	const int PLAYER_RADIUS = 35;			/*!< Player's current radius*/
	const int MAX_FRAMES_EXPLOSION = 7;		/*!< Frames in explosion animation*/
	const float DE_ACCEL = 4.f;				/*!< Rate of change of velocity when slowing down*/
	const float BULLET_RELOAD_TIME = 100.f;	/*!< Time takes to reload a bullet*/

	bool m_gameOver;		/*!< If game is over*/
	int m_health;			/*!< Players health*/
	int m_teleportedState;	/*!< Current state of the teleport*/
	int m_smartBombState;	/*!< Current state of the smart bomb*/
	float m_bulletTimer;	/*!< Time since last bullet fired*/

	int m_directionX;		/*!< Moving up or down*/
	int m_directionY;		/*!< Moving left or right*/

	sf::Vector2f m_accel;				/*!< Player's acceleration*/
	sf::Vector2f m_velocity;			/*!< Player's velocity*/
	sf::Vector2i m_teleportingBounds;	/*!< Range of position in which player can teleport to*/

	int NUM_OF_ANIMS = 4;	/*!< Number of animations player has*/

	sf::Time m_frameTime;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
	sf::CircleShape m_playerCollider;
};