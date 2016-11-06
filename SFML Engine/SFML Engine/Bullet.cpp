#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
	: m_alive(false)
	, m_rotation(0)
	, m_animatedSprite(sf::seconds(0.2f), true, false)
	, m_animations(NUM_OF_ANIMS)
{
}

Bullet::~Bullet()
{
}

void Bullet::init(sf::Texture & tex)
{
	m_animations[Type::Lazer].setSpriteSheet(tex);
	m_animations[Type::Lazer].addFrame(sf::IntRect(158, 0, 34, 9));

	m_animations[Type::Missile].setSpriteSheet(tex);
	m_animations[Type::Missile].addFrame(sf::IntRect(94, 0, 50, 32));
}

// bool playerBullet - decides if the player has fired or the com. Useful for collisions 
void Bullet::setUpBullet(sf::Vector2f position, int direction, int type, bool playerBullet)
{
	m_alive = true;
	m_type = type;
	m_playerBullet = playerBullet;
	m_direction = direction;
	m_velocity.x = BULLET_SPEED * m_direction;

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
	m_alive = true;
	m_playerBullet = false;
	m_type = type;
	m_currAnimation = &m_animations[Type::Missile];
	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(position);
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);

	m_velocity = targetPosition - position;
	m_velocity = Helper::GetInstance().Normalize(m_velocity);
	m_rotation = std::atan2(m_velocity.y, m_velocity.x);
}

void Bullet::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
	m_animatedSprite.play(*m_currAnimation);
	if (m_type == Missile)
	{
		m_ttl += deltaTime.asSeconds();
		//if (m_ttl > MISSILE_TTL)
		//{
		//	m_type = Explosion;
		//	m_currAnimation = &m_animations[Type::Explosion];
		//}
		//else
		//{
			m_velocity = playerPos - m_animatedSprite.getPosition();
			m_velocity = Helper::GetInstance().Normalize(m_velocity);
			m_velocity.x *= MISSILE_SPEED;
			m_velocity.y *= MISSILE_SPEED;
			float rotation = std::atan2(m_velocity.y, m_velocity.x);

			// Add some magic to rotate only a little and not instantly


			m_animatedSprite.setRotation(rotation * ANGLE_TO_RADS);
		//}
	}
	else if (m_type == Explosion)
	{
		if (m_animatedSprite.getFrame() > MAX_FRAMES_EXPLOSION)
			m_alive = false;
	}
	m_animatedSprite.move(m_velocity * deltaTime.asSeconds());
	m_animatedSprite.update(deltaTime);
}

bool Bullet::isAlive()
{
	return m_alive;
}

int Bullet::getType()
{
	return m_type;
}

AnimatedSprite Bullet::draw()
{
	return m_animatedSprite;
}
