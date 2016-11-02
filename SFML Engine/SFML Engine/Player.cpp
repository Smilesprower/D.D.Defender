#include "stdafx.h"
#include "Player.h"



Player::Player()
	: m_velocity(0, 0)
	, m_ACCELERATION(0.05)
{
}


Player::~Player()
{
}

void Player::init(sf::Texture & tex, sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
	m_sprite.setTexture(tex);
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5, m_sprite.getTextureRect().height * 0.5);
}

void Player::update(sf::Time deltaTime)
{
	Move(deltaTime);
}

void Player::Move(sf::Time deltaTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_sprite.setScale(-1, 1);
		if (m_directionX == Right)
		{
			m_directionX = Left;
		}

		if (m_velocity.x > -MAX_SPEED)
		{
			m_velocity.x -= 0.1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_sprite.setScale(1, 1);
		if (m_directionX == Left)
		{
			m_directionX = Right;
		}
		if (m_velocity.x < MAX_SPEED)
		{
			m_velocity.x += 0.1;
		}
	}
	else
	{
		if (m_velocity.x != 0)
		{
			if (m_velocity.x < 0)
			{
				m_velocity.x += m_ACCELERATION;
			}
			else if (m_velocity.x > 0)
			{
				m_velocity.x -= m_ACCELERATION;
			}
			if (m_velocity.x > -0.1 && m_velocity.x < 0.1)
			{
				m_velocity.x = 0;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_directionY = Up;
		if (m_velocity.y > -MAX_SPEED)
		{
			m_velocity.y -= 0.5;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_directionY = Down;
		if (m_velocity.y < MAX_SPEED)
		{
			m_velocity.y += 0.5;
		}
	}
	else
	{
		if (m_velocity.y != 0)
		{
			if (m_velocity.y < 0)
			{
				m_velocity.y += m_ACCELERATION;
			}
			else if (m_velocity.y > 0)
			{
				m_velocity.y -= m_ACCELERATION;
			}
			if (m_velocity.y > -0.1 && m_velocity.y < 0.1)
			{
				m_velocity.y = 0;
			}
		}
	}

	m_sprite.move(m_velocity.x, m_velocity.y);
}

sf::Sprite Player::draw()
{
	return m_sprite;
}
