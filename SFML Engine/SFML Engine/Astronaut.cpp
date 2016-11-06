#include "stdafx.h"
#include "Astronaut.h"




Astronaut::Astronaut()
	: m_alive(true)
	, m_state(Falling)
	, m_animatedSprite(sf::seconds(0.2f),true, false)
	, m_animations(NUM_OF_ANIMS)
{
}

Astronaut::~Astronaut()
{
}

void Astronaut::init(sf::Texture & tex, int xPos)
{
	m_animations[Anims::WalkLeft].setSpriteSheet(tex);
	m_animations[Anims::WalkLeft].addFrame(sf::IntRect(48,48,48,48));
	m_animations[Anims::WalkLeft].addFrame(sf::IntRect(0,48,48,48));
	m_animations[Anims::WalkLeft].addFrame(sf::IntRect(48, 48, 48, 48));
	m_animations[Anims::WalkLeft].addFrame(sf::IntRect(96,48,48,48));

	m_animations[Anims::WalkRight].setSpriteSheet(tex);
	m_animations[Anims::WalkRight].addFrame(sf::IntRect(48, 96, 48, 48));
	m_animations[Anims::WalkRight].addFrame(sf::IntRect(0, 96, 48, 48));
	m_animations[Anims::WalkRight].addFrame(sf::IntRect(48, 96, 48, 48));
	m_animations[Anims::WalkRight].addFrame(sf::IntRect(96, 96, 48, 48));

	m_animations[Anims::Falling_Abducted].setSpriteSheet(tex);
	m_animations[Anims::Falling_Abducted].addFrame(sf::IntRect(0,0,48,48));

	m_currAnimation = &m_animations[Anims::Falling_Abducted];
	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(sf::Vector2f(200, 300));
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);

}

void Astronaut::update(sf::Time deltaTime)
{
	m_animatedSprite.play(*m_currAnimation);

	if (m_state == Wander)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_currAnimation = &m_animations[Anims::WalkLeft];
			m_velocity.x = -MAX_SPEED;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_currAnimation = &m_animations[Anims::WalkRight];
			m_velocity.x = MAX_SPEED;
		}
		else
		{
			m_velocity.x = 0;
			m_velocity.y = 0;
			m_animatedSprite.stop();
		}
	}
	else if (m_state == Falling)
	{
		m_currAnimation = &m_animations[Anims::Falling_Abducted];
		if (m_animatedSprite.getPosition().y > GROUND)
		{
			int x = m_animatedSprite.getPosition().x;
			int y = m_animatedSprite.getPosition().y;

			m_animatedSprite.setPosition(sf::Vector2f(m_animatedSprite.getPosition().x, GROUND));
			m_state = Wander;
			m_velocity.y = 0;
		}
		else
		{
			m_velocity.x = 0;
			m_velocity.y = GRAVITY;
		}
	}
	m_animatedSprite.move(m_velocity * deltaTime.asSeconds());
	m_animatedSprite.update(deltaTime);
}

void Astronaut::setPosition(sf::Vector2f pos)
{
	m_animatedSprite.setPosition(pos);
}

AnimatedSprite Astronaut::draw()
{
	return m_animatedSprite;
}

