#pragma once
#include "Scene.h"

class HUD
{
public:
	HUD();
	void init(sf::Texture & tex, sf::Vector2i screenSize);
	void update(sf::Time deltaTime, float sbRectSize);
	void updateSmartBombRect(float size);
	sf::Sprite draw();
	sf::RectangleShape drawRectangle();
private:
	sf::Vector2i m_screenSize;
	sf::Sprite m_hud;

	sf::RectangleShape m_smartBombRect;
	
};
