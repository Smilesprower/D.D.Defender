#include "stdafx.h"
#include "PauseScene.h"

PauseScene::PauseScene(SceneStack& stack, Context context)
	: Scene(stack, context)
	, m_text()
{
	context.window->setView(context.window->getDefaultView());		// Reset the window view after sf::View has been used
	m_text.setFont(context.fonts->get(Fonts::PS2P));				// Gets and Sets the font from Resourse Holder
	m_text.setString("Game \n\n Paused");
	m_text.setCharacterSize(200);
	m_text.setPosition(780, 310);

	m_background.setTexture(context.textures->get(Textures::PauseBackground));
	m_background.setOrigin(m_background.getTextureRect().width * 0.5, m_background.getTextureRect().height * 0.5);
	m_background.setScale(0.5, 0.5);
	m_background.setPosition(context.window->getSize().x * 0.5, context.window->getSize().y * 0.5);
}


void PauseScene::draw()
{
	sf::RenderWindow& window = *getContext().window;	// Get Render Window
	window.setView(window.getDefaultView());
	window.draw(m_background);
	window.draw(m_background2);
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