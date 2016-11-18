#pragma once
#include "Scene.h"

class HUD
{
public:
	HUD();
	void init(sf::Texture & tex, sf::Vector2i screenSize);
	void update(sf::Time deltaTime, float sbRectSize);
	void updateSmartBombRect(float size);
	void reset();
	sf::Sprite draw();
	sf::RectangleShape drawRectangle();
	sf::Vector3f interpolate(sf::Vector3f a, sf::Vector3f b, float t);
private:
	sf::Vector2i m_screenSize;
	sf::Sprite m_hud;

	sf::RectangleShape m_smartBombRect;
	sf::Vector3f m_colorA, m_colorB, m_interpolatedColor;
	float m_colorTimer;
};
