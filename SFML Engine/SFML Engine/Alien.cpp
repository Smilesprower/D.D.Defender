#include "stdafx.h"
#include "Alien.h"


Alien::Alien(sf::Texture & tex, sf::Vector2i screenBounds)
	: m_animatedSprite(sf::seconds(0.2f), true, false)
	, m_animations(NUM_OF_ANIMS)
	, m_acceleration(0,0)
	, m_currentState(Blank)
	, m_screenBounds(screenBounds)
	, m_alive(false)
	, m_health(100)
{
	m_animations[Anims::Default].setSpriteSheet(tex);
	m_animations[Anims::Default].addFrame(sf::IntRect(287, 231, 173, 105));

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
	m_acceleration = Pvector(0, 0);
	m_velocity = Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
	m_maxSpeed = 3.5;
	m_maxForce = 0.5;
	m_location.x = position.x;
	m_location.y = position.y;

	m_currAnimation = &m_animations[Anims::Default];
	m_animatedSprite.setScale(1, 1);
	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(position);
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);
	m_animatedSprite.setScale(1, 1);


	// DEBUGGING CODE
	/////////////////////////////////////////////
	m_collisionRadius = sf::CircleShape(ABDUCT_RADIUS);
	m_collisionRadius.setFillColor(sf::Color::Transparent);
	m_collisionRadius.setOutlineThickness(3);
	m_collisionRadius.setOutlineColor(sf::Color::Yellow);
	m_collisionRadius.setOrigin(ABDUCT_RADIUS, ABDUCT_RADIUS);
}

void Alien::applyForce(Pvector force)
{
	m_acceleration.addVector(force);
}

Pvector Alien::separation(std::vector<Alien*> *alien)
{
	float desiredseparation = 175;
	Pvector steer(0, 0);
	int count = 0;
	for (int i = 0; i < alien->size(); i++)
	{
		if (m_alive && m_currentState == Flock)
		{
			float d = m_location.distance(alien->at(i)->m_location);
			if ((d > 0) && (d < desiredseparation))
			{
				Pvector diff(0, 0);
				diff = diff.subTwoVector(m_location, alien->at(i)->m_location);
				diff.normalize();
				diff.divScalar(d);
				steer.addVector(diff);
				count++;
			}
		}
	}
	if (count > 0)
		steer.divScalar((float)count);
	if (steer.magnitude() > 0)
	{
		steer.normalize();
		steer.mulScalar(m_maxSpeed);
		steer.subVector(m_velocity);
		steer.limit(m_maxForce);
	}
	return steer;
}

Pvector Alien::alignment(std::vector<Alien*> *alien)
{
	float neighbordist = 200;

	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < alien->size(); i++)
	{
		if (m_alive && m_currentState == Flock) 
		{
			float d = m_location.distance(alien->at(i)->m_location);
			if ((d > 0) && (d < neighbordist)) // 0 < d < 50
			{
				sum.addVector(alien->at(i)->m_velocity);
				count++;
			}
		}
	}
	// If there are boids close enough for alignment...
	if (count > 0)
	{
		sum.divScalar((float)count);// Divide sum by the number of close boids (average of velocity)
		sum.normalize();	   		// Turn sum into a unit vector, and
		sum.mulScalar(m_maxSpeed);  // Multiply by maxSpeed
									
		Pvector steer;				// Steer = Desired - Velocity
		steer = steer.subTwoVector(sum, m_velocity); //sum = desired(average)  
		steer.limit(m_maxForce);
		return steer;
	}
	else 
	{
		Pvector temp(0, 0);
		return temp;
	}
}

Pvector Alien::cohesion(std::vector<Alien*> *alien)
{
	float neighbordist = 200;

	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < alien->size(); i++)
	{
		if (m_alive && m_currentState == Flock)
		{
			float d = m_location.distance(alien->at(i)->m_location);
			if ((d > 0) && (d < neighbordist))
			{
				sum.addVector(alien->at(i)->m_location);
				count++;
			}
		}
	}
	if (count > 0)
	{
		sum.divScalar(count);
		return seek(sum);
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}

Pvector Alien::seek(Pvector v)
{
	Pvector desired;
	desired.subVector(v);
	desired.normalize();
	desired.mulScalar(m_maxSpeed);
	m_acceleration.subTwoVector(desired, m_velocity);
	m_acceleration.limit(m_maxForce);
	return m_acceleration;
}

void Alien::run(std::vector<Alien*> *alien, sf::Time deltaTime)
{
	if (m_currentState == Flock)
	{
		flock(alien);
		updateFlocking(deltaTime);
		borders();
	}
	else if (m_currentState == Capture || m_currentState == Target)
	{
		updateTargetCapture(deltaTime);
	}
	else
	{
		updateDying(deltaTime);
	}

	//debugging
	m_collisionRadius.setPosition(m_animatedSprite.getPosition());
}

void Alien::updateFlocking(sf::Time deltaTime)
{

	//To make the slow down not as abrupt
	m_acceleration.mulScalar(.9);
	// Update velocity
	m_velocity.addVector(m_acceleration);
	// Limit speed
	m_velocity.limit(m_maxSpeed);
	m_location.addVector(m_velocity);

	//m_circ.setPosition(sf::Vector2f(m_location.x, m_location.y));


	sf::Vector2f vel = sf::Vector2f(m_velocity.x, m_velocity.y);
	m_animatedSprite.move(vel);
	m_animatedSprite.update(deltaTime);

	// Reset accelertion to 0 each cycle
	m_acceleration.mulScalar(0);
}

void Alien::updateTargetCapture(sf::Time dt)
{
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
			m_astro->setAbducted();
			m_velocity = Pvector(0, 0);
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
	}
	m_animatedSprite.move(vel.x, vel.y);
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
	if (m_location.y < 100 || m_location.y > (m_screenBounds.y - 200))
	{
		m_velocity.y *= -1;
	}
}

void Alien::flock(std::vector<Alien*> *alien)
{
	Pvector sep = separation(alien);
	Pvector ali = alignment(alien);
	Pvector coh = cohesion(alien);
	// Arbitrarily weight these forces
	sep.mulScalar(1.5);
	ali.mulScalar(1.0); // Might need to alter weights for different characteristics
	coh.mulScalar(1.0);

	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
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
		m_currentState = Dying;
		m_currAnimation = &m_animations[Anims::Explode];
		m_animatedSprite.setOrigin(40, 40);
		m_animatedSprite.setScale(2, 2);
		m_health = 0;
		m_animatedSprite.play(*m_currAnimation);
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

sf::CircleShape Alien::drawCollisionRadius()
{
	return m_collisionRadius;
}

