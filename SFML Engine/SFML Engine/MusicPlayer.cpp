#include "stdafx.h"
#include "MusicPlayer.h"

MusicPlayer * MusicPlayer::m_inst = nullptr;
MusicPlayer * MusicPlayer::Instance()
{
	if (!m_inst)
	{
		m_inst = new MusicPlayer();
	}
	return m_inst;
}
void MusicPlayer::play(Music::ID effect)
{
	if (!m_music.openFromFile(m_musicPaths[effect]))
	{
	}
	m_music.play();
}

void MusicPlayer::stop()
{
	m_music.stop();
}

MusicPlayer::MusicPlayer()
{
	m_musicPaths.push_back("../resources/sfx/Menu1.wav");
	m_musicPaths.push_back("../resources/sfx/Stage2.ogg");
	m_musicPaths.push_back("../resources/sfx/Menu2.wav");
}


MusicPlayer::~MusicPlayer()
{
}
