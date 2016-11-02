#include "stdafx.h"
#include "SceneStack.h"
#include "Scene.h"
#include <assert.h>


SceneStack::SceneStack(Scene::Context context)
	:mContext(context)
	,mFactories()
	,mStack()
{
}

void SceneStack::update(sf::Time deltaTime)
{
	if (!mStack.empty())
	{
		auto itr = mStack.rbegin();
		(*itr)->update(deltaTime);
	}

	applyPendingChanges();
}

void SceneStack::draw()
{
	for each (const std::unique_ptr<Scene>&state in mStack){
		state->draw();
	}
}

void SceneStack::handleEvent(const sf::Event & event)
{
	if (!mStack.empty())
	{
		auto itr = mStack.rbegin();
		(*itr)->handleEvent(event);
	}
	applyPendingChanges();
}

void SceneStack::pushScene(Scenes::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}

void SceneStack::popScene()
{
	mPendingList.push_back(PendingChange(Pop));
}

void SceneStack::clearScene()
{
	mPendingList.push_back(PendingChange(Clear));
}

bool SceneStack::isEmpty() const
{
	return mStack.empty();
}


std::unique_ptr<Scene> SceneStack::createState(Scenes::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());
	return found->second();
}
void SceneStack::applyPendingChanges()
{
	for each (PendingChange change in mPendingList)
	{
		switch (change.action)
		{
		case Push:
			mStack.push_back(createState(change.stateID));
			break;

		case Pop:
			mStack.pop_back();
			break;

		case Clear:
			mStack.clear();
			break;
		}
	}
	mPendingList.clear();
}

SceneStack::PendingChange::PendingChange(Action action, Scenes::ID sceneID)
	: action(action)
	, stateID(sceneID)
{
}
