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
	, m_playRipple(false)
	, m_astro()
	, m_playo()
{

	// Check player world bounds " X value is MIN / Y value is MAX of the X Position"

	// Init Astro - Give the random Values
	m_astro.init(context.textures->get(Textures::Astro), 960);


	BulletManager::Instance()->init(context.textures->get(Textures::Astro), MAX_BULLETS);

	//	Init Playo
	m_playo.init(context.textures->get(Textures::Playo), sf::Vector2f(m_halfScreenSize.x, m_halfScreenSize.y), sf::Vector2i(m_worldSize.x + m_screenSize.x, m_worldSize.y - m_screenSize.x));
	// Init Hud
	m_hud.init(context.textures->get(Textures::HUD), m_screenSize);
	context.textures->get(Textures::GameBackground).setRepeated(true);
	m_sprite.setTexture(context.textures->get(Textures::GameBackground));	// Gets and Sets the texture from Resourse Holder
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_screenSize.x * m_numOfScreens, m_screenSize.y));
	m_sprite.setPosition(m_worldSize.x, 0);


	m_shaders.load(Shaders::Ripple, "../resources/shader/ripple.vert", "../resources/shader/ripple.frag");
	m_ripple = &m_shaders.get(Shaders::Ripple);
	m_ripple->setUniform("texture", sf::Shader::CurrentTexture);

	m_shaders.load(Shaders::Shockwave, "../resources/shader/shockwave.vert", "../resources/shader/shockwave.frag");
	m_shockwave = &m_shaders.get(Shaders::Shockwave);
	m_shockwave->setUniform("texture", sf::Shader::CurrentTexture);
}
void GameScene::draw()
{
	std::vector<Bullet*> bulletCopy = BulletManager::Instance()->getBullets();

	// Get current Player Pos need for camera and Shaders etc
	m_currPlayerPos.x = m_playo.m_animatedSprite.getPosition().x;
	m_currPlayerPos.y = m_playo.m_animatedSprite.getPosition().y;
	// Get our render window
	sf::RenderWindow& window = *getContext().window;

	// Check player world bounds " X value is MIN / Y value is MAX of the X Position"
	if (m_currPlayerPos.x > m_boundries.y)
	{
		int bulletSize = bulletCopy.size();
		for (int i = 0; i < bulletSize; i++)
		{
			if (bulletCopy[i]->isEnabled())
			{
				sf::Vector2f tempPos = bulletCopy[i]->getPosition();
				if (tempPos.x < m_currPlayerPos.x + (m_halfScreenSize.x)
					&& tempPos.x > m_currPlayerPos.x - (m_halfScreenSize.x))
				{
					tempPos.x = m_boundries.x + (tempPos.x - m_currPlayerPos.x);
					bulletCopy[i]->setPosition(tempPos);
				}
			}
		}
		m_currPlayerPos.x = m_boundries.x;
	}
	else if (m_currPlayerPos.x < m_boundries.x)
	{
		int bulletSize = bulletCopy.size();
		for (int i = 0; i < bulletSize; i++)
		{
			if (bulletCopy[i]->isEnabled())
			{
				sf::Vector2f tempPos = bulletCopy[i]->getPosition();
				if (tempPos.x > m_currPlayerPos.x - (m_halfScreenSize.x)
					&& tempPos.x < m_currPlayerPos.x + (m_halfScreenSize.x))
				{
					tempPos.x = m_boundries.y + (tempPos.x- m_currPlayerPos.x);
					bulletCopy[i]->setPosition(tempPos);
				}
			}
		}
		m_currPlayerPos.x = m_boundries.y;
	}

	// Set players position 
	m_playo.m_animatedSprite.setPosition(sf::Vector2f(m_currPlayerPos.x, m_currPlayerPos.y));

	// Set the camera view
	window.setView(m_camera.Update(m_currPlayerPos.x));
	
	// Draw game entities
	if (m_playShockwave)
		window.draw(m_sprite, m_shockwave);
	else if(m_playRipple)
		window.draw(m_sprite, m_ripple);
	else
		window.draw(m_sprite);

	for (int i = 0; i < MAX_BULLETS; i++)
		if(bulletCopy[i]->isEnabled())
			window.draw(bulletCopy.at(i)->draw());

	window.draw(m_playo.draw());
	window.draw(m_astro.draw());
	window.setView(window.getDefaultView());

	window.draw(m_hud.drawRectangle());
	window.draw(m_hud.draw());

}

bool GameScene::update(sf::Time deltaTime)
{
	if (!m_playShockwave && !m_playRipple && m_playo.getSmartBombState() == m_playo.Fired)
		setupShockwave(m_currPlayerPos);
	else if (!m_playRipple && !m_playShockwave && m_playo.getTeleport() == m_playo.Fired)
		setupRipple(m_currPlayerPos);

	if (m_playShockwave)
	{
		m_shockwave->setUniform("time", m_clock.getElapsedTime().asSeconds() * 0.2f);
		if (m_clock.getElapsedTime().asSeconds() > 5)
		{
			m_playShockwave = false;
			m_playo.chargeSmartBomb();
		}
	}
	else if (m_playRipple)
	{
		if (m_clock.getElapsedTime().asSeconds() <= 2.5f)
		{
			m_shaderValue1 += 0.15f;
			m_shaderValue2 += 0.25f;
		}
		else
		{
			m_shaderValue1 -= 0.15f;
			m_shaderValue2 -= 0.25f;
		}
		m_ripple->setUniform("wave_amount", m_shaderValue1);
		m_ripple->setUniform("wave_speed", m_shaderValue2);
		m_ripple->setUniform("time", m_clock.getElapsedTime().asSeconds() * 0.2f);
		if (m_clock.getElapsedTime().asSeconds() > 5)
		{
			m_playRipple = false;
			m_playo.disableTeleporter();
		}
	}
	else
	{
		sf::Vector2f tempBounds(m_currPlayerPos.x - m_halfScreenSize.x, m_currPlayerPos.x + m_halfScreenSize.x);

		// Do you really need to curse in the comments Jay? lol
		BulletManager::Instance()->update(deltaTime);

		m_hud.update(deltaTime, m_playo.m_smartBombTimer, m_playo.getHealth());
		m_playo.update(deltaTime);
		//m_astro.update(deltaTime);

	}
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
		if (event.key.code == sf::Keyboard::P)
		{
			requestStackPush(Scenes::Pause);
		}
	}
	return true;
}

void GameScene::setupShockwave(sf::Vector2f playerPos)
{
	//SoundPlayer::Instance()->play(SoundEffect::Charge);
	m_clock.restart();
	m_shockwave->setUniform("shock_amplitude", 10.f);
	m_shockwave->setUniform("shock_refraction", .5f);
	m_shockwave->setUniform("shock_width", 0.15f);
	m_shockwave->setUniform("resolution", sf::Vector2f(1920, 1080));
	m_shockwave->setUniform("centre", sf::Vector2f(m_currPlayerPos.x + m_screenSize.x, m_currPlayerPos.y));

	m_playShockwave = true;
	m_hud.reset();
}
void GameScene::setupRipple(sf::Vector2f playerPos)
{
	//SoundPlayer::Instance()->play(SoundEffect::Charge);
	m_clock.restart();
	m_ripple->setUniform("wave_amount", 0.f);
	m_ripple->setUniform("wave_distortion", 1.f);
	m_ripple->setUniform("wave_speed", 0.f);
	m_ripple->setUniform("resolution", sf::Vector2f(1920, 1080));
	m_ripple->setUniform("centre", sf::Vector2f(m_currPlayerPos.x + m_screenSize.x, m_currPlayerPos.y));
	m_playRipple = true;
}