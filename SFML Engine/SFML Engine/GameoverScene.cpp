#include "stdafx.h"
#include "GameoverScene.h"




GameoverScene::GameoverScene(SceneStack & stack, Context context)
	: Scene(stack, context)
	, m_text()
	, m_selectedButton(1)
{
	context.window->setView(context.window->getDefaultView());		// Reset the window view after sf::View has been used
	m_text.setFont(context.fonts->get(Fonts::PS2P));				// Gets and Sets the font from Resourse Holder
	m_text.setString("Play              Exit");
	m_text.setCharacterSize(70);
	m_text.setPosition(context.window->getSize().x * 0.365, context.window->getSize().y * 0.7);

	m_score.setFont(context.fonts->get(Fonts::PS2P));				// Gets and Sets the font from Resourse Holder
	m_score.setCharacterSize(70);
	m_score.setPosition(context.window->getSize().x * 0.4, context.window->getSize().y * 0.48);

	m_time.setFont(context.fonts->get(Fonts::PS2P));				// Gets and Sets the font from Resourse Holder
	m_time.setCharacterSize(70);
	m_time.setPosition(context.window->getSize().x * 0.4, context.window->getSize().y * 0.395);

	m_astrosRemaining.setFont(context.fonts->get(Fonts::PS2P));				// Gets and Sets the font from Resourse Holder
	m_astrosRemaining.setCharacterSize(70);
	m_astrosRemaining.setPosition(context.window->getSize().x * 0.4, context.window->getSize().y * 0.57);

	if (Score::Instance()->getGameWon())
	{
		m_background.setTexture(context.textures->get(Textures::GameWinBG));
	}
	else
	{
		m_background.setTexture(context.textures->get(Textures::GameOverBG));
	}
	m_background.setOrigin(m_background.getTextureRect().width * 0.5, m_background.getTextureRect().height * 0.5);
	m_background.setPosition(context.window->getSize().x * 0.5, context.window->getSize().y * 0.5);


	// Setup Buttons
	m_ButtonPlay.setTexture(context.textures->get(Textures::Button));
	m_ButtonPlay.setPosition(context.window->getSize().x * 0.45, context.window->getSize().y * 0.7);
	m_ButtonPlay.scale(-1, 1); // flip button

	m_ButtonExit.setTexture(context.textures->get(Textures::Button));
	m_ButtonExit.setPosition(context.window->getSize().x * 0.55, context.window->getSize().y * 0.7);
}

void GameoverScene::draw()
{
	sf::RenderWindow& window = *getContext().window;	// Get Render Window
	window.draw(m_background);
	window.draw(m_ButtonPlay);
	window.draw(m_ButtonExit);
	window.draw(m_text);
	window.draw(m_score);
	window.draw(m_time);
	if (Score::Instance()->getGameWon() == true)
	{
		window.draw(m_astrosRemaining);
	}
}

bool GameoverScene::update(sf::Time deltaTime)
{
	std::string score = std::to_string(Score::Instance()->getScore());
	m_score.setString(score);
	std::string time = std::to_string(Score::Instance()->getPlayTime());
	m_time.setString(time);
	std::string astrosAlive = std::to_string(Score::Instance()->getAliveAstros());
	m_astrosRemaining.setString(astrosAlive);

	if (m_selectedButton == 1)
	{
		m_ButtonPlay.setColor(sf::Color(255, 255, 0, 255));
		m_ButtonExit.setColor(sf::Color(255, 255, 255, 255));
	}
	else if (m_selectedButton == 2)
	{
		m_ButtonExit.setColor(sf::Color(255, 255, 0, 255));
		m_ButtonPlay.setColor(sf::Color(255, 255, 255, 255));
	}
	return true;
}

bool GameoverScene::handleEvent(const sf::Event & event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		if (m_selectedButton == 1)
		{
			requestStackPop();					// Removes current Scene from Stack
			requestStackPush(Scenes::Game);		// Push Game Scene to the Stack
			MusicPlayer::Instance()->stop();
			MusicPlayer::Instance()->play(Music::GameTheme);
			Score::Instance()->reset();
		}
		else if (m_selectedButton == 2)
		{
			sf::RenderWindow& window = *getContext().window;	// Get Render Window
			window.close();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_selectedButton = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_selectedButton = 2;
	}

	return true;
}
