#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
	: m_screenSize(0,0)
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
	updateSmartBombRect(sbRectSize);
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

sf::Sprite HUD::draw()
{
	return m_hud;
}

sf::RectangleShape HUD::drawRectangle()
{
	return m_smartBombRect;
}

