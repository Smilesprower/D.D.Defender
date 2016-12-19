#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace sf {
	class Time;
}

class Obstacle
{
public:
	Obstacle();
	~Obstacle();
	void update();
	void init(sf::Texture & tex, sf::Vector2f pos, sf::Vector2i screenBounds);
	sf::Sprite draw();
	sf::CircleShape drawOutline();
	sf::Vector2f getPosition();
	int getRadius();
private:
	const int RADIUS = 100;

	sf::Sprite m_sprite;
	sf::CircleShape m_collider;
	sf::Vector2f m_position;
};

