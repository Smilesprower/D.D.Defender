#include "stdafx.h"
#include "GameScene.h"




GameScene::GameScene(SceneStack& stack, Context context)
	: Scene(stack, context)
	, m_screenSize(context.window->getSize())			// Size of the Window
	, m_rect(sf::Vector2f(100, 100))
	, m_playShockwave(false)
	, m_astro()
	, m_playo()
{
	// Init Astro
	m_astro.init(context.textures->get(Textures::Astro), 500);
	//	Init Playo
	m_playo.init(context.textures->get(Textures::Playo), sf::Vector2f(100, 0));

	m_sprite.setTexture(context.textures->get(Textures::GameBackground));	// Gets and Sets the texture from Resourse Holder
	
	m_shaders.load(Shaders::Shockwave, "../resources/shader/shockwave.vert", "../resources/shader/shockwave.frag");
	m_shockwave = &m_shaders.get(Shaders::Shockwave);
	m_shockwave->setUniform("texture", sf::Shader::CurrentTexture);
	m_shockwave->setUniform("shock_amplitude", 10.f);
	m_shockwave->setUniform("shock_refraction", .2f);
	m_shockwave->setUniform("shock_width", 0.15f);
	m_shockwave->setUniform("resolution", m_screenSize);
	m_shockwave->setUniform("centre",m_screenSize/2.f);

}

void GameScene::draw()
{
	sf::RenderWindow& window = *getContext().window;

	
	window.setView(m_camera.Update(m_playo.m_animatedSprite.getPosition().x, window.getSize()));

	for (int i = 0; i < NUMOFSCREENS - 1; i++)
	{
		m_sprite.setPosition(i * window.getSize().x, 0);

		if(m_playShockwave)
			window.draw(m_sprite, m_shockwave);
		else 
			window.draw(m_sprite);
	}


	window.draw(m_astro.draw());
	window.draw(m_playo.draw());

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
	m_playo.update(deltaTime);


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