#include "stdafx.h"
#include "SceneStack.h"
#include "Scene.h"

Scene::Scene(SceneStack & stack, Context context)
	: mStack(&stack)
	, mContext(context)
{
}

Scene::~Scene()
{
}

Scene::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)
	: window(&window)
	, textures(&textures)
	, fonts(&fonts)
{
}


void Scene::requestStackPush(Scenes::ID stateID)
{
	mStack->pushScene(stateID);
}

void Scene::requestStackPop()
{
	mStack->popScene();
}

void Scene::requestStateClear()
{
	mStack->clearScene();
}

Scene::Context Scene::getContext() const
{
	return mContext;
}
