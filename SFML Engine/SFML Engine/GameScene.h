#pragma once
#include "Scene.h"
#include "AnimatedSprite.h"
#include "Bullet.h"
#include "Astronaut.h"
#include "Player.h"
#include "Camera.h"

class GameScene : public Scene
{
public:
	GameScene(SceneStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

	void setupShockwave(sf::Vector2f playerPos);

private:
	const int OFFSET = 2;

	int m_numOfScreens;
	sf::Vector2i m_screenSize;
	sf::Vector2i m_halfScreenSize;
	sf::Vector2i m_worldSize;
	sf::Vector2i m_boundries;

	Camera m_camera;

	sf::Sprite m_sprite;
	ShaderHolder m_shaders;
	sf::Shader * m_shockwave;
	sf::Clock m_clock;
	bool m_playShockwave;

	Astronaut m_astro;
	Player m_playo;
	sf::Vector2f m_currPlayerPos;
	Bullet m_testBullet;
};
