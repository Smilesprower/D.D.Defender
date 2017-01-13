#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(sf::Texture & tex)
	: m_enabled(false)
	, m_rotation(0)
	, m_prevRotation(0)
	, m_animatedSprite(sf::seconds(0.1f), true, false)
	, m_animations(NUM_OF_ANIMS)
{
	
	m_animations[Type::Lazer].setSpriteSheet(tex);
	m_animations[Type::Lazer].addFrame(sf::IntRect(158, 0, 34, 9));

	m_animations[Type::Missile].setSpriteSheet(tex);
	m_animations[Type::Missile].addFrame(sf::IntRect(94, 0, 50, 32));

	m_animations[Type::Ball].setSpriteSheet(tex);
	m_animations[Type::Ball].addFrame(sf::IntRect(223, 0, 26, 26));

	m_animations[Type::Explosion].setSpriteSheet(tex);
	m_animations[Type::Explosion].addFrame(sf::IntRect(0, 144, 80, 80));
	m_animations[Type::Explosion].addFrame(sf::IntRect(80, 144, 80, 80));
	m_animations[Type::Explosion].addFrame(sf::IntRect(160, 144, 80, 80));
	m_animations[Type::Explosion].addFrame(sf::IntRect(240, 144, 80, 80));
	m_animations[Type::Explosion].addFrame(sf::IntRect(320, 144, 80, 80));
	m_animations[Type::Explosion].addFrame(sf::IntRect(400, 144, 80, 80));
	m_animations[Type::Explosion].addFrame(sf::IntRect(480, 144, 80, 80));
	m_animations[Type::Explosion].addFrame(sf::IntRect(560, 144, 80, 80));
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::setUpEBullet(sf::Vector2f position, sf::Vector2f targetPosition, int type, bool playerBullet)
{
	m_enabled = true;
	m_ttl = 0;
	m_type = type;
	m_playerBullet = playerBullet;
	m_currAnimation = &m_animations[Type::Ball];

	sf::Vector2f temp = targetPosition - position;
	temp = Helper::Normalize(temp);
	m_rotation = std::atan2(temp.y, temp.x);
	m_velocity = sf::Vector2f(cos(m_rotation) * MISSILE_SPEED, sin(m_rotation)*  MISSILE_SPEED);

	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(position);
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);
}

// bool playerBullet - decides if the player has fired or the com. Useful for collisions 
void Bullet::setUpBullet(sf::Vector2f position, float xSpeed, int direction, int type, bool playerBullet)
{
	m_enabled = true;
	m_ttl = 0;
	m_type = type;
	m_playerBullet = playerBullet;
	m_direction = direction;
	m_velocity.x = (xSpeed + BULLET_SPEED) * m_direction ;
	m_velocity.y = 0;
	if (m_type == Default)
	{
		m_currAnimation = &m_animations[Type::Default];
	}
	else if (m_type == Lazer)
	{
		m_currAnimation = &m_animations[Type::Lazer];
	}
	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(position);
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);
}

void Bullet::setUpMissile(sf::Vector2f position, sf::Vector2f targetPosition, int type)
{
	m_enabled = true;
	m_playerBullet = false;
	m_type = type;
	m_currAnimation = &m_animations[Type::Missile];
	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(position);
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);

	sf::Vector2f temp = targetPosition - position;
	temp = Helper::Normalize(temp);
	m_rotation = std::atan2(temp.y, temp.x);
	m_velocity = sf::Vector2f(cos(m_rotation) * MISSILE_SPEED, sin(m_rotation)*  MISSILE_SPEED);
	m_prevRotation = m_rotation;

}
void Bullet::update(sf::Time deltaTime, sf::Vector2f playerPos, int &missleCount)
{
	if (m_enabled)
	{
		if(m_type != Missile && m_type != Explosion)
		{
			m_animatedSprite.move(m_velocity * deltaTime.asSeconds());
			m_animatedSprite.update(deltaTime);

			m_ttl += deltaTime.asSeconds();
			if (m_ttl > BULLET_TTL)
			{
				m_velocity.x = 0;
				m_velocity.y = 0;
				m_rotation = 0;
				m_enabled = false;
			}
		}
		else
		{
			m_animatedSprite.play(*m_currAnimation);
			if (m_type == Missile)
			{
				m_missileCollider.setPosition(m_animatedSprite.getPosition());
				m_ttl += deltaTime.asSeconds();
				if (m_ttl > MISSILE_TTL)
				{
					m_type = Explosion;
					m_currAnimation = &m_animations[Type::Explosion];
					m_velocity.x = 0;
					m_velocity.y = 0;
					m_rotation = 0;
				}
				else
				{
					sf::Vector2f temp = playerPos - m_animatedSprite.getPosition();
					temp = Helper::Normalize(temp);
					m_rotation = std::atan2(temp.y, temp.x);
					m_velocity = sf::Vector2f(cos(m_rotation) * MISSILE_SPEED, sin(m_rotation)*  MISSILE_SPEED);
				}
				m_animatedSprite.setRotation(m_rotation * ANGLE_TO_RADS);
			}
			else if (m_type == Explosion)
			{
				if (m_animatedSprite.getFrame() > MAX_FRAMES_EXPLOSION)
				{
					m_ttl = 0;
					m_enabled = false;
					missleCount--;
				}
			}
			m_animatedSprite.move(m_velocity * deltaTime.asSeconds());
			m_animatedSprite.update(deltaTime);
		}
	}
}

void Bullet::setPosition(sf::Vector2f newPosition)
{
	m_animatedSprite.setPosition(newPosition);
}

sf::Vector2f Bullet::getPosition()
{
	return m_animatedSprite.getPosition();
}

void Bullet::setEnabled(bool enabled)
{
	m_enabled = enabled;
}

bool Bullet::isEnabled()
{
	return m_enabled;
}

int Bullet::getType()
{
	return m_type;
}

void Bullet::setTTL(int ttl)
{
	m_ttl = ttl;
}


int Bullet::getRadius()
{
	return MISSILE_RADIUS;
}

AnimatedSprite Bullet::draw()
{
	return m_animatedSprite;
}

sf::CircleShape Bullet::drawMissileCollider()
{
	return m_missileCollider;
}
