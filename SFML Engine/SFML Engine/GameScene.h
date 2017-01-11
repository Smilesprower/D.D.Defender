#pragma once
#include "Scene.h"
#include "AnimatedSprite.h"
#include "Bullet.h"
#include "Astronaut.h"
#include "nest.h"
#include "Camera.h"
#include "HUD.h"
#include "CollisionManager.h"
#include "Obstacle.h"


class GameScene : public Scene
{
public:
	GameScene(SceneStack& stack, Context context);
	~GameScene();
	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

	void setupShockwave(sf::Vector2f playerPos);
	void setupRipple(sf::Vector2f playerPos);

private:
	const int OFFSET = 2;
	const int MAX_GAS_CLOUDS = 7;
	int m_numOfScreens;
	sf::Vector2i m_screenSize;
	sf::Vector2i m_halfScreenSize;
	sf::Vector2i m_worldSize;
	sf::Vector2i m_boundries;

	Camera m_camera;

	sf::Sprite m_sprite;
	ShaderHolder m_shaders;
	sf::Shader * m_shockwave;
	sf::Shader * m_ripple;
	sf::Clock m_clock;
	bool m_playShockwave;
	bool m_playRipple;

	Astronaut m_astro;
	Player * m_playo;
	CollisionManager m_collisionManager;
	HUD m_hud;
	std::vector<Nest*> m_nests;
	std::vector<Obstacle*> m_gasClouds;
	sf::Vector2f m_currPlayerPos;
	const int MAX_BULLETS = 50;
	float m_shaderValue1;
	float m_shaderValue2;

	sf::RectangleShape m_screenView;
	sf::RectangleShape m_playerCutOff;
	sf::RectangleShape m_enemyCutOff;


	// RADAR
	std::vector<sf::CircleShape> m_radarIcons;
	sf::RectangleShape m_radarScreen;
	sf::CircleShape m_playerRadar;
	bool m_canUpdateRadar;
	float m_radarTime;
};
