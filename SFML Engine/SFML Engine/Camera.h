#pragma once
#include <SFML\Graphics.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	sf::View Update(float playerX, sf::Vector2u windowSize);


private:
	sf::View m_view;
	sf::Vector2f m_viewPosition;

};

