#include "stdafx.h"
#include "Alien.h"


Alien::Alien()
	: m_animatedSprite(sf::seconds(0.2f), true, false)
	, m_animations(NUM_OF_ANIMS)
	, m_acceleration(0,0)
	, m_maxSpeed(3.5)
	, m_maxForce(0.5)
	, m_currentState(Flock)
	, m_alive(false)
{
}

Alien::~Alien()
{
}

void Alien::init(sf::Texture & tex, sf::Vector2f position, sf::Vector2i screenBounds)
{
	m_acceleration = Pvector(0, 0);
	m_velocity = Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
	m_maxSpeed = 3.5;
	m_maxForce = 0.5;
	m_location.x = position.x;
	m_location.y = position.y;
	m_screenBounds = screenBounds;

	m_animations[Anims::Default].setSpriteSheet(tex);
	m_animations[Anims::Default].addFrame(sf::IntRect(287, 231, 173, 105));
	m_currAnimation = &m_animations[Anims::Default];
	m_animatedSprite.play(*m_currAnimation);
	m_animatedSprite.setPosition(position);
	m_animatedSprite.setOrigin(m_animatedSprite.getLocalBounds().width * 0.5f, m_animatedSprite.getLocalBounds().height * 0.5f);
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
		float d = m_location.distance(alien->at(i)->m_location);
		if ((d > 0) && (d < neighbordist)) // 0 < d < 50
		{
			sum.addVector(alien->at(i)->m_velocity);
			count++;
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
		float d = m_location.distance(alien->at(i)->m_location);
		if ((d > 0) && (d < neighbordist))
		{
			sum.addVector(alien->at(i)->m_location);
			count++;
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
	else if (m_currentState == Capture)
	{
		updateCapture(deltaTime);
	}
	else
	{
		updateDying(deltaTime);
	}
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

void Alien::updateCapture(sf::Time dt)
{
}

void Alien::updateDying(sf::Time dt)
{
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

int Alien::getState()
{
	return m_currentState;
}

AnimatedSprite Alien::draw()
{
	return m_animatedSprite;
}

