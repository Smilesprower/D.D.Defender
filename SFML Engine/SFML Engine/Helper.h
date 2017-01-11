#pragma once
#include <SFML/Graphics.hpp>
class Helper
{
public:
	~Helper();
	static Helper & GetInstance();
	float Distance(sf::Vector2f a, sf::Vector2f b);
	float Length(sf::Vector2f) const;
	float LengthSquared(sf::Vector2f) const;
	sf::Vector2f Normalize(sf::Vector2f);
	sf::Vector2f DivScaler(sf::Vector2f a, float s);
private:
	Helper();
	Helper(Helper const&);
};
