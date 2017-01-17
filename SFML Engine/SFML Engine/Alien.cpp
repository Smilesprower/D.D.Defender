#include "stdafx.h"
#include "Alien.h"
#include "Score.h"


Alien::Alien(sf::Texture & tex, sf::Vector2i screenBounds, sf::Vector2i worldBounds)
	: m_animatedSprite(sf::seconds(0.1f), true, false)
	, m_animations(NUM_OF_ANIMS)
	, m_currentState(Blank)
	, m_screenBounds(screenBounds)
	, m_worldBounds(sf::Vector2i(worldBounds.x, worldBounds.y + abs(worldBounds.x)))
	, m_alive(false)
	, m_health(100)
{
	m_animations[Anims::Default].setSpriteSheet(tex);
	m_animations[Anims::Default].addFrame(sf::IntRect(287, 231, 173, 105));

	m_animations[Anims::Abduct].setSpriteSheet(tex);
	m_animations[Anims::Abduct].addFrame(sf::IntRect(462, 231, 174, 380));

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

Alien::~Alien()
{
}

void Alien::init(sf::Vector2f position)
{
	m_currentState = Flock;
	m_alive = true;
	m_velocity = sf::Vector2f(rand() % 101 + (-50) , rand() % 101 + (-50)); // Allows for range of -2 -> 2
	m_position = position;
	m_health = 100;

	m_currAnimation = &m_animations[Anims::Default];
	m_animatedSprite.setScale(1, 1);
	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(position);
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);
	m_animatedSprite.setScale(1, 1);
}

sf::Vector2f Alien::separation(std::vector<Alien*>* alien, int index)
{
	sf::Vector2f steer;
	int neighbourCount = 0;
	float neighbordist = 175;

	for (int i = 0; i < alien->size(); i++)
	{
		if (m_alive && m_currentState == Flock)
		{
			if (Helper::Distance(m_animatedSprite.getPosition(), alien->at(i)->getPosition()) < neighbordist)
			{
				steer += alien->at(i)->getPosition() - m_animatedSprite.getPosition();
				neighbourCount++;
			}
		}
	}
	if (neighbourCount == 0)
		return steer;
	else
	{
		steer.x /= neighbourCount;
		steer.y /= neighbourCount;

		steer.x *= -1;
		steer.y *= -1;
		steer = Helper::Normalize(steer);
		return steer;
	}
}

sf::Vector2f Alien::alignment(std::vector<Alien*>* alien, int index)
{
	sf::Vector2f vel;
	int neighbourCount = 0;
	float neighbordist = 200;

	for (int i = 0; i < alien->size(); i++)
	{
		if (m_alive && m_currentState == Flock )
		{
			if (Helper::Distance(m_animatedSprite.getPosition(), alien->at(i)->getPosition()) < neighbordist)
			{
				vel += alien->at(i)->m_velocity;
				neighbourCount++;
			}
		}
	}
	if (neighbourCount == 0)
		return vel;
	else
	{
		vel.x /= neighbourCount;
		vel.y /= neighbourCount;
		vel = Helper::Normalize(vel);
		return vel;
	}
}

sf::Vector2f Alien::cohesion(std::vector<Alien*>* alien, int index)
{
	sf::Vector2f pos;
	int neighbourCount = 0;
	float neighbordist = 200;

	for (int i = 0; i < alien->size(); i++)
	{
		if (m_alive && m_currentState == Flock)
		{
			if (Helper::Distance(m_animatedSprite.getPosition(), alien->at(i)->getPosition()) < neighbordist)
			{
				pos += alien->at(i)->getPosition();
				neighbourCount++;
			}
		}
	}
	if (neighbourCount == 0)
		return pos;
	else
	{
		pos.x /= neighbourCount;
		pos.y /= neighbourCount;
		sf::Vector2f temp{pos - m_animatedSprite.getPosition()};
		temp = Helper::Normalize(temp);
		return temp;
	}
}

bool Alien::run(std::vector<Alien*> *alien, sf::Time deltaTime, sf::Vector2f playerPos, int index)
{
	bool spawnMutant = false;

	if (m_alive)
	{
		checkBounds();
		if (m_currentState == Flock)
		{
			flock(alien, index);
			updateFlocking(deltaTime, playerPos);
			borders();
		}
		else if (m_currentState == Capture || m_currentState == Target)
		{
			spawnMutant = updateTargetCapture(deltaTime);
		}
		else
		{
			updateDying(deltaTime);
		}
	}
	return spawnMutant;
}

void Alien::updateFlocking(sf::Time deltaTime, sf::Vector2f playerPos)
{
	m_bulletReloadTimer += deltaTime.asSeconds();
	float distanceSquared;
	float dx = m_animatedSprite.getPosition().x - playerPos.x;
	float dy = m_animatedSprite.getPosition().y - playerPos.y;
	distanceSquared = (dx*dx) + (dy*dy);

	if (distanceSquared < BULLET_RANGE * BULLET_RANGE)
	{
		if (m_bulletReloadTimer >= BULLET_COOLDOWN_TIMER)
		{
			if (BulletManager::Instance()->createEBullet(m_animatedSprite.getPosition(), playerPos, 4, false));
			{
				m_bulletReloadTimer = 0;
			}
		}
	}
	m_animatedSprite.move(m_velocity * deltaTime.asSeconds());
	m_animatedSprite.update(deltaTime);
}

bool Alien::updateTargetCapture(sf::Time dt)
{
	bool outOfScreen = false;
	sf::Vector2f vel;
	if (m_currentState == Target)
	{
		sf::Vector2f tPos = m_astro->getAbductPosition();
		sf::Vector2f pos = m_animatedSprite.getPosition();
		vel = tPos - pos;
		vel = Helper::Normalize(vel);
		vel = sf::Vector2f(vel.x * TARGET_SPEED * dt.asSeconds(), vel.y * TARGET_SPEED * dt.asSeconds());
		m_animatedSprite.move(vel.x, vel.y);
		if (pos.x > tPos.x - 10 && pos.x < tPos.x + 10 && pos.y > tPos.y - 10 && pos.y < tPos.y + 10)
		{
			m_currentState = Capture;
			m_currAnimation = &m_animations[Anims::Abduct];
			m_animatedSprite.play(*m_currAnimation);
			m_astro->setAbducted();
			m_velocity = sf::Vector2f(0, 0);
		}
	
	}
	else if (m_currentState == Capture)
	{
		vel = sf::Vector2f(0, -100);
		vel *= dt.asSeconds();

		/*
		ADD CODE HERE TO SAY IF OFF SCREEN

		m_astro gives you access to the astronaut
		make sure u set him to NULL when your done with him
		*/
		if (m_animatedSprite.getPosition().y < -200)
		{
			outOfScreen = true;
			m_alive = false;
			m_astro->setAlive(false);
			m_astro = NULL;
			Score::Instance()->removeAstro();
		}

	}
	m_animatedSprite.move(vel.x, vel.y);
	return outOfScreen;
}

void Alien::updateDying(sf::Time dt)
{
	m_animatedSprite.update(dt);
	if (m_animatedSprite.getFrame() > 3)
	{
		m_alive = false;
		if (m_astro != NULL)
		{
			m_astro->setFalling();
			m_astro->setTargeted(false);
			m_astro = NULL;
		}
	}
}

void Alien::borders()
{
	if (m_animatedSprite.getPosition().y < 300)	
	{
		m_velocity.y = abs(m_velocity.y);
	}
	else if (m_animatedSprite.getPosition().y >(m_screenBounds.y - 300))
	{
		m_velocity.y = abs(m_velocity.y) * -1;
	}
}

void Alien::flock(std::vector<Alien*> *alien, int index)
{
	sf::Vector2f sep = separation(alien, index);
	sf::Vector2f ali = alignment(alien, index);
	sf::Vector2f coh = cohesion(alien, index);

	if (sep == sf::Vector2f{ 0,0 } && ali == sf::Vector2f{ 0,0 } && coh == sf::Vector2f{ 0,0 })
	{
		return;
	}

	m_velocity.x = ali.x + coh.x  + sep.x * 1.5f;
	m_velocity.y = ali.y + coh.y  + sep.y * 1.5f;
	m_velocity = Helper::Normalize(m_velocity);
	m_velocity *= 150.f;
}

bool Alien::getAlive()
{
	return m_alive;
}

void Alien::setAlive(bool alive)
{
	m_alive = alive;
}

void Alien::setState(int state)
{
	m_currentState = state;
}

int Alien::getRadius()
{
	return RADIUS;
}

int Alien::getAbductRadius()
{
	return ABDUCT_RADIUS;
}

void Alien::setDamage(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		if (m_currAnimation != &m_animations[Anims::Explode])
		{
			Score::Instance()->increaseScore(50);
		}
		m_currentState = Dying;
		m_currAnimation = &m_animations[Anims::Explode];
		m_animatedSprite.setOrigin(40, 40);
		m_animatedSprite.setScale(2, 2);
		m_health = 0;
		m_animatedSprite.play(*m_currAnimation);
		Score::Instance()->setKillStreak();

	}
}

int Alien::getHealth()
{
	return m_health;
}

sf::Vector2f Alien::getPosition()
{
	return m_animatedSprite.getPosition();
}

void Alien::setPosition(sf::Vector2f position)
{
	m_animatedSprite.setPosition(position);
}

void Alien::setAstro(Astronaut * astro)
{
	m_astro = astro;
}

int Alien::getState()
{
	return m_currentState;
}

AnimatedSprite Alien::draw()
{
	return m_animatedSprite;
}

void Alien::checkBounds()
{

	if (m_animatedSprite.getPosition().x - m_animatedSprite.getLocalBounds().width * 0.5f >= m_worldBounds.y)
	{
		m_animatedSprite.setPosition(m_worldBounds.x - m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getPosition().y);
	}
	else if (m_animatedSprite.getPosition().x + m_animatedSprite.getLocalBounds().width * 0.5f <= m_worldBounds.x)
	{
		m_animatedSprite.setPosition(m_worldBounds.y + m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getPosition().y);
	}
}

int Alien::getCurrentState()
{
	return m_currentState;
}

