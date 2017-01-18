/*! \brief The Pause Scene. Handles everything that occurs when the game has been paused.
*
*
*
*/

#pragma once
#include "Scene.h"
#include "SceneStack.h"

class PauseScene : public Scene
{
public:
	PauseScene(SceneStack& stack, Context context);

	void draw() override;
	bool update(sf::Time deltaTime) override;
	bool handleEvent(const sf::Event& event) override;

private:
	sf::Text m_text;
	sf::Sprite m_background;
	sf::Sprite m_background2;
};
