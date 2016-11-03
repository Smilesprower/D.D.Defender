#pragma once
#include "Scene.h"
#include "SceneStack.h"

class TitleScene : public Scene
{
public:
	TitleScene(SceneStack& stack, Context context);

	void draw() override;
	bool update(sf::Time deltaTime) override;
	bool handleEvent(const sf::Event& event) override;

private:
	sf::Clock clock;
	sf::Text m_text;
	sf::Sprite m_background;

	//	Buttons
	sf::Sprite m_ButtonPlay;
	sf::Sprite m_ButtonExit;
	int m_selectedButton;
};
