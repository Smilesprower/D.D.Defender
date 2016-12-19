#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle()
{
}


Obstacle::~Obstacle()
{
}

void Obstacle::update()
{
	
}

void Obstacle::init(sf::Texture & tex, sf::Vector2f pos, sf::Vector2i screenBounds)
{
	m_sprite.setTexture(tex);
	m_position = pos;
	m_sprite.setOrigin(m_sprite.getLocalBounds().width * 0.5, m_sprite.getLocalBounds().height * 0.5);
	m_sprite.setPosition(m_position);

	//m_collider.setRadius(RADIUS);
	//m_collider.setFillColor(sf::Color::Transparent);
	//m_collider.setOutlineThickness(3);
	//m_collider.setOutlineColor(sf::Color::Yellow);
	//m_collider.setOrigin(RADIUS, RADIUS);
	//m_collider.setPosition(pos);

	m_collider = sf::CircleShape(RADIUS);
	m_collider.setFillColor(sf::Color::Transparent);
	m_collider.setOutlineThickness(3);
	m_collider.setOutlineColor(sf::Color::Cyan);
	m_collider.setOrigin(RADIUS, RADIUS);
	m_collider.setPosition(pos);
}

sf::Sprite Obstacle::draw()
{
	return m_sprite;
}

sf::CircleShape Obstacle::drawOutline()
{
	return m_collider;
}

sf::Vector2f Obstacle::getPosition()
{
	return m_position;
}

int Obstacle::getRadius()
{
	return RADIUS;
}
