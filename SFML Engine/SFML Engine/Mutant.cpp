#include "stdafx.h"
#include "Mutant.h"

float pi = 3.141592653589793;

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
	m_location = Pvector(pos.x, pos.y);
	m_maxSpeed = 20;
	m_alive = true;
	m_health = 100;
	m_velocity = Pvector(0,300);
	m_currAnimation = &m_animations[Anims::Default];
	m_animatedSprite.setScale(1, 1);
	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(pos);
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);
	m_animatedSprite.setScale(1, 1);
}
void Mutant::update(Mutant *mutant, int mutantSize, bool leader, int currentMutant, sf::Time deltaTime, sf::Vector2f playerPos)
{
	bool changeVel = true;
	if (m_state == Start)
	{
		if (m_animatedSprite.getPosition().y > 200)
		{
			m_velocity.y = 0;
			m_state = FormationA;
		}
	}
	else if (m_state == FormationA)
	{
		Pvector	sub(0, 0);
		Pvector sum(0, 0);
		int npcRadius = 60;
		int closeEnough = 30;
		float angleAroundCircle = 0.0;
		Pvector targetSlot(0, 0);

		//if (leader)
		//{
		//	float temp = abs(m_location.x - playerPos.x - m_location.y - playerPos.y);
		//	if (temp > 100 || -temp < 100)
		//	{
		//		m_acceleration = seek(playerPos);
		//	}
		//	m_velocity.normalize();
		//	m_velocity.mulScalar(m_maxSpeed);
		//	applyForce(sum);
		//}
		//else
		//{
			angleAroundCircle = (float)currentMutant / (mutantSize);
			angleAroundCircle = angleAroundCircle * pi * 2;
			float radius = npcRadius / sin(pi / (mutantSize));

			targetSlot = Pvector(playerPos.x , playerPos.y);
			targetSlot.x = targetSlot.x + radius * cos(angleAroundCircle);
			targetSlot.y = targetSlot.y + radius * sin(angleAroundCircle);
			sub = sub.subTwoVector(targetSlot, m_location);
			float D = sub.magnitude();
			if (D > closeEnough)
			{
				sum = sub;
				sum.normalize();
				sum.mulScalar(m_maxSpeed);
				applyForce(sum);
			}
			else
			{
				//m_velocity = mutant->getVelocity();
				changeVel = false;
				m_velocity = Pvector{ 0,0 };
			}
		/*}*/
	}
	if (changeVel)
	{
		m_acceleration.mulScalar(.9);
		m_velocity.addVector(m_acceleration);
		m_velocity.limit(m_maxSpeed);
		m_location.addVector(m_velocity);
	}

	sf::Vector2f vel{ m_velocity.x , m_velocity.y };
	m_animatedSprite.move(vel);
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

void Mutant::applyForce(Pvector force)
{
	m_acceleration.addVector(force);
}

Pvector Mutant::seek(sf::Vector2f playerpos)
{
	Pvector desired{ playerpos.x, playerpos.y};
	desired.subVector(m_location);
	desired.normalize();
	desired.mulScalar(m_maxSpeed);
	desired.subVector(m_velocity);
	m_acceleration = desired;
	m_acceleration.limit(m_maxForce);
	return m_acceleration;
}

Pvector Mutant::getVelocity()
{
	return m_velocity;
}
