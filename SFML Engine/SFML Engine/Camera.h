/*! \brief  Handles all the properties of the camera, controls the view.
*
*
*
*/
#pragma once
#include <SFML\Graphics.hpp>

class Camera
{
public:
	Camera(sf::Vector2i, sf::Vector2i);
	~Camera();
	sf::View Update(float playerX);		/*!< Update Camera based on plyers x position*/
													
private:
	sf::View m_view;				/*!< Contains camera view*/
	sf::Vector2i m_worldSize;		/*!< Contains world size*/
	sf::Vector2i m_viewSize;		/*!< Contains view size*/
	sf::Vector2f m_viewPosition;	/*!< Contains view position*/
};

