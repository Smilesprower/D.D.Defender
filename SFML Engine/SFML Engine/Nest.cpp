#include "stdafx.h"
#include "Nest.h"


Nest::Nest(sf::Texture & tex, sf::Vector2f pos, sf::Vector2i screenBounds)
	: m_position(pos)
	, m_screenBounds(screenBounds)
	, m_alive(true)
	, m_state(Wander)
{
	// TODO: Stuff


}


Nest::~Nest()
{
}

void Nest::update(sf::Time deltaTime)
{
}

AnimatedSprite Nest::draw()
{
	return AnimatedSprite();
}
