#pragma once
#include <SFML\Graphics.hpp>

class Camera
{
public:
	Camera(sf::Vector2i, sf::Vector2i);
	~Camera();
	sf::View Update(float playerX);

private:
	sf::View m_view;
	sf::Vector2i m_worldSize;
	sf::Vector2i m_viewSize;
	sf::Vector2f m_viewPosition;
};

