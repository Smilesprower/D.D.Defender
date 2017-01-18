/*! \brief Handles the input, loading of textures and fonts, creates scenes.
*
*
*
*/
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
	void run();							/*!< Runs gameloop"*/

private:
	void handleInput();					/*!< Handles input for the game "All Scenes"*/
	void update(sf::Time deltaTime);	/*!< Handles update for the game "All Scenes"*/
	void render();						/*!< Handles draw for the game "All Scenes"*/
	void createScenes();				/*!< Creates all game scenes"*/


	sf::RenderWindow m_window;			/*!< Render Window for the game"*/
	TextureHolder m_textures;			/*!< Holds all the games Textures"*/
	FontHolder m_fonts;					/*!< Holds all the games fonts"*/
	SceneStack m_sceneStack;			/*!< Holds all the games Scenes"*/
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);	/*!<Game Update in frames per second"*/
};

