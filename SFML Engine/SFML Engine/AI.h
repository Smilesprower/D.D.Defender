#pragma once
#include "AnimatedSprite.h"
class AI
{
public:
	~AI();
	AI();
	virtual void Init() = 0;
	virtual void Update(sf::Time pTime, sf::Vector2f pTargetPosition) = 0;
	virtual AnimatedSprite draw() = 0;

protected:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	AnimatedSprite m_sprite;

};

