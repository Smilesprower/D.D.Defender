#pragma once
#include <SFML/Graphics.hpp>
#define PI 3.141592635
class Helper
{
public:
	static float Length(sf::Vector2f v)
	{
		return sqrt((v.x * v.x) + (v.y * v.y));
	}
	static float Helper::LengthSquared(sf::Vector2f v)  
	{
		return v.x *v.x + v.y * v.y;
	}
	static sf::Vector2f Helper::DivScaler(sf::Vector2f v, float s)
	{
		return sf::Vector2f(v.x / s, v.y / s);
	}
	static float Helper::Distance(sf::Vector2f v, sf::Vector2f v2)
	{
		float dx = v.x - v2.x;
		float dy = v.y - v2.y;
		float dist = sqrt(dx*dx + dy*dy);
		return dist;
	}
	static sf::Vector2f Helper::Normalize(sf::Vector2f v)
	{
		if (Length(v) != 0) 
		{
			float length = Length(v);
			v.x /= length;
			v.y /= length;
			return v;
		}
		v.x = 0;
		v.y = 0;
		return v;
	}
	static float Helper::dotProduct(sf::Vector2f v, sf::Vector2f v2)
	{
		float dot = v.x * v2.x + v.y * v2.y;
		return dot;
	}
	static float Helper::angleBetween(sf::Vector2f v, sf::Vector2f v2)
	{
		if (v.x == 0 && v.y == 0) return 0.0f;
		if (v2.x == 0 && v2.y == 0) return 0.0f;

		double dot = v.x * v2.x + v.y * v2.y;
		double v1mag = sqrt(v.x * v.x + v.y * v.y);
		double v2mag = sqrt(v2.x * v2.x + v2.y * v2.y);
		double amt = dot / (v1mag * v2mag);
										
		if (amt <= -1) {
			return PI;
		}
		else if (amt >= 1) {
			return 0;
		}
		float tmp = acos(amt);
		return tmp;
	}

};
