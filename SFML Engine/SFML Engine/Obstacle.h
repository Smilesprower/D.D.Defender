/*! \brief Handles all the properties of the in game obstacles and items such as the Gas Clouds and the Health Packs.
*
*
*
*/

#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "AnimatedSprite.h"

namespace sf {
	class Time;
}

class Obstacle
{
public:
	enum Type
	{
		GasCloud,
		HealthPack,
	};

	Obstacle();
	~Obstacle();
	void update();					/*!< Updates each type of obstacle*/
	void init(sf::Texture & atlas, sf::Vector2f pos, sf::Vector2i screenBounds, int type);	/*!< Initialises the specific type of obstacle*/
	AnimatedSprite draw();			/*!< Returns the sprite of each type of obstacle*/
	sf::CircleShape drawOutline();	/*!< Returns the outline of the collision box for each obstacle*/
	sf::Vector2f getPosition();		/*!< Gets the psoition of the obstacle*/
	int getRadius();				/*!< Gets the collision radius of the obstacle*/
	int getType();					/*!< Returns the type of obstacle, health pack or gas cloud*/
	void setEnabled(bool alive);	/*!< Set if the obstacle is active or not*/
	bool isEnabled();				/*!< Check if obstacle is active*/
private:
	int NUM_OF_ANIMS = 2;
	const int RADIUS = 100;			/*!< Collision radius of object*/
	int m_type;						/*!< Type of obstacle*/
	bool m_alive;					/*!< is obstacle active or not*/

	AnimatedSprite m_animatedSprite;	/*!< Obstacle sprite*/
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
	//sf::Sprite m_sprite;
	sf::CircleShape m_collider;			/*!< Debugging shape for collider*/
	sf::Vector2f m_position;			/*!< Position of obstacle*/
};

