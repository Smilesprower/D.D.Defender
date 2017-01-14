#include "stdafx.h"
#include "GameoverScene.h"




GameoverScene::GameoverScene(SceneStack & stack, Context context)
	: Scene(stack, context)
{
}

void GameoverScene::draw()
{
}

bool GameoverScene::update(sf::Time deltaTime)
{
	return true;
}

bool GameoverScene::handleEvent(const sf::Event & event)
{
	return true;
}
