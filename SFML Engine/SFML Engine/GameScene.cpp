#include "stdafx.h"
#include "GameScene.h"
#include <iostream>
#include "Score.h"


GameScene::GameScene(SceneStack& stack, Context context)
	: Scene(stack, context)
	, m_numOfScreens(9) // Change for number of screens needed, variables will auto assign to allow bigger screens
	, m_screenSize(context.window->getSize())
	, m_halfScreenSize(m_screenSize.x * 0.5f, m_screenSize.y * 0.5f)
	, m_worldSize(-m_screenSize.x, m_screenSize.x * (m_numOfScreens - OFFSET))
	, m_boundries(-m_halfScreenSize.x, m_worldSize.y + m_halfScreenSize.x)
	, m_camera(sf::Vector2i(m_worldSize.x, m_worldSize.y), sf::Vector2i(m_screenSize.x, m_screenSize.y))
	, m_playShockwave(false)
	, m_playRipple(false)
	, m_playo(new Player())
	, m_canUpdateRadar(false)
	, m_score(0)
	, m_displayingAstroText(0)
{
	// DEBUGGING CODE
	/////////////////////////////////////////////
	m_screenView = sf::RectangleShape(sf::Vector2f(m_screenSize.x, m_screenSize.y));
	m_screenView.setFillColor(sf::Color::Transparent);
	m_screenView.setOutlineThickness(3);
	m_screenView.setOutlineColor(sf::Color::Green);

	m_playerCutOff = sf::RectangleShape(sf::Vector2f(m_boundries.y + m_halfScreenSize.x, m_screenSize.y * 2));
	m_playerCutOff.setFillColor(sf::Color::Transparent);
	m_playerCutOff.setOutlineThickness(3);
	m_playerCutOff.setOutlineColor(sf::Color::Red);
	m_playerCutOff.setPosition(sf::Vector2f(m_boundries.x, 0));
	/////////////////////////////////////////////

	// Check player world bounds " X value is MIN / Y value is MAX of the X Position"

	m_scoreText.setFont(context.fonts->get(Fonts::PS2P));				// Gets and Sets the font from Resourse Holder
	m_scoreText.setCharacterSize(50);
	m_scoreText.setPosition(context.window->getSize().x * 0.56, context.window->getSize().y * 0.925);

	m_aliveAstrosText.setFont(context.fonts->get(Fonts::PS2P));				// Gets and Sets the font from Resourse Holder
	m_aliveAstrosText.setCharacterSize(70);
	m_aliveAstrosText.setPosition(context.window->getSize().x * 0.05, context.window->getSize().y * 0.91);

	// Init Astros - Give the random Values
	for (int i = 0; i < NUM_OF_ASTROS; i++)
	{
		m_astronauts.push_back(new Astronaut(context.textures->get(Textures::Astro), 700 * i - 100));
	}
	for (int i = 0; i < NUM_OF_ALIENS; i++)
	{
		m_aliens.push_back(new Alien(context.textures->get(Textures::Astro), m_screenSize, m_worldSize));
	}
	BulletManager::Instance()->init(context.textures->get(Textures::Astro), MAX_BULLETS);

	//init nest
	for (int i = 0; i < 3; i++)
	{
		m_nests.push_back(new Nest(context.textures->get(Textures::Astro), m_worldSize));
		m_nests[i]->init(sf::Vector2f(2000 * i, 200));
	}
	for (int i = 0; i < MAX_GAS_CLOUDS; i++)
	{
		//init gas clouds
		m_gasClouds.push_back(new Obstacle());
		m_gasClouds[i]->init(context.textures->get(Textures::Astro), sf::Vector2f(i * 1920, rand() % 600 + 100), m_worldSize, 0);
	}
	for (int i = 0; i < m_astronauts.size(); ++i)
	{
		sf::CircleShape icon;
		icon.setFillColor(sf::Color::Green);
		icon.setRadius(8);
		icon.setOrigin(4, 4);
		m_radarIcons.push_back(icon);
	}
	for (int i = 0; i < NUM_OF_HEALTH_PACKS; i++)
	{
		//init health packs
		m_healthPacks.push_back(new Obstacle());
		m_healthPacks[i]->init(context.textures->get(Textures::Astro), sf::Vector2f(i * 1920, rand() % 800 + 100), m_worldSize, 1);
	}
	//	Init Playo
	m_playo->init(context.textures->get(Textures::Astro), sf::Vector2f(m_halfScreenSize.x, m_halfScreenSize.y), sf::Vector2i(m_worldSize.x + m_screenSize.x, m_worldSize.y - m_screenSize.x));
	// PLAYER RADAR
	m_radarScreen.setOutlineColor(sf::Color::White);
	m_radarScreen.setOutlineThickness(2);
	m_radarScreen.setFillColor(sf::Color::Transparent);
	m_radarScreen.setSize(sf::Vector2f(190, 118));
	m_radarScreen.setOrigin(sf::Vector2f(95, 59));

	m_playerRadar.setFillColor(sf::Color::White);
	m_playerRadar.setRadius(6);
	m_playerRadar.setOrigin(3, 3);
	
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
GameScene::~GameScene()
{
	for (int i = 0; i < m_nests.size(); i++)
	{
		delete m_nests[i];
		m_nests[i] = nullptr;
	}
	for (int i = 0; i < m_gasClouds.size(); i++)
	{
		delete m_gasClouds[i];
		m_gasClouds[i] = nullptr;
	}
	for (int i = 0; i < m_astronauts.size(); i++)
	{
		delete m_astronauts[i];
		m_astronauts[i] = nullptr;
	}
	for (int i = 0; i < m_aliens.size(); i++)
	{
		delete m_aliens[i];
		m_aliens[i] = nullptr;
	}
	delete m_playo;
	m_playo = nullptr;
}

void GameScene::draw()
{

	std::vector<Bullet*> bulletCopy = BulletManager::Instance()->getBullets();

	// Get current Player Pos need for camera and Shaders etc
	m_currPlayerPos.x = m_playo->m_animatedSprite.getPosition().x;
	m_currPlayerPos.y = m_playo->m_animatedSprite.getPosition().y;
	// Get our render window
	sf::RenderWindow& window = *getContext().window;

	// Check player world bounds " X value is MIN / Y value is MAX of the X Position"
	if (m_currPlayerPos.x > m_boundries.y)
	{
		int enemyNestSize = m_nests.size();
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
		for (int i = 0; i < enemyNestSize; i++)
		{
			sf::Vector2f tempPos = m_nests[i]->getPosition();
			if (tempPos.x < m_currPlayerPos.x + (m_halfScreenSize.x)
				&& tempPos.x > m_currPlayerPos.x - (m_halfScreenSize.x))
			{
				tempPos.x = m_boundries.x + (tempPos.x - m_currPlayerPos.x);
				m_nests[i]->setPosition(tempPos);
			}
		}
		m_currPlayerPos.x = m_boundries.x;
	}
	else if (m_currPlayerPos.x < m_boundries.x)
	{
		int enemyNestSize = m_nests.size();
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
		for (int i = 0; i < enemyNestSize; i++)
		{
			sf::Vector2f tempPos = m_nests[i]->getPosition();
			if (tempPos.x > m_currPlayerPos.x - (m_halfScreenSize.x)
				&& tempPos.x < m_currPlayerPos.x + (m_halfScreenSize.x))
			{
				tempPos.x = m_boundries.y + (tempPos.x - m_currPlayerPos.x);
				m_nests[i]->setPosition(tempPos);

			}
		}
		m_currPlayerPos.x = m_boundries.y;
	}


	// Set players position 
	m_playo->m_animatedSprite.setPosition(sf::Vector2f(m_currPlayerPos.x, m_currPlayerPos.y));

	// Set the camera view
	window.setView(m_camera.Update(m_currPlayerPos.x));

	//Add the score to the string
	
	// Draw game entities
	if (m_playShockwave)
		window.draw(m_sprite, m_shockwave);
	else if(m_playRipple)
		window.draw(m_sprite, m_ripple);
	else
	{
		window.draw(m_sprite);
		window.draw(m_playo->draw());

		if (!m_playRipple)
		{
			for (int i = 0; i < m_nests.size(); ++i)
			{
				if (m_nests[i]->isAlive() == true)
				{
					window.draw(m_nests[i]->draw());
				}
			}
			for (int i = 0; i < m_aliens.size(); i++)
			{
				if (m_aliens[i]->getAlive() == true)
				{
					window.draw(m_aliens[i]->draw());
				}
			}
			for (int i = 0; i < NUM_OF_ASTROS; i++)
			{
				if (m_astronauts[i]->isAlive())
				{
					window.draw(m_astronauts[i]->draw());
				}
			}

			for (int i = 0; i < MAX_BULLETS; i++)
			{
				if (bulletCopy[i]->isEnabled())
				{
					window.draw(bulletCopy.at(i)->draw());
					if (bulletCopy[i]->getType() == bulletCopy[i]->Missile)
					{
						window.draw(bulletCopy[i]->drawMissileCollider());
					}
				}

			}
			for (int i = 0; i < MAX_GAS_CLOUDS; i++)
			{
				window.draw(m_gasClouds[i]->draw());
			}
			for (int i = 0; i < NUM_OF_HEALTH_PACKS; i++)
			{
				if (m_healthPacks[i]->isEnabled())
				{
					window.draw(m_healthPacks[i]->draw());
				}
			}
		}
	}
		
	// DEBUGGING CODE
	/////////////////////////////////////////////
	window.draw(m_screenView);
	window.draw(m_playerCutOff);
	window.draw(m_nests[0]->drawEvade());
	window.draw(m_nests[0]->drawFire());
	window.draw(m_playo->drawPlayerOutline());
	/////////////////////////////////////////////

	window.setView(window.getDefaultView());
	window.draw(m_hud.drawRectangle());
	window.draw(m_hud.drawHealthRect());
	window.draw(m_hud.draw());

	for (int i = 0; i < m_radarIcons.size(); i++)
	{
		if (m_astronauts[i]->isAlive() == true)
		{
			m_radarIcons[i].setPosition((m_astronauts[i]->getPosition().x + m_screenSize.x) / 9, (m_astronauts[i]->getPosition().y / 9) + 10);
			if (m_astronauts[i]->getState() == m_astronauts[i]->Abducted)
			{
				m_radarIcons[i].setFillColor(sf::Color::Red);
			}
			else
			{
				m_radarIcons[i].setFillColor(sf::Color::Green);
			}
			window.draw(m_radarIcons[i]);
		}
	}
	m_radarScreen.setPosition(((m_currPlayerPos.x + m_screenSize.x) / 9), 69);
	m_playerRadar.setPosition(((m_currPlayerPos.x + m_screenSize.x) / 9), (m_currPlayerPos.y / 9) + 10);
	window.draw(m_playerRadar);
	window.draw(m_radarScreen);

	std::string score = std::to_string(Score::Instance()->getScore());
	m_scoreText.setString(score);
	window.draw(m_scoreText);

	if (Score::Instance()->canDisplayAstroText() == true)
	{
		m_displayingAstroText++;

		std::string astrosRemaining = std::to_string(Score::Instance()->getAliveAstros());
		m_aliveAstrosText.setString("Astronauts Remaining: " + astrosRemaining);
		window.draw(m_aliveAstrosText);
		if (m_displayingAstroText >= 50)
		{
			Score::Instance()->setDisplayAstroText(false);
			m_displayingAstroText = 0;
		}
	}


	
}

bool GameScene::update(sf::Time deltaTime)
{
	// Check Player Dead
	//////////////////////////////
	if(m_playo->gameOver())
	{
		requestStackPop();
		// Make Game Over Scene
		requestStackPush(Scenes::Title);
	}

	m_radarTime += deltaTime.asSeconds();
	if (m_radarTime > 2)
	{
		m_canUpdateRadar = true;
	}
	std::vector<Bullet*> bullets = BulletManager::Instance()->getBullets();

	if (!m_playShockwave && !m_playRipple && m_playo->getSmartBombState() == m_playo->Fired)
		setupShockwave(m_currPlayerPos);
	else if (!m_playRipple && !m_playShockwave && m_playo->getTeleport() == m_playo->Fired)
		setupRipple(m_currPlayerPos);

	if (m_playShockwave)
	{
		m_shockwave->setUniform("time", m_clock.getElapsedTime().asSeconds() * 0.2f);
		if (m_clock.getElapsedTime().asSeconds() > 5)
		{
			m_playShockwave = false;
			m_playo->chargeSmartBomb();
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
			m_playo->disableTeleporter();
		}
	}
	else
	{
		sf::Vector2f tempBounds(m_currPlayerPos.x - m_halfScreenSize.x, m_currPlayerPos.x + m_halfScreenSize.x);

		BulletManager::Instance()->update(deltaTime, m_currPlayerPos);

		m_hud.update(deltaTime, m_playo->m_smartBombTimer, m_playo->getHealth());
		m_playo->update(deltaTime);

		for (int i = 0; i < m_nests.size(); i++)
		{
			if(m_nests[i]->update(deltaTime, m_currPlayerPos))
			{
				// spawn enemy
				for (int j = 0; j < m_aliens.size(); j++)
				{
					if (m_aliens[j]->getAlive() == false)
					{
						m_aliens[j]->init(m_nests[i]->getPosition());
						break;
					}
				}
			}
		}

		for (int i = 0; i < m_aliens.size(); i++)
		{
			if(m_aliens[i]->run(&m_aliens, deltaTime, m_currPlayerPos))
			{
				// Spawn a new enemy
			}

		}

		for (int i = 0; i < NUM_OF_ASTROS; i++)
		{
			if (m_astronauts[i]->isAlive())
			{
				m_astronauts[i]->update(deltaTime);
			}
		}

		//	EANBLE HEALTH PACKS AFTER KILL STREAK
		if (Score::Instance()->getKillStreak() >= 3)
		{
			Score::Instance()->resetKillStreak();
			if (m_streakCount < NUM_OF_HEALTH_PACKS)
			{
				m_healthPacks[m_streakCount]->setEnabled(true);
				m_streakCount++;
			}
		}
	}
	m_screenView.setPosition(m_currPlayerPos.x - m_screenSize.x * 0.5, 0);
	m_collisionManager.checkCollision(m_playo, &bullets, &m_gasClouds, &m_healthPacks, &m_nests, &m_aliens, &m_astronauts);
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
	SoundPlayer::Instance()->play(SoundEffect::Charge);
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
	SoundPlayer::Instance()->play(SoundEffect::Charge);
	m_clock.restart();
	m_ripple->setUniform("wave_amount", 0.f);
	m_ripple->setUniform("wave_distortion", 1.f);
	m_ripple->setUniform("wave_speed", 0.f);
	m_ripple->setUniform("resolution", sf::Vector2f(1920, 1080));
	m_ripple->setUniform("centre", sf::Vector2f(m_currPlayerPos.x + m_screenSize.x, m_currPlayerPos.y));
	m_playRipple = true;
}