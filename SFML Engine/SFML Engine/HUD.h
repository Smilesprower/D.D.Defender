/*! \brief Handles the UI that is displayed during the game.
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
	void init(sf::Texture & tex, sf::Vector2i screenSize);					/*!< Initialises the UI items*/
	void update(sf::Time deltaTime, float sbRectSize, int healthRectSize);	/*!< Updates each item int the UI*/
	void updateSmartBombRect(float size);									/*!< Updates the rectangle bar for the smart bomb displayed on the UI*/
	void updateHealthRect(int size);										/*!< Updates the rectangle bar for the player's health displayed on the UI*/
	void reset();															/*!< Reset the HUD when the game is restarted*/

	sf::Sprite draw();														/*!< Returns the HUD image to be displayed on the screen*/
	sf::RectangleShape drawRectangle();
	sf::RectangleShape drawHealthRect();
	sf::Vector3f interpolate(sf::Vector3f a, sf::Vector3f b, float t);		/*!< Used to change the colour of the health and smart bomb bar*/
private:
	sf::Vector2i m_screenSize;	/*!< Size of the screen*/
	sf::Sprite m_hud;			/*!< Sprite for the HUD*/

	sf::RectangleShape m_smartBombRect;	/*!< Rectangle shape for the smart bomb*/
	sf::RectangleShape m_healthRect;	/*!< Rectangle chape for the players health*/
		
	sf::Vector3f m_colorA, m_colorB, m_colorC, m_interpolatedColor, m_interpolatedHealthColor;
	float m_colorTimer;
	int m_playerHealth;	/*!< Players health*/
};
