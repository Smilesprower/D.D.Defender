#include "stdafx.h"
#include "Mutant.h"
#include "Score.h"

float pi = 3.141592653589793;

Mutant::Mutant(sf::Texture & tex, sf::Vector2i screenBounds, sf::Vector2i worldBounds)
	: m_animatedSprite(sf::seconds(0.1f), true, false)
	, m_animations(NUM_OF_ANIMS)
	, m_screenBounds(screenBounds)
	, m_worldBounds(sf::Vector2i(worldBounds.x, worldBounds.y + abs(worldBounds.x)))
	, m_alive(false)
	, m_health(0)
	, m_kamikazeTimer(0)
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
	m_state = Start;
	m_position = pos;
	m_maxSpeed = 20;
	m_alive = true;
	m_health = 100;
	m_velocity = sf::Vector2f{ 0,300 };
	m_currAnimation = &m_animations[Anims::Default];
	m_animatedSprite.setScale(1, 1);
	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(pos);
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);
	m_animatedSprite.setScale(1, 1);
}
void Mutant::update(int mutantSize, int currentMutant, sf::Time deltaTime, sf::Vector2f playerPos, sf::Vector2f playerVel)
{
	if (m_alive)
	{
		float distanceSquared;
		float dx = m_animatedSprite.getPosition().x - playerPos.x;
		float dy = m_animatedSprite.getPosition().y - playerPos.y;
		distanceSquared = (dx*dx) + (dy*dy);

		mutantSize += 1;
		m_bulletReloadTimer += deltaTime.asSeconds();

		if (m_state == Start)
		{
			if (m_animatedSprite.getPosition().y > 200)
			{
				m_velocity = sf::Vector2f(0, 0);
				m_state = FormationB;
			}
		}
		else if (m_state == FormationA)
		{
			if (mutantSize > 3)
			{
				m_state = FormationB;
			}
		}
		// Circle Formation
		else if (m_state == FormationB)
		{

			if (m_health < 15 || mutantSize < 2)
			{
				m_state = FormationC;
				m_velocity = sf::Vector2f(0, 0);
			}

			sf::Vector2f targetSlot;
			int npcRadius = 175;
			int closeEnough = 175;
			float angleAroundCircle = 0.0;

			angleAroundCircle = ((float)currentMutant) / (mutantSize);
			angleAroundCircle = angleAroundCircle * pi * 2;
			float radius = npcRadius / sin(pi / (mutantSize));

			targetSlot = playerPos;
			targetSlot.x = targetSlot.x + radius * cos(angleAroundCircle);
			targetSlot.y = targetSlot.y + radius * sin(angleAroundCircle);

			m_velocity = targetSlot - m_animatedSprite.getPosition();
			float distance = Helper::Length(m_velocity);

			if (distance > closeEnough)
			{
				m_velocity = Helper::Normalize(m_velocity) * MAX_VELOCITY;
			}
			else
			{
				if (distanceSquared < BULLET_RANGE * BULLET_RANGE)
				{
					if (m_bulletReloadTimer >= BULLET_COOLDOWN_TIMER)
					{
						if (BulletManager::Instance()->createEBullet(m_animatedSprite.getPosition(), playerPos, 5, false));
						{
							m_bulletReloadTimer = 0;
						}
					}
				}
				m_velocity = sf::Vector2f(0, 0);
			}
		}
		// Suicide Bomber
		else if (m_state == FormationC)
		{
			m_velocity = playerPos - m_animatedSprite.getPosition();
			float distance = Helper::Length(m_velocity);
			m_velocity = Helper::Normalize(m_velocity) * 1000.f;
		}
		else if (m_state == Dying)
		{
			if (m_animatedSprite.getFrame() > 3)
			{
				m_alive = false;
			}
		}
		m_animatedSprite.move(m_velocity * deltaTime.asSeconds());
		m_animatedSprite.update(deltaTime);
	}
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
	m_health -= damage;
	if (m_health <= 0)
	{
		if (m_currAnimation != &m_animations[Anims::Explode])
		{
			Score::Instance()->increaseScore(50);
		}

		m_state = Dying;
		m_currAnimation = &m_animations[Anims::Explode];
		m_animatedSprite.setOrigin(40, 40);
		m_animatedSprite.setScale(2, 2);
		m_health = 0;
		m_animatedSprite.play(*m_currAnimation);
		m_velocity = sf::Vector2f(0, 0);
	}
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

int Mutant::getCurrentState()
{
	return m_state;
}

//void Mutant::applyForce(Pvector force)
//{
//	m_acceleration.addVector(force);
//}

//Pvector Mutant::seek(sf::Vector2f playerpos)
//{
//	//Pvector desired{ playerpos.x, playerpos.y};
//	//desired.subVector(m_location);
//	//desired.normalize();
//	//desired.mulScalar(m_maxSpeed);
//	//desired.subVector(m_velocity);
//	//m_acceleration = desired;
//	//m_acceleration.limit(m_maxForce);
//	return m_acceleration;
//}
//
//Pvector Mutant::getVelocity()
//{
//	return m_velocity;
//}
//	Pvector	sub(0, 0);
//	Pvector sum(0, 0);
//	int npcRadius = 60;
//	int closeEnough = 30;
//	float angleAroundCircle = 0.0;
//	Pvector targetSlot(0, 0);

//	//if (leader)
//	//{
//	//	float temp = abs(m_location.x - playerPos.x - m_location.y - playerPos.y);
//	//	if (temp > 100 || -temp < 100)
//	//	{
//	//		m_acceleration = seek(playerPos);
//	//	}
//	//	m_velocity.normalize();
//	//	m_velocity.mulScalar(m_maxSpeed);
//	//	applyForce(sum);
//	//}
//	//else
//	//{
//		angleAroundCircle = (float)currentMutant / (mutantSize);
//		angleAroundCircle = angleAroundCircle * pi * 2;
//		float radius = npcRadius / sin(pi / (mutantSize));

//		targetSlot = Pvector(playerPos.x , playerPos.y);
//		targetSlot.x = targetSlot.x + radius * cos(angleAroundCircle);
//		targetSlot.y = targetSlot.y + radius * sin(angleAroundCircle);
//		sub = sub.subTwoVector(targetSlot, m_location);
//		float D = sub.magnitude();
//		if (D > closeEnough)
//		{
//			sum = sub;
//			sum.normalize();
//			sum.mulScalar(m_maxSpeed);
//			applyForce(sum);
//		}
//		else
//		{
//			//m_velocity = mutant->getVelocity();
//			changeVel = false;
//			m_velocity = Pvector{ 0,0 };
//		}
//	/*}*/
//}
//if (changeVel)
//{
//	m_acceleration.mulScalar(.9);
//	m_velocity.addVector(m_acceleration);
//	m_velocity.limit(m_maxSpeed);
//	m_location.addVector(m_velocity);
//}
