#pragma once
#include <memory>
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneIdentifiers.h"
#include "SoundPlayer.h"
#include <SFML/Graphics.hpp>

class SceneStack;
class Scene
{
public:

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts);
		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
	};

	Scene(SceneStack& stack, Context context);
	virtual	~Scene();

	virtual void draw() = 0;
	virtual bool update(sf::Time deltaTime) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;


protected:
	void requestStackPush(Scenes::ID sceneID);
	void requestStackPop();
	void requestStateClear();
	Context	getContext() const;

private:
	SceneStack*	mStack;
	Context	mContext;
};
