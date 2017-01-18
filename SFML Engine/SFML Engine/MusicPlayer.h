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
	void play(Music::ID effect);
	void stop();


private:
	sf::Music m_music;
	std::vector<std::string> m_musicPaths;

	static MusicPlayer *m_inst;

	// Disallow Copying
	MusicPlayer(const MusicPlayer&);
	MusicPlayer& operator=(const MusicPlayer&);
	MusicPlayer();
	~MusicPlayer();
};

