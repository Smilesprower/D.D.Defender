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
	void update();
	void init(sf::Texture & atlas, sf::Vector2f pos, sf::Vector2i screenBounds, int type);
	AnimatedSprite draw();
	sf::CircleShape drawOutline();
	sf::Vector2f getPosition();
	int getRadius();
private:
	int NUM_OF_ANIMS = 2;
	const int RADIUS = 100;
	int m_type;

	AnimatedSprite m_animatedSprite;
	std::vector<Animation> m_animations;
	Animation* m_currAnimation;
	//sf::Sprite m_sprite;
	sf::CircleShape m_collider;
	sf::Vector2f m_position;
};

