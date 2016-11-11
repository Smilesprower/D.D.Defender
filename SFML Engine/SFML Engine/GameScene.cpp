#include "stdafx.h"
#include "GameScene.h"
#include <iostream>



GameScene::GameScene(SceneStack& stack, Context context)
	: Scene(stack, context)
	, m_numOfScreens(4) // Change for number of screens needed, variables will auto assign to allow bigger screens
	, m_screenSize(context.window->getSize())
	, m_halfScreenSize(m_screenSize.x * 0.5f, m_screenSize.y * 0.5f)
	, m_worldSize(-m_screenSize.x, m_screenSize.x * (m_numOfScreens - OFFSET))
	, m_boundries(-m_halfScreenSize.x, m_worldSize.y - m_halfScreenSize.x)
	, m_camera(sf::Vector2i(m_worldSize.x, m_worldSize.y), sf::Vector2i(m_screenSize.x, m_screenSize.y))
	, m_playShockwave(false)
	, m_astro()
	, m_playo()
{

	// Check player world bounds " X value is MIN / Y value is MAX of the X Position"

	// Init Astro - Give the random Values
	//m_astro.init(context.textures->get(Textures::Astro), 960);

	m_testBullet.init(context.textures->get(Textures::Astro));


	//	Init Playo
	m_playo.init(context.textures->get(Textures::Playo), sf::Vector2f(m_halfScreenSize.x, m_halfScreenSize.y), sf::Vector2i(m_worldSize.x + m_screenSize.x, m_worldSize.y - m_screenSize.x));

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
	m_currPlayerPos.x = m_playo.m_animatedSprite.getPosition().x;
	m_currPlayerPos.y = m_playo.m_animatedSprite.getPosition().y;
	// Get our render window
	sf::RenderWindow& window = *getContext().window;

	// Check player world bounds " X value is MIN / Y value is MAX of the X Position"
	if (m_currPlayerPos.x > m_boundries.y)
	{
		sf::Vector2f tempPos = m_testBullet.getPosition();
		if (tempPos.x < m_currPlayerPos.x + (m_halfScreenSize.x)
			&& tempPos.x > m_currPlayerPos.x - (m_halfScreenSize.x))
		{
			tempPos.x = m_boundries.x + (tempPos.x - m_currPlayerPos.x);
			m_testBullet.setPosition(tempPos);
		}

		m_currPlayerPos.x = m_boundries.x;
		//for all entities in players view

	}
	else if (m_currPlayerPos.x < m_boundries.x)
	{
		//for every bullet Ai and Astro

		sf::Vector2f tempPos = m_testBullet.getPosition();
		if (tempPos.x > m_currPlayerPos.x - (m_halfScreenSize.x)
			&& tempPos.x < m_currPlayerPos.x + (m_halfScreenSize.x))
		{
			tempPos.x = m_boundries.y - (m_currPlayerPos.x - tempPos.x);
			m_testBullet.setPosition(tempPos);
		}
		m_currPlayerPos.x = m_boundries.y;

	}
	
	// Set players position 
	m_playo.m_animatedSprite.setPosition(sf::Vector2f(m_currPlayerPos.x, m_currPlayerPos.y));

	// Set the camera view
	window.setView(m_camera.Update(m_currPlayerPos.x));

	// Draw game entities
	if(m_playShockwave)
		window.draw(m_sprite, m_shockwave);
	else
		window.draw(m_sprite);

	//window.draw(m_astro.draw());
	window.draw(m_playo.draw());
	if (m_testBullet.isAlive())
		window.draw(m_testBullet.draw());
}

bool GameScene::update(sf::Time deltaTime)
{
	if (m_playShockwave)
	{
		m_shockwave->setUniform("time", m_clock.getElapsedTime().asSeconds() * 0.2f);
		if (m_clock.getElapsedTime().asSeconds() > 5)
			m_playShockwave = false;
	}
	//m_astro.update(deltaTime);
	m_playo.update(deltaTime);

	if(m_testBullet.isAlive())
		m_testBullet.update(deltaTime, m_playo.draw().getPosition());

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
		if (event.key.code == sf::Keyboard::F)
		{
			m_testBullet.setUpMissile(sf::Vector2f(100, 400), m_playo.draw().getPosition(), 2);
		}
		if (event.key.code == sf::Keyboard::P)
		{
			requestStackPush(Scenes::Pause);
		}
	}
	return true;
}