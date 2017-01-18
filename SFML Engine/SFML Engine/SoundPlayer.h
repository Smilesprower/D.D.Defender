/*! \brief Controls the playing of sounds.
*
*
*
*/

#pragma once
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include <list>

class SoundPlayer
{

public:

	static SoundPlayer * Instance();
	void play(SoundEffect::ID effect);
	void removeStoppedSounds();

private:

	SoundBufferHolder m_soundBuffers;
	std::list<sf::Sound> m_sounds;

	static SoundPlayer *m_inst;

	// Disallow Copying
	SoundPlayer(const SoundPlayer&);
	SoundPlayer& operator=(const SoundPlayer&);

	SoundPlayer();
	~SoundPlayer();
};

