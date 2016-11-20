#include "stdafx.h"
#include "Player.h"
#include <iostream>


Player::Player()
	: m_velocity(0, 0)
	, m_accel(0,0)
	, m_animatedSprite(sf::seconds(0.1f), true, true)
	, m_animations(NUM_OF_ANIMS)
	, m_teleported(false)
	, m_smartBombState(SmartBomb::Charging)
	, m_smartBombTimer(0)
	, m_bulletTimer(1)
	, m_directionX(Right)
	, m_health(100)
{
}


Player::~Player()
{
}

void Player::init(sf::Texture & tex, sf::Vector2f pos, sf::Vector2i tpBounds)
{
	m_teleportingBounds = tpBounds;

	m_animations[Anims::MoveUp].setSpriteSheet(tex);
	m_animations[Anims::MoveUp].addFrame(sf::IntRect(5, 100, 128, 72));
	//m_animations[Anims::MoveUp].addFrame(sf::IntRect(154, 88, 128, 90));

	m_animations[Anims::MoveDown].setSpriteSheet(tex);
	m_animations[Anims::MoveDown].addFrame(sf::IntRect(5, 200, 128, 78));
	//m_animations[Anims::MoveDown].addFrame(sf::IntRect(154, 188, 128, 96));


	m_animations[Anims::MoveSideways].setSpriteSheet(tex);
	m_animations[Anims::MoveSideways].addFrame(sf::IntRect(5, 4, 128, 69));


	m_animatedSprite.setOrigin(64, 35);
	m_animatedSprite.setPosition(pos);
	m_currAnimation = &m_animations[Anims::MoveSideways];
}

void Player::update(sf::Time deltaTime)
{
	m_animatedSprite.play(*m_currAnimation);
	Move(deltaTime);
	updateSmartBomb(deltaTime);

	if (m_bulletTimer < BULLET_RELOAD_TIME)
	{
		m_bulletTimer += deltaTime.asMilliseconds();
	}
}

void Player::Move(sf::Time deltaTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_currAnimation = &m_animations[Anims::MoveSideways];
		m_animatedSprite.setScale(-1, 1);
		if (m_directionX == Right)
		{
			m_accel.x *= 0.5;
		}
		m_directionX = Left;

		if (m_accel.x > -MAX_SPEED)
		{
			m_accel.x -= 10;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_currAnimation = &m_animations[Anims::MoveSideways];
		m_animatedSprite.setScale(1, 1);
		if (m_directionX == Left)
		{
			m_accel.x *= 0.5;
		}
		m_directionX = Right;

		if (m_accel.x < MAX_SPEED)
		{
			m_accel.x += 10;
		}
	}
	else
	{
		if (m_accel.x != 0)
		{
			if (m_accel.x < 0)
			{
				m_accel.x += DE_ACCEL;
			}
			else if (m_accel.x > 0)
			{
				m_accel.x -= DE_ACCEL;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_currAnimation = &m_animations[Anims::MoveUp];
		m_directionY = Up; 
		m_velocity.y = -MAX_SPEED * 0.5f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_currAnimation = &m_animations[Anims::MoveDown];
		m_directionY = Down;
		m_velocity.y = MAX_SPEED * 0.5f;
	}
	else
	{
		m_currAnimation = &m_animations[Anims::MoveSideways];
	}
	// Fire Lazers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (m_bulletTimer >= BULLET_RELOAD_TIME)
		{
			if(BulletManager::Instance()->createLaser(m_animatedSprite.getPosition(), m_accel.x, m_directionX, 1, true))
				m_bulletTimer = 0;
		}
	}
	// One Time Teleporter
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && !m_teleported)
	{
		m_teleported = true;
		teleport();
	}
	// Smart Bomb
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && m_smartBombState == SmartBomb::Ready)
	{
		m_smartBombState = SmartBomb::Fired;
		m_smartBombTimer = 0;
	}

	m_velocity.x = m_accel.x * deltaTime.asSeconds();
	m_velocity.y *= deltaTime.asSeconds();

	m_animatedSprite.move(m_velocity.x, m_velocity.y);
	m_animatedSprite.update(deltaTime);
}

AnimatedSprite Player::draw()
{
	return m_animatedSprite;
}

void Player::teleport()
{
	int randX = rand() % m_teleportingBounds.y + m_teleportingBounds.x;
	m_animatedSprite.setPosition(randX, m_animatedSprite.getPosition().y);
}

int Player::getSmartBombState()
{
	return m_smartBombState;
}

void Player::chargeSmartBomb()
{
	m_smartBombState = SmartBomb::Charging;
}

void Player::updateSmartBomb(sf::Time deltaTime)
{
	if (m_smartBombState == SmartBomb::Charging)
	{
		m_smartBombTimer += deltaTime.asSeconds();
		if (m_smartBombTimer >= SMART_BOMB_RELOAD_TIME)
		{
			m_smartBombState = SmartBomb::Ready;
		}
	}
}

int Player::getHealth()
{
	return m_health;
}
