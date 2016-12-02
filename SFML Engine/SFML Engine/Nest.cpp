#include "stdafx.h"
#include "Nest.h"


Nest::Nest()
	: m_alive(true)
	, m_state(Wander)
	, m_direction(Left)
	, m_animations(NUM_OF_ANIMS)
	, m_wanderTime(0)
{
}


Nest::~Nest()
{
}

void Nest::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
	if (m_state == Wander)
	{
		//m_wanderTime += deltaTime.asSeconds();

		//if (m_wanderTime >= TIME_TO_SWITCH_DIRECTION)
		//{
			//m_direction = m_direction * -1;
			//m_wanderTime = 0;
	/*	}*/
	}
	else if (m_state == Flee)
	{

	}

	m_velocity.x = MAX_VELOCITY * m_direction;
	m_animatedSprite.move(m_velocity * deltaTime.asSeconds());
	m_animatedSprite.update(deltaTime);
	checkBounds(playerPos);
}

void Nest::init(sf::Texture & tex, sf::Vector2f pos, sf::Vector2i screenBounds)
{
	m_screenBounds = screenBounds;
	m_animations[Anims::Default].setSpriteSheet(tex);
	m_animations[Anims::Default].addFrame(sf::IntRect(0, 0, 400, 216));

	m_currAnimation = &m_animations[Anims::Default];
	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(sf::Vector2f(200, 300));
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);
}

void Nest::checkBounds(sf::Vector2f playerPos)
{
	sf::Vector2f temp = m_animatedSprite.getPosition();

	if (abs(temp.x - playerPos.x) > 960)
	{
		if (m_animatedSprite.getPosition().x >= m_screenBounds.y)
		{
			m_animatedSprite.setPosition(m_screenBounds.x, m_animatedSprite.getPosition().y);
		}
		else if (m_animatedSprite.getPosition().x <= m_screenBounds.x)
		{
			m_animatedSprite.setPosition(m_screenBounds.y, m_animatedSprite.getPosition().y);
		}
	}
	
}

AnimatedSprite Nest::draw()
{
	return m_animatedSprite;
}
