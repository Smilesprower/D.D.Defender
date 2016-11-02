#include "stdafx.h"
#include "PauseScene.h"

PauseScene::PauseScene(SceneStack& stack, Context context)
	: Scene(stack, context)
	, m_text()
{
	context.window->setView(context.window->getDefaultView());		// Reset the window view after sf::View has been used
	m_text.setFont(context.fonts->get(Fonts::PS2P));				// Gets and Sets the font from Resourse Holder
	m_text.setString("Pause Screen");
}


void PauseScene::draw()
{
	sf::RenderWindow& window = *getContext().window;	// Get Render Window
	window.draw(m_text);
}

bool PauseScene::update(sf::Time deltaTime)
{
	return true;
}

bool PauseScene::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::P)
		{
			requestStackPop();
		}
	}
	return true;
}