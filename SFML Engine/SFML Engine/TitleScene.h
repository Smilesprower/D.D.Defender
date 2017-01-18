/*! \brief Handles everything that occurs when the game has been paused.
*
*
*
*/

#pragma once
#include "Scene.h"
#include "SceneStack.h"

class TitleScene : public Scene
{
public:
	TitleScene(SceneStack& stack, Context context);

	void draw() override;	/*!< This draws the title scene, anything that is placed on the title scene is drawn here*/
	bool update(sf::Time deltaTime) override;	/*!< This updates the title scene, it will update everything on the title scene*/
	bool handleEvent(const sf::Event& event) override;	/*!< This handles the events on the title scene*/

private:
	sf::Clock clock;

	sf::Text m_text;			/*!< Text On Buttons*/
	sf::Sprite m_background;	/*!< Main Menu Background*/

	//	Buttons
	sf::Sprite m_ButtonPlay;	/*!< Main Menu Play Button*/
	sf::Sprite m_ButtonExit;	/*!< Main Menu Exit Button*/
	int m_selectedButton;		/*!< Currently Selected Button*/
};
