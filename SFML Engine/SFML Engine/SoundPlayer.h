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

	static SoundPlayer * Instance();	 /*!< Instance of the Sound Player to be accessed by other classes*/
	void play(SoundEffect::ID effect);	 /*!< Function to play the sound effect*/
	void removeStoppedSounds();			 /*!< Function to remove sounds from buffer that aren't playing*/

private:

	SoundBufferHolder m_soundBuffers;	 /*!< Soundbuffer to load and hold different sound effects*/
	std::list<sf::Sound> m_sounds;		 /*!< List of sound effects to be played*/

	static SoundPlayer *m_inst;			 /*!< Used for creation of sound player instance*/

	// Disallow Copying
	SoundPlayer(const SoundPlayer&);
	SoundPlayer& operator=(const SoundPlayer&);

	SoundPlayer();						/*!< Constructor loads in sound effects*/
	~SoundPlayer();
};

