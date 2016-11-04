#include "stdafx.h"
#include "GameScene.h"
#include <iostream>



GameScene::GameScene(SceneStack& stack, Context context)
	: Scene(stack, context)
	, m_numOfScreens(4) // Change for number of screens needed, variables will auto assign to allow bigger screens
	, m_screenSize(context.window->getSize())
	, m_worldSize(-m_screenSize.x, m_screenSize.x * (m_numOfScreens - OFFSET))
	, m_boundries(-m_screenSize.x * 0.5f, m_worldSize.y - (m_screenSize.x * 0.5f))
	, m_camera(sf::Vector2i(m_worldSize.x, m_worldSize.y), sf::Vector2i(m_screenSize.x, m_screenSize.y))
	, m_playShockwave(false)
	, m_astro()
	, m_playo()
{

	// Init Astro - Give the random Values
	m_astro.init(context.textures->get(Textures::Astro), 960);

	//	Init Playo
	//m_playo.init(context.textures->get(Textures::Playo), sf::Vector2f(960, 0));

	context.textures->get(Textures::GameBackground).setRepeated(true);
	m_sprite.setTexture(context.textures->get(Textures::GameBackground));	// Gets and Sets the texture from Resourse Holder
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_screenSize.x * m_numOfScreens, m_screenSize.y));
	m_sprite.setPosition(m_worldSize.x, 0);

	m_shaders.load(Shaders::Shockwave, "../resources/shader/shockwave.vert", "../resources/shader/shockwave.frag");
	m_shockwave = &m_shaders.get(Shaders::Shockwave);
	m_shockwave->setUniform("texture", sf::Shader::CurrentTexture);
}
void GameScene::draw()
{
	// Get current Player Pos need for camera and Shaders etc
	m_currPlayerPos.x = m_astro.draw().getPosition().x;
	m_currPlayerPos.y = m_astro.draw().getPosition().y;
	// Get our render window
	sf::RenderWindow& window = *getContext().window;

	// Check player world bounds " X value is MIN / Y value is MAX "
	if (m_currPlayerPos.x > m_boundries.y)
		m_currPlayerPos.x = m_boundries.x;
	else if (m_currPlayerPos.x < m_boundries.x)
		m_currPlayerPos.x = m_boundries.y;
	
	// Set players position 
	//std::cout << "X POS " << playerPos.x << std::endl;
	m_astro.setPosition(sf::Vector2f(m_currPlayerPos.x, m_currPlayerPos.y));

	// Set the camera view
	window.setView(m_camera.Update(m_currPlayerPos.x));

	// Draw game entities
	if(m_playShockwave)
		window.draw(m_sprite, m_shockwave);
	else
		window.draw(m_sprite);

	window.draw(m_astro.draw());
	//window.draw(m_playo.draw());
}

bool GameScene::update(sf::Time deltaTime)
{
	if (m_playShockwave)
	{
		m_shockwave->setUniform("time", m_clock.getElapsedTime().asSeconds() * 0.2f);
		if (m_clock.getElapsedTime().asSeconds() > 5)
			m_playShockwave = false;
	}
	m_astro.update(deltaTime);
	//m_playo.update(deltaTime);
	return true;
}
// Event Input
bool GameScene::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			requestStackPop();
		}
		if (event.key.code == sf::Keyboard::Return)
		{
			if (!m_playShockwave)
			{
				SoundPlayer::Instance()->play(SoundEffect::Charge);
				m_clock.restart();
				m_shockwave->setUniform("shock_amplitude", 10.f);
				m_shockwave->setUniform("shock_refraction", .5f);
				m_shockwave->setUniform("shock_width", 0.15f);
				m_shockwave->setUniform("resolution", sf::Vector2f(1920, 1080));
				m_shockwave->setUniform("centre", sf::Vector2f(m_currPlayerPos.x + m_screenSize.x, m_currPlayerPos.y));
				m_playShockwave = true;
			}
		}
		if (event.key.code == sf::Keyboard::P)
		{
			requestStackPush(Scenes::Pause);
		}
	}
	return true;
}