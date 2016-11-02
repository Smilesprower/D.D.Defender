#include "stdafx.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneStack& stack, Context context)
	: Scene(stack, context)								
	, m_text()
{
	context.window->setView(context.window->getDefaultView());		// Reset the window view after sf::View has been used
	m_text.setFont(context.fonts->get(Fonts::PS2P));				// Gets and Sets the font from Resourse Holder
	m_text.setString("Title Screen");
}


void TitleScene::draw()
{	
	sf::RenderWindow& window = *getContext().window;	// Get Render Window
	window.draw(m_text);

}

bool TitleScene::update(sf::Time deltaTime)
{
	return true;
}

bool TitleScene::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();					// Removes current Scene from Stack
		requestStackPush(Scenes::Game);		// Push Game Scene to the Stack
	}

	return true;
}