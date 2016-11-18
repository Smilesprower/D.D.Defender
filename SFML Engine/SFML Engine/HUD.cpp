#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
	: m_screenSize(0,0)
	, m_colorA(255,0,0)
	, m_colorB(0,255,0)
	, m_interpolatedColor(0,0,0)
	, m_colorTimer(0)
{

}

void HUD::init(sf::Texture & smartBombReload, sf::Vector2i screenSize)
{
	m_screenSize = screenSize;

	m_hud.setTexture(smartBombReload);
	m_smartBombRect.setPosition(screenSize.x * 0.885f, 20);
}

void HUD::update(sf::Time deltaTime, float sbRectSize)
{
	m_colorTimer += deltaTime.asSeconds();
	m_smartBombRect.setSize(sf::Vector2f(sbRectSize * 3.42, 40));
	if (m_colorTimer < 60) {

		double t = m_colorTimer / 90; // t goes from 0 to 1
		m_interpolatedColor = interpolate(m_colorA, m_colorB, t);
		sf::Color colour = sf::Color(255 * m_interpolatedColor.x, 255 * m_interpolatedColor.y, m_interpolatedColor.z);
		m_smartBombRect.setFillColor(sf::Color(m_interpolatedColor.x, m_interpolatedColor.y, m_interpolatedColor.z));
	}
	//updateSmartBombRect(sbRectSize);

}

void HUD::updateSmartBombRect(float size)
{
	m_smartBombRect.setSize(sf::Vector2f(size * 3.42, 40));

	if (size < 20)
	{

		m_smartBombRect.setFillColor(sf::Color(255, 0, 0));
	}
	else if (size >= 20 && size < 40)
	{
		m_smartBombRect.setFillColor(sf::Color(255, 255, 0));
	}
	else if (size < 60)
	{
		m_smartBombRect.setFillColor(sf::Color(0, 255, 0));
	}
	else
	{
		m_smartBombRect.setFillColor(sf::Color(229, 198, 0));
	}
}

void HUD::reset()
{
	m_colorTimer = 0;

}

sf::Sprite HUD::draw()
{
	return m_hud;
}

sf::RectangleShape HUD::drawRectangle()
{
	return m_smartBombRect;
}

sf::Vector3f HUD::interpolate(sf::Vector3f a, sf::Vector3f b, float t)
{
	return a*(1 - t) + b*t;
}

