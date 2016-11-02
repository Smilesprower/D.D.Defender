#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "SceneStack.h"
#include "SceneIdentifiers.h"
#include "SoundPlayer.h"

class Application
{
public:
	Application();
	void run();

private:
	void handleInput();					// Handles Input and Events
	void update(sf::Time deltaTime);	// Update
	void render();						// Draw
	void createScenes();				// Creating our states

private:

	sf::RenderWindow m_window;
	TextureHolder m_textures;
	FontHolder m_fonts;
	SceneStack m_sceneStack;
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
};

