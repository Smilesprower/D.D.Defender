#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle()
	:m_type(0)
	, m_animations(NUM_OF_ANIMS)
	, m_alive(true)
{
}


Obstacle::~Obstacle()
{
}

void Obstacle::update()
{
	
}

void Obstacle::init(sf::Texture & atlas, sf::Vector2f pos, sf::Vector2i screenBounds, int type)
{
	m_type = type;

	m_animations[Type::HealthPack].setSpriteSheet(atlas);
	m_animations[Type::HealthPack].addFrame(sf::IntRect(260, 0, 140, 140));

	m_animations[Type::GasCloud].setSpriteSheet(atlas);
	m_animations[Type::GasCloud].addFrame(sf::IntRect(630, 0, 370, 200));

	if (m_type == GasCloud)
	{
		m_currAnimation = &m_animations[Type::GasCloud];
	}
	else if (m_type == HealthPack)
	{
		m_currAnimation = &m_animations[Type::HealthPack];
	}

	m_animatedSprite.play(*m_currAnimation);
	m_position = pos;
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5, m_animatedSprite.getLocalBounds().height * 0.5);
	m_animatedSprite.setPosition(m_position);
}

AnimatedSprite Obstacle::draw()
{
	return m_animatedSprite;
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

int Obstacle::getType()
{
	return m_type;
}

void Obstacle::setEnabled(bool alive)
{
	m_alive = alive;
}

bool Obstacle::isEnabled()
{
	return m_alive;
}
