#include "stdafx.h"
#include "Camera.h"


Camera::Camera(sf::Vector2i worldSize, sf::Vector2i viewSize)
	: m_worldSize(worldSize)
	, m_viewSize(viewSize)
{
	m_view.reset(sf::FloatRect(0, 0, viewSize.x, viewSize.y));
	m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
}


Camera::~Camera()
{

}

sf::View Camera::Update(float xPosPlayer)
{
	// Sets view to centre of the screen
	m_view.reset(sf::FloatRect(m_viewPosition.x = xPosPlayer - (m_viewSize.x * 0.5), m_viewPosition.y, m_viewSize.x, m_viewSize.y));
	//m_view.reset(sf::FloatRect(m_viewPosition.x = xPosPlayer - (m_viewSize.x * 2), m_viewPosition.y - 800 , m_viewSize.x * 4, m_viewSize.y * 4));
	return m_view;
}
