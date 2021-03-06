#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include "SoundPlayer.h"


Player::Player()
	: m_velocity(0, 0)
	, m_accel(0,0)
	, m_animatedSprite(sf::seconds(0.1f), true, true)
	, m_animations(NUM_OF_ANIMS)
	, m_teleportedState(SmartBomb::Ready)
	, m_smartBombState(SmartBomb::Charging)
	, m_smartBombTimer(0)
	, m_bulletTimer(1)
	, m_directionX(Right)
	, m_health(100)
	, m_gameOver(false)
{
}


Player::~Player()
{
}

void Player::init(sf::Texture & tex, sf::Vector2f pos, sf::Vector2i tpBounds)
{

	m_teleportingBounds = tpBounds;

	m_animations[Anims::MoveUp].setSpriteSheet(tex);
	m_animations[Anims::MoveUp].addFrame(sf::IntRect(5, 333, 128, 72));
	//m_animations[Anims::MoveUp].addFrame(sf::IntRect(154, 88, 128, 90));

	m_animations[Anims::MoveDown].setSpriteSheet(tex);
	m_animations[Anims::MoveDown].addFrame(sf::IntRect(5, 433, 128, 78));
	//m_animations[Anims::MoveDown].addFrame(sf::IntRect(154, 188, 128, 96));


	m_animations[Anims::MoveSideways].setSpriteSheet(tex);
	m_animations[Anims::MoveSideways].addFrame(sf::IntRect(5, 237, 128, 69));

	m_animations[Anims::Explosion].setSpriteSheet(tex);
	m_animations[Anims::Explosion].addFrame(sf::IntRect(0, 144, 80, 80));
	m_animations[Anims::Explosion].addFrame(sf::IntRect(80, 144, 80, 80));
	m_animations[Anims::Explosion].addFrame(sf::IntRect(160, 144, 80, 80));
	m_animations[Anims::Explosion].addFrame(sf::IntRect(240, 144, 80, 80));
	m_animations[Anims::Explosion].addFrame(sf::IntRect(320, 144, 80, 80));
	m_animations[Anims::Explosion].addFrame(sf::IntRect(400, 144, 80, 80));
	m_animations[Anims::Explosion].addFrame(sf::IntRect(480, 144, 80, 80));
	m_animations[Anims::Explosion].addFrame(sf::IntRect(560, 144, 80, 80));

	m_animatedSprite.setOrigin(64, 35);
	m_animatedSprite.setPosition(pos);
	m_currAnimation = &m_animations[Anims::MoveSideways];

	/////////////// OUTLINE OF player
	m_playerCollider = sf::CircleShape(PLAYER_RADIUS);
	m_playerCollider.setFillColor(sf::Color::Transparent);
	m_playerCollider.setOutlineThickness(3);
	m_playerCollider.setOutlineColor(sf::Color::Cyan);
	m_playerCollider.setOrigin(PLAYER_RADIUS, PLAYER_RADIUS);
}

void Player::update(sf::Time deltaTime)
{
	m_animatedSprite.play(*m_currAnimation);

	Move(deltaTime);
	updateSmartBomb(deltaTime);
	m_playerCollider.setPosition(m_animatedSprite.getPosition());
	if (m_bulletTimer < BULLET_RELOAD_TIME)
	{
		m_bulletTimer += deltaTime.asMilliseconds();
	}
	
}

void Player::Move(sf::Time deltaTime)
{
	if (m_currAnimation != &m_animations[Anims::Explosion])
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
				SoundPlayer::Instance()->play(SoundEffect::Lazer);
				if (BulletManager::Instance()->createLaser(sf::Vector2f(m_animatedSprite.getPosition().x , m_animatedSprite.getPosition().y +10), MAX_SPEED, m_directionX, 1, true))
					m_bulletTimer = 0;
			}
		}
		// One Time Teleporter
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && m_teleportedState == SmartBomb::Ready)
		{
			m_teleportedState = SmartBomb::Fired;
			teleport(deltaTime);
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
	}
	else
	{
		if (m_animatedSprite.getFrame() >= MAX_FRAMES_EXPLOSION)
		{
			m_gameOver = true;
		}
	}
	m_animatedSprite.update(deltaTime);
}

AnimatedSprite Player::draw()
{
	return m_animatedSprite;
}

void Player::teleport(sf::Time deltaTime)
{
	int randX = rand() % m_teleportingBounds.y;
	m_animatedSprite.setPosition(randX, m_animatedSprite.getPosition().y);
}

int Player::getTeleport()
{
	return m_teleportedState;
}

void Player::disableTeleporter()
{
	m_teleportedState = SmartBomb::Disable;
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

void Player::setDamage(int damage)
{
	if (m_currAnimation != &m_animations[Anims::Explosion])
	{

		m_health -= damage;
		if (m_health < 0)
		{
			SoundPlayer::Instance()->play(SoundEffect::Explosion);
			m_currAnimation = &m_animations[Anims::Explosion];
			m_animatedSprite.setOrigin(40, 40);
			m_animatedSprite.setScale(2, 2);
			m_health = 0;
			m_animatedSprite.play(*m_currAnimation);
		}
		else if (m_health >= 100)
		{
			m_health = 100;
		}
	}
}

int Player::getHealth()
{
	return m_health;
}

int Player::getRadius()
{
	return PLAYER_RADIUS;
}

bool Player::gameOver()
{
	return m_gameOver;
}



sf::Vector2f Player::getPosition()
{
	return m_animatedSprite.getPosition();
}

void Player::setPosition(sf::Vector2f pos)
{
	m_animatedSprite.setPosition(pos);
}

sf::CircleShape Player::drawPlayerOutline()
{
	return m_playerCollider;
}

sf::Vector2f Player::getVel()
{
	return m_velocity;
}

sf::Vector2f Player::getAccel()
{
	return m_accel;
}
