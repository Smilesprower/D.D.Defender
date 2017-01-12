#include "stdafx.h"
#include "Astronaut.h"




Astronaut::Astronaut(sf::Texture & tex, int xPos)
	: m_alive(true)
	, m_state(Falling)
	, m_animatedSprite(sf::seconds(0.2f),true, false)
	, m_animations(NUM_OF_ANIMS)
	, m_abductedVelocity(0, MAX_ABDUCTED_SPEED)
	, m_direction(1)
{
	m_animations[Anims::WalkLeft].setSpriteSheet(tex);
	m_animations[Anims::WalkLeft].addFrame(sf::IntRect(48, 48, 48, 48));
	m_animations[Anims::WalkLeft].addFrame(sf::IntRect(0, 48, 48, 48));
	m_animations[Anims::WalkLeft].addFrame(sf::IntRect(48, 48, 48, 48));
	m_animations[Anims::WalkLeft].addFrame(sf::IntRect(96, 48, 48, 48));

	m_animations[Anims::WalkRight].setSpriteSheet(tex);
	m_animations[Anims::WalkRight].addFrame(sf::IntRect(48, 96, 48, 48));
	m_animations[Anims::WalkRight].addFrame(sf::IntRect(0, 96, 48, 48));
	m_animations[Anims::WalkRight].addFrame(sf::IntRect(48, 96, 48, 48));
	m_animations[Anims::WalkRight].addFrame(sf::IntRect(96, 96, 48, 48));

	m_animations[Anims::Falling_Abducted].setSpriteSheet(tex);
	m_animations[Anims::Falling_Abducted].addFrame(sf::IntRect(0, 0, 48, 48));

	m_currAnimation = &m_animations[Anims::Falling_Abducted];
	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(sf::Vector2f(xPos, 900));
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);

	// DEBUGGING CODE
	/////////////////////////////////////////////
	m_collisionRadius = sf::CircleShape(RADIUS);
	m_collisionRadius.setFillColor(sf::Color::Transparent);
	m_collisionRadius.setOutlineThickness(3);
	m_collisionRadius.setOutlineColor(sf::Color::Yellow);
	m_collisionRadius.setOrigin(RADIUS, RADIUS);
}

Astronaut::~Astronaut()
{
}

void Astronaut::init(sf::Texture & tex, int xPos)
{

}

void Astronaut::update(sf::Time deltaTime)
{
	m_animatedSprite.play(*m_currAnimation);

	if (m_state == Wander)
	{
		m_wanderTime += deltaTime.asSeconds();
		if (m_direction == 1)
		{
			m_currAnimation = &m_animations[Anims::WalkRight];
		}
		else
		{
			m_currAnimation = &m_animations[Anims::WalkLeft];
		}
		m_velocity.x = (MAX_SPEED * deltaTime.asSeconds())* m_direction;

		if (m_wanderTime >= rand() % 50 + 10)
		{
			m_direction = m_direction * -1;
			m_wanderTime = 0;
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
	else if (m_state = Abducted)
	{
		abducted(deltaTime);
	}
	m_animatedSprite.move(m_velocity * deltaTime.asSeconds());
	m_animatedSprite.update(deltaTime);

	//debugging
	m_collisionRadius.setPosition(m_animatedSprite.getPosition());
}

void Astronaut::abducted(sf::Time deltaTime)
{
	m_animatedSprite.move(m_abductedVelocity * deltaTime.asSeconds());
}

sf::Vector2f Astronaut::getPosition()
{
	return m_animatedSprite.getPosition();
}

void Astronaut::setPosition(sf::Vector2f pos)
{
	m_animatedSprite.setPosition(pos);
}

AnimatedSprite Astronaut::draw()
{
	return m_animatedSprite;
}

void Astronaut::setAbducted()
{
	m_state = Abducted;
}

int Astronaut::isAbducted()
{
	return m_state;
}

int Astronaut::getRadius()
{
	return RADIUS;
}

sf::CircleShape Astronaut::drawCollisionRadius()
{
	return m_collisionRadius;
}

