#include "stdafx.h"
#include "nest.h"

Nest::Nest()
	: m_alive(true)
	, m_state(Wander)
	, m_direction(Left)
	, m_animations(NUM_OF_ANIMS)
	, m_wanderTime(0)
	, m_missileReloadTimer(COOLDOWN_TIMER)
	, m_health(MAX_HEALTH)
	, m_animatedSprite(sf::seconds(0.15f), true, false)
{
}


Nest::~Nest()
{
}

void Nest::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
	if (m_alive)
	{
		m_missileReloadTimer += deltaTime.asSeconds();
		float distanceSquared;
		float dx = m_evadeRadius.getPosition().x - playerPos.x;
		int dy = m_evadeRadius.getPosition().y - playerPos.y;
		distanceSquared = (dx*dx) + (dy*dy);

		if (distanceSquared < EVADE_RANGE * EVADE_RANGE)
		{
			m_state = Evade;
			m_velocity.x = MAX_EVADE_VELOCITY;
		}
		else
		{
			m_state = Wander;
			m_velocity.x = MAX_VELOCITY;
		}

		if (m_state == Wander)
		{
			m_wanderTime += deltaTime.asSeconds();

			if (m_wanderTime >= TIME_TO_SWITCH_DIRECTION)
			{
				m_direction = m_direction * -1;
				m_wanderTime = 0;
			}
		}
		else if (m_state == Evade)
		{
			if (playerPos.x > m_animatedSprite.getPosition().x)
			{
				m_direction = Direction::Left;
			}
			else
			{
				m_direction = Direction::Right;
			}

			if (distanceSquared < MISSILE_RANGE * MISSILE_RANGE)
			{
				if (m_missileReloadTimer >= COOLDOWN_TIMER)
				{
					if (BulletManager::Instance()->createMissile(m_animatedSprite.getPosition(), playerPos, 2));
					{
						m_missileReloadTimer = 0;
					}
				}
			}
		}
		std::cout << m_health << std::endl;
		if (m_animatedSprite.getFrame() > 3)
		{
			m_alive = false;
		}
		m_velocity.x *= m_direction;
		m_animatedSprite.move(m_velocity * deltaTime.asSeconds());
		m_animatedSprite.update(deltaTime);
		checkBounds();
		m_evadeRadius.setPosition(m_animatedSprite.getPosition());
		m_missileRadius.setPosition(m_animatedSprite.getPosition());
	}
}

void Nest::init(sf::Texture & tex, sf::Vector2f pos, sf::Vector2i screenBounds)
{
	m_screenBounds = screenBounds;
	m_screenBounds.y += abs(m_screenBounds.x);
	m_animations[Anims::Default].setSpriteSheet(tex);
	m_animations[Anims::Default].addFrame(sf::IntRect(0, 525, 400, 216));

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
	m_animatedSprite.setPosition(pos);
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);


	// DEBUGGING CODE
	/////////////////////////////////////////////
	m_evadeRadius = sf::CircleShape(EVADE_RANGE);
	m_evadeRadius.setFillColor(sf::Color::Transparent);
	m_evadeRadius.setOutlineThickness(3);
	m_evadeRadius.setOutlineColor(sf::Color::Yellow);
	m_evadeRadius.setOrigin(EVADE_RANGE, EVADE_RANGE);

	m_missileRadius = sf::CircleShape(MISSILE_RANGE);
	m_missileRadius.setFillColor(sf::Color::Transparent);
	m_missileRadius.setOutlineThickness(3);
	m_missileRadius.setOutlineColor(sf::Color::Magenta);
	m_missileRadius.setOrigin(MISSILE_RANGE, MISSILE_RANGE);
}

void Nest::checkBounds()
{	
	if (m_animatedSprite.getPosition().x - m_animatedSprite.getLocalBounds().width * 0.5f >= m_screenBounds.y)
	{
		m_animatedSprite.setPosition(m_screenBounds.x - m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getPosition().y);
	}
	else if (m_animatedSprite.getPosition().x + m_animatedSprite.getLocalBounds().width * 0.5f <= m_screenBounds.x)
	{
		m_animatedSprite.setPosition(m_screenBounds.y + m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getPosition().y);
	}
	
}

sf::Vector2f Nest::getPosition()
{
	return m_animatedSprite.getPosition();
}

void Nest::setPosition(sf::Vector2f position)
{
	m_animatedSprite.setPosition(position);
}

AnimatedSprite Nest::draw()
{
	return m_animatedSprite;
}

sf::CircleShape Nest::drawEvade()
{
	return m_evadeRadius;
}

sf::CircleShape Nest::drawFire()
{
	return m_missileRadius;
}

void Nest::setDamage(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		m_currAnimation = &m_animations[Anims::Explode];
		m_animatedSprite.setOrigin(40, 40);
		m_animatedSprite.setScale(4, 4);
		m_health = 0;
		m_animatedSprite.play(*m_currAnimation);
	}
}

int Nest::getHealth()
{
	return m_health;
}

int Nest::getRadius()
{
	return NEST_RADIUS;
}

bool Nest::isAlive()
{
	return m_alive;
}

void Nest::setAlive(bool alive)
{
	m_alive = alive;
}
