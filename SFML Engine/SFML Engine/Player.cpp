#include "stdafx.h"
#include "Player.h"



Player::Player()
	: m_velocity(0, 0)
	, m_ACCELERATION(0.05)
	, m_animatedSprite(sf::seconds(0.1f), true, true)
	, m_animations(NUM_OF_ANIMS)
{
}


Player::~Player()
{
}

void Player::init(sf::Texture & tex, sf::Vector2f pos)
{
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
}

void Player::Move(sf::Time deltaTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_currAnimation = &m_animations[Anims::MoveSideways];
		m_animatedSprite.setScale(-1, 1);
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
		m_currAnimation = &m_animations[Anims::MoveSideways];
		m_animatedSprite.setScale(1, 1);
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
		m_currAnimation = &m_animations[Anims::MoveUp];

		m_directionY = Up;
		if (m_velocity.y > -MAX_SPEED)
		{
			m_velocity.y -= 0.5;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_currAnimation = &m_animations[Anims::MoveDown];
		m_directionY = Down;
		if (m_velocity.y < MAX_SPEED)
		{
			m_velocity.y += 0.5;
		}
	}
	else
	{
		m_currAnimation = &m_animations[Anims::MoveSideways];
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
	m_velocity.x *= deltaTime.asSeconds();
	m_velocity.y *= deltaTime.asSeconds();
	m_animatedSprite.move(m_velocity.x, m_velocity.y);
	m_animatedSprite.update(deltaTime);
}

AnimatedSprite Player::draw()
{
	return m_animatedSprite;
}
