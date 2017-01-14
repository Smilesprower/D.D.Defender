#pragma once
#include "Scene.h"
#include "SceneStack.h"
#include "Score.h"

class GameoverScene : public Scene
{
public:
	GameoverScene(SceneStack& stack, Context context);

	void draw() override;
	bool update(sf::Time deltaTime) override;
	bool handleEvent(const sf::Event& event) override;

private:
	sf::Text m_text;
	sf::Text m_score;
	sf::Sprite m_background;

	//	Buttons
	sf::Sprite m_ButtonPlay;
	sf::Sprite m_ButtonExit;
	int m_selectedButton;
};
