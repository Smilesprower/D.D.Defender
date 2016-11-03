#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	m_view.reset(sf::FloatRect(0, 0, 1920, 1080));
	m_view.setViewport(sf::FloatRect(0, 0, 1.0, 1.0));

}


Camera::~Camera()
{

}

sf::View Camera::Update(float p_playerX, sf::Vector2u p_windowSize)
{
	m_viewPosition.x = p_playerX - (p_windowSize.x * 0.5);
	m_view.reset(sf::FloatRect(m_viewPosition.x, m_viewPosition.y, 1920, 1080));

	return m_view;
}
