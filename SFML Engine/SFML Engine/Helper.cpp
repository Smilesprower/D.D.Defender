#include "stdafx.h"
#include "Helper.h"


Helper::Helper()
{
}


Helper::~Helper()
{
}

Helper & Helper::GetInstance()
{
	static Helper instance;
	return instance;
}

float Helper::Distance(sf::Vector2f a, sf::Vector2f b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dist = sqrt(dx*dx + dy*dy); //Based on definition of distance formula
	return dist;
}

float Helper::Length(sf::Vector2f pVel) const{
	return sqrt((pVel.x  * pVel.x) + (pVel.y * pVel.y));
}

float Helper::LengthSquared(sf::Vector2f pVel) const{
	return pVel.x *pVel.x + pVel.y * pVel.y;
}

sf::Vector2f Helper::Normalize(sf::Vector2f pVel)
{
	if (Length(pVel) != 0) {
		float length = Length(pVel);
		pVel.x /= length;
		pVel.y /= length;
		return pVel;
	}
	pVel.x = 0;
	pVel.y = 0;
	return pVel;
}

sf::Vector2f Helper::DivScaler(sf::Vector2f a, float s)
{
	sf::Vector2f temp;
	temp.x = a.x /= s;
	temp.y = a.x /= s;
	return sf::Vector2f(temp);
}

sf::Vector2f Helper::SubTwoVector(sf::Vector2f a, sf::Vector2f b)
{
	return sf::Vector2f(a - b);
}
