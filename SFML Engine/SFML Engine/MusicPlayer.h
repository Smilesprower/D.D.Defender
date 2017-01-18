/*! \brief Handles Playing and Stopping Music through the game
*
*
*
*/
#pragma once
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio.hpp>
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include <list>

class MusicPlayer
{

public:

	static MusicPlayer * Instance();
	void play(Music::ID effect);		/*!< Plays Music*/
	void stop();						/*!< Stops all Music*/


private:
	sf::Music m_music;						/*!< Contains the music object*/
	std::vector<std::string> m_musicPaths;	/*!< Vector that contains the path to all Music files*/
	static MusicPlayer *m_inst;

	// Disallow Copying
	MusicPlayer(const MusicPlayer&);
	MusicPlayer& operator=(const MusicPlayer&);
	MusicPlayer();
	~MusicPlayer();
};

