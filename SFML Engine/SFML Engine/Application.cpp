#include "stdafx.h"
#include "Application.h"
#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "PauseScene.h"
#include "SceneIdentifiers.h"

Application::Application()
	: m_window(sf::VideoMode(1920, 1080), "States", sf::Style::Titlebar)
	, m_textures()
	, m_fonts()
	, m_sceneStack(Scene::Context(m_window, m_textures, m_fonts))
{
	m_window.setKeyRepeatEnabled(false);								// Disable repeat keys
	m_window.setVerticalSyncEnabled(true);								// Enable vertical sync

	m_fonts.load(Fonts::PS2P, "../resources/font/Digital.ttf"); 	// Load Fonts
	m_textures.load(Textures::GameBackground, "../resources/tex/Game/Backgrounds/SpaceBackground.png");	// Load Textures
	m_textures.load(Textures::PauseBackground, "../resources/tex/Menu/PauseMenu.png");	// Load Textures
	m_textures.load(Textures::PauseBackgroundOpaque, "../resources/tex/Menu/PauseMenu2.png");	// Load Textures

	createScenes();														// Create all the scenes
	m_sceneStack.pushScene(Scenes::Title);								// Add scene to the stack
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			handleInput();
			update(TIME_PER_FRAME);

			SoundPlayer::Instance()->removeStoppedSounds();

			// Stack of states are empty, end the application
			if (m_sceneStack.isEmpty())
				m_window.close();
		}
		render();
	}
}

void Application::handleInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		m_sceneStack.handleEvent(event);
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Application::update(sf::Time deltaTime)
{
	m_sceneStack.update(deltaTime);
}

void Application::render()
{
	m_window.clear();
	m_sceneStack.draw();
	m_window.display();
}

void Application::createScenes()
{
	m_sceneStack.createScene<TitleScene>(Scenes::Title);
	m_sceneStack.createScene<GameScene>(Scenes::Game);
	m_sceneStack.createScene<PauseScene>(Scenes::Pause);
}
