#pragma once

#include <vector>
#include <utility>
#include <functional>
#include <map>
#include "Scene.h"

class SceneStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

	explicit SceneStack(Scene::Context context);

	template <typename T>
	void createScene(Scenes::ID sceneID);
	void update(sf::Time deltaTime);
	void draw();
	void handleEvent(const sf::Event& event);
	void pushScene(Scenes::ID sceneID);
	void popScene();
	void clearScene();
	bool isEmpty() const;

private:
	struct PendingChange
	{
		explicit PendingChange(Action action, Scenes::ID sceneID = Scenes::None);

		Action action;
		Scenes::ID stateID;
	};
	void applyPendingChanges();
	std::vector<PendingChange> mPendingList;
	std::unique_ptr<Scene> createState(Scenes::ID sceneID);
	std::vector<std::unique_ptr<Scene>>	mStack;
	Scene::Context mContext;
	std::map<Scenes::ID, std::function<std::unique_ptr<Scene>()>> mFactories;
};
		
template <typename T>
void SceneStack::createScene(Scenes::ID sceneID)
{
	std::string tname = typeid(T).name();
	mFactories[sceneID] = [this]()
	{
		return std::unique_ptr<Scene>(new T(*this, mContext));
	};
}