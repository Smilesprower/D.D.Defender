#include "stdafx.h"
#include "Alien.h"


Alien::Alien(sf::Texture & tex, sf::Vector2f position)
{
}

Alien::~Alien()
{
}

void Alien::applyForce(sf::Vector2f force)
{
	m_accel.x += force.x;
	m_accel.y += force.y;
}

sf::Vector2f Alien::separation(std::vector<Alien> alien)
{
	// If the boid we're looking at is a predator, do not run the separation
	// algorithm

	// Distance of field of vision for separation between boids
	float desiredseparation = 20;
	sf::Vector2f steer{0, 0};
	int count = 0;
	// For every boid in the system, check if it's too close
	for (int i = 0; i < alien.size(); i++)
	{
		// Calculate distance from current boid to boid we're looking at
		float d = Helper::GetInstance().Distance(m_position, alien[i].m_position);

		// If this is a fellow boid and it's too close, move away from it
		if ((d > 0) && (d < desiredseparation))
		{
			sf::Vector2f diff{0, 0};
			diff = m_position - alien[i].m_position;
			diff = Helper::GetInstance().Normalize(diff);
			diff = Helper::GetInstance().DivScaler(diff, d);
			steer += diff;
			count++;
		}
		// If current boid is a predator and the boid we're looking at is also
		// a predator, then separate only slightly 
		//if ((d > 0) && (d < desiredseparation) && predator == true && boids[i].predator == true)
		//{
		//	Pvector pred2pred(0, 0);
		//	pred2pred = pred2pred.subTwoVector(location, boids[i].location);
		//	pred2pred.normalize();
		//	pred2pred.divScalar(d);
		//	steer.addVector(pred2pred);
		//	count++;
		//}
		//// If current boid is not a predator, but the boid we're looking at is
		//// a predator, then create a large separation Pvector
		//else if ((d > 0) && (d < desiredseparation + 70) && boids[i].predator == true)
		//{
		//	Pvector pred(0, 0);
		//	pred = pred.subTwoVector(location, boids[i].location);
		//	pred.mulScalar(900);
		//	steer.addVector(pred);
		//	count++;
		//}
	}
	// Adds average difference of location to acceleration
	if (count > 0)
		steer = Helper::GetInstance().DivScaler(steer, (float)count);
		//steer.divScalar((float)count);
	if (steer.magnitude() > 0)
	{
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}
	return steer;
}

void Alien::run(std::vector<Alien> alien, sf::Time deltaTime)
{
	flock(alien);
	update(deltaTime);
	borders();
}
