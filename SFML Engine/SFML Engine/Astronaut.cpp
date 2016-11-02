#include "stdafx.h"
#include "Astronaut.h"

Astronaut::Astronaut()
	: m_alive(true)
	, m_flee(false)
    , m_abducted(false)
    , m_direction(Left)
{
}

Astronaut::~Astronaut()
{
}

void Astronaut::init(sf::Texture & tex, sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
	m_sprite.setTexture(tex);
}

void Astronaut::update(sf::Time deltaTime)
{
}

sf::Sprite Astronaut::draw()
{
	return m_sprite;
}


