#pragma once
#include <SFML/Graphics.hpp>
class Helper
{
public:
	~Helper();
	static Helper & GetInstance();

	float Length(sf::Vector2f) const;
	float LengthSquared(sf::Vector2f) const;
	sf::Vector2f Normalize(sf::Vector2f);

private:
	Helper();
	Helper(Helper const&);
};
