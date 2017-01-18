/*! \brief Handles everything that is displayed when the game has ended.
*
*
*
*/
#pragma once
#include "Scene.h"
#include "SceneStack.h"
#include "Score.h"

class GameoverScene : public Scene
{
public:
	GameoverScene(SceneStack& stack, Context context);

	void draw() override;									 /*!< This draws the game over scene, anything that is placed on the title scene is drawn here*/
	bool update(sf::Time deltaTime) override;				 /*!< This updates the game over scene, it will update everything on the game over scene*/
	bool handleEvent(const sf::Event& event) override;		 /*!< This handles the events on the game over scene*/

private:
	sf::Text m_text;	/*!< Text for buttons*/
	sf::Text m_score;	/*!< Score displayed on screen after game*/
	sf::Text m_time;	/*!< Time the game was played for*/
	sf::Text m_astrosRemaining;	/*!< Number of astronauts remaining, only displayed if game was won*/
	sf::Sprite m_background;	/*!< Background image of scene*/

	//	Buttons
	sf::Sprite m_ButtonPlay;	/*!< Play button image used to restart the game*/
	sf::Sprite m_ButtonExit;	/*!< Exit button image, used to exit the game*/
	int m_selectedButton;		/*!< Currently selected button*/
};
