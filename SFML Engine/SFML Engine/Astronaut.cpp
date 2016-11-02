#include "stdafx.h"
#include "Astronaut.h"




Astronaut::Astronaut()
	: m_alive(true)
	, m_state(Abducted)
	, m_dimensions(0,0,35,46) // Current TexRect
	, target(200, GROUND)
{
}

Astronaut::~Astronaut()
{
}

void Astronaut::init(sf::Texture & tex, int xPos)
{
	m_sprite.setPosition(xPos, GROUND - m_dimensions.height);
	m_sprite.setTexture(tex);
}

void Astronaut::update(sf::Time deltaTime)
{
	if (m_state == Wander)
	{

	}
	else if (m_state == Flee)	
	{
		int direction = m_sprite.getPosition().x - target.x;
		if (direction > 0)
		{
			m_velocity.x = MAX_SPEED;
		}
		else
		{
			m_velocity.x = -MAX_SPEED;
		}
	}
	else if (m_state == Falling)
	{
		if (m_sprite.getPosition().y > GROUND - m_dimensions.height)
		{
			m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, GROUND - m_dimensions.height));
			m_state = Wander;
			m_velocity.y = 0;
		}
		else
		{
			m_velocity.y = GRAVITY;
		}
	}
	else if (m_state == Abducted)
	{
		m_velocity.y = -GRAVITY;
	}

	m_velocity = m_velocity * deltaTime.asSeconds();
	m_sprite.move(m_velocity.x, m_velocity.y);
}

sf::Sprite Astronaut::draw()
{
	return m_sprite;
}


