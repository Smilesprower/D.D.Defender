#include "stdafx.h"
#include "Mutant.h"



Mutant::Mutant(sf::Texture & tex, sf::Vector2i screenBounds, sf::Vector2i worldBounds)
	: m_animatedSprite(sf::seconds(0.1f), true, false)
	, m_animations(NUM_OF_ANIMS)
	, m_screenBounds(screenBounds)
	, m_worldBounds(sf::Vector2i(worldBounds.x, worldBounds.y + abs(worldBounds.x)))
	, m_alive(false)
	, m_health(0)
{
	m_animations[Anims::Default].setSpriteSheet(tex);
	m_animations[Anims::Default].addFrame(sf::IntRect(417, 0, 98, 98));

	m_animations[Anims::Explode].setSpriteSheet(tex);
	m_animations[Anims::Explode].addFrame(sf::IntRect(0, 144, 80, 80));
	m_animations[Anims::Explode].addFrame(sf::IntRect(80, 144, 80, 80));
	m_animations[Anims::Explode].addFrame(sf::IntRect(160, 144, 80, 80));
	m_animations[Anims::Explode].addFrame(sf::IntRect(240, 144, 80, 80));
	m_animations[Anims::Explode].addFrame(sf::IntRect(320, 144, 80, 80));
	m_animations[Anims::Explode].addFrame(sf::IntRect(400, 144, 80, 80));
	m_animations[Anims::Explode].addFrame(sf::IntRect(480, 144, 80, 80));
	m_animations[Anims::Explode].addFrame(sf::IntRect(560, 144, 80, 80));

	m_currAnimation = &m_animations[Anims::Default];
	m_animatedSprite.play(*m_currAnimation);
}

Mutant::~Mutant()
{
}
void Mutant::init(sf::Vector2f pos)
{
	m_alive = true;
	m_health = 100;
	m_velocity = sf::Vector2f(0, 300);
	m_currAnimation = &m_animations[Anims::Default];
	m_animatedSprite.setScale(1, 1);
	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(pos);
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);
	m_animatedSprite.setScale(1, 1);
}
void Mutant::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
	if (m_state == Start)
	{
		if (m_animatedSprite.getPosition().y > 200)
		{
			m_state == Seek;
			m_velocity.y = 0;
		}
	}
	m_animatedSprite.move(m_velocity * deltaTime.asSeconds());
	m_animatedSprite.update(deltaTime);
}



void Mutant::checkBounds()
{
}

sf::Vector2f Mutant::getPosition()
{
	return m_animatedSprite.getPosition();
}

void Mutant::setPosition(sf::Vector2f position)
{
	m_animatedSprite.setPosition(position);
}

AnimatedSprite Mutant::draw()
{
	return m_animatedSprite;
}

void Mutant::setDamage(int damage)
{
}

int Mutant::getHealth()
{
	return m_health;
}

int Mutant::getRadius()
{
	return COLLISION_RADIUS;
}

bool Mutant::isAlive()
{
	return m_alive;
}

void Mutant::setAlive(bool alive)
{
	m_alive = alive;
}
