/*! \brief The HUD Class. Handles the UI that is displayed during the game.
*
*
*
*/
#pragma once
#include "Scene.h"

class HUD
{
public:
	HUD();
	void init(sf::Texture & tex, sf::Vector2i screenSize);
	void update(sf::Time deltaTime, float sbRectSize, int healthRectSize);
	void updateSmartBombRect(float size);
	void updateHealthRect(int size);
	void reset();
	sf::Sprite draw();
	sf::RectangleShape drawRectangle();
	sf::RectangleShape drawHealthRect();
	sf::Vector3f interpolate(sf::Vector3f a, sf::Vector3f b, float t);
private:
	sf::Vector2i m_screenSize;
	sf::Sprite m_hud;

	sf::RectangleShape m_smartBombRect;
	sf::RectangleShape m_healthRect;
		
	sf::Vector3f m_colorA, m_colorB, m_colorC, m_interpolatedColor, m_interpolatedHealthColor;
	float m_colorTimer;
	int m_playerHealth;
};
