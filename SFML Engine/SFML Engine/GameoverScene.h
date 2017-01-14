#pragma once
#include "Scene.h"
#include "SceneStack.h"

class GameoverScene : public Scene
{
public:
	GameoverScene(SceneStack& stack, Context context);

	void draw() override;
	bool update(sf::Time deltaTime) override;
	bool handleEvent(const sf::Event& event) override;

private:
	sf::Sprite m_background;
};
