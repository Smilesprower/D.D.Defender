#pragma once
#include <vector>
#include "Alien.h"
class Flock
{
public:
	Flock();
	~Flock();


private:
	std::vector<Alien*> m_flock;
	Alien * getAlien(int i);
	void addAlien(Alien alien);
	void flocking();
	void swarming();
};

