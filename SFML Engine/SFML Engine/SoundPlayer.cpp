#include "stdafx.h"
#include "SoundPlayer.h"

SoundPlayer * SoundPlayer::m_inst = nullptr;
SoundPlayer::SoundPlayer()
	: m_soundBuffers()
	, m_sounds()
{
	// Load Sounds
	m_soundBuffers.load(SoundEffect::Charge, "../resources/sfx/charge.wav");
}
SoundPlayer::~SoundPlayer()
{
}

SoundPlayer * SoundPlayer::Instance()
{
	if (!m_inst)
	{
		m_inst = new SoundPlayer();
	}
	return m_inst;
}

void SoundPlayer::play(SoundEffect::ID effect)
{
	m_sounds.push_back(sf::Sound(m_soundBuffers.get(effect)));    
	m_sounds.back().play();
}

void SoundPlayer::removeStoppedSounds()
{
	m_sounds.remove_if([](const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	});

}
