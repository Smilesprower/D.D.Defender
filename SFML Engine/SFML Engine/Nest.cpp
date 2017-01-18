#include "stdafx.h"
#include "nest.h"
#include "Score.h"
#include "SoundPlayer.h"

Nest::Nest(sf::Texture & tex, sf::Vector2i screenBounds)
	: m_alive(false)
	, m_state(Wander)
	, m_direction(Left)
	, m_animations(NUM_OF_ANIMS)
	, m_animations1(1)
	, m_wanderTime(0)
	, m_missileReloadTimer(COOLDOWN_TIMER)
	, m_health(MAX_HEALTH)
	, m_animatedSprite(sf::seconds(0.15f), true, false)
	, m_animatedSprite1(sf::seconds(0.15f), true, true)
	, m_spawnTimer(0)
	, m_screenBounds(sf::Vector2i(screenBounds.x, screenBounds.y + abs(screenBounds.x)))
{
	m_animations[Anims::Default].setSpriteSheet(tex);
	m_animations[Anims::Default].addFrame(sf::IntRect(0, 531, 431, 464));

	m_animations1[0].setSpriteSheet(tex);
	m_animations1[0].addFrame(sf::IntRect(640, 634, 360, 95));
	m_animations1[0].addFrame(sf::IntRect(640, 754, 360, 95));
	m_animations1[0].addFrame(sf::IntRect(640, 879, 360, 95));

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

	m_currAnimation1 = &m_animations1[0];
	m_animatedSprite1.play(*m_currAnimation1);

}


Nest::~Nest()
{
}

bool Nest::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
	if (m_alive)
	{
		if (m_currAnimation != &m_animations[Anims::Explode])
		{
			m_spawnTimer += deltaTime.asSeconds();
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
						SoundPlayer::Instance()->play(SoundEffect::Missile);
						if (BulletManager::Instance()->createMissile(m_animatedSprite.getPosition(), playerPos, 2));
						{
							m_missileReloadTimer = 0;
						}
					}
				}
			}
			if (m_spawnTimer >= 3)
			{
				m_spawnTimer = 0;
				return true;
			}
		}

		if (m_animatedSprite.getFrame() > 3)
		{
			m_alive = false;
		}
		m_velocity.x *= m_direction;
		m_animatedSprite.move(m_velocity * deltaTime.asSeconds());
		m_animatedSprite.update(deltaTime);
		m_animatedSprite1.setPosition(m_animatedSprite.getPosition().x, m_animatedSprite.getPosition().y + 100);
		m_animatedSprite1.update(deltaTime);
		checkBounds();
		m_evadeRadius.setPosition(m_animatedSprite.getPosition());
		m_missileRadius.setPosition(m_animatedSprite.getPosition());

	}
	return false;
}

void Nest::init(sf::Vector2f pos)
{
	m_alive = true;

	m_missileReloadTimer = COOLDOWN_TIMER;
	m_wanderTime = 0;
	m_health = MAX_HEALTH;
	m_state = Wander;
	m_direction = Left;
	m_spawnTimer = 0;

	m_animatedSprite.setPosition(pos);
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);

	m_animatedSprite1.setOrigin(m_animatedSprite1.getLocalBounds().width * 0.5f, m_animatedSprite1.getLocalBounds().height * 0.5f);

	// DEBUGGING CODE
	/////////////////////////////////////////////
	/*m_evadeRadius = sf::CircleShape(EVADE_RANGE);
	m_evadeRadius.setFillColor(sf::Color::Transparent);
	m_evadeRadius.setOutlineThickness(3);
	m_evadeRadius.setOutlineColor(sf::Color::Yellow);
	m_evadeRadius.setOrigin(EVADE_RANGE, EVADE_RANGE);

	m_missileRadius = sf::CircleShape(MISSILE_RANGE);
	m_missileRadius.setFillColor(sf::Color::Transparent);
	m_missileRadius.setOutlineThickness(3);
	m_missileRadius.setOutlineColor(sf::Color::Magenta);
	m_missileRadius.setOrigin(MISSILE_RANGE, MISSILE_RANGE);*/
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

AnimatedSprite Nest::drawElectricity()
{
	return m_animatedSprite1;
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
		SoundPlayer::Instance()->play(SoundEffect::Explosion);
		m_velocity = sf::Vector2f(0, 0);
		if (m_currAnimation != &m_animations[Anims::Explode])
		{
			Score::Instance()->increaseScore(200);
		}
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
