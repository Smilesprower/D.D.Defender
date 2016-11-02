#pragma once
#include "Scene.h"


class GameScene : public Scene
{
public:
	GameScene(SceneStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& event);

private:
	sf::Vector2f m_screenSize;
	sf::View m_view;
	sf::Text m_text;
	sf::Sprite m_sprite;
	ShaderHolder m_shaders;
	sf::Shader * m_shockwave;
	sf::Clock m_clock;
	sf::RectangleShape m_rect;
	bool m_playShockwave;

};
