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
