/*! \brief Requests the changing of scenes.
*
*
*
*/

#pragma once
#include <memory>
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneIdentifiers.h"
#include "SoundPlayer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MusicPlayer.h"

class SceneStack;
class Scene
{
public:
	/*! \brief Context holds map to all textures, render window and all fonts. Only one instance is every created and passed around.
	*
	*
	*
	*/
	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts);
		sf::RenderWindow* window;	/*!< Containsrender window*/
		TextureHolder* textures;	/*!< Contains map of textures*/
		FontHolder* fonts;			/*!< Contains map of fonts*/
	};

	Scene(SceneStack& stack, Context context);
	virtual	~Scene();

	virtual void draw() = 0;								/*!< Scene virtual draw function*/
	virtual bool update(sf::Time deltaTime) = 0;			/*!< Scene virtual update function*/
	virtual bool handleEvent(const sf::Event& event) = 0;	/*!< Scene virtual handle event function*/


protected:
	void requestStackPush(Scenes::ID sceneID);				/*!< Request scene to be pushed*/
	void requestStackPop();									/*!< Request scene to be popped*/
	void requestStateClear();								/*!< Request Flushing the stack of scenes*/
	Context	getContext() const;								/*!< Returns context */

private:
	SceneStack*	mStack;
	Context	mContext;
};
