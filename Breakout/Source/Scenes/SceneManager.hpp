#pragma once

#include <unordered_map>

#include "Scenes/Scene.hpp"
#include "SceneGameplay.hpp"
#include "SceneMain.hpp"
//#include "Game.hpp"

namespace breakout
{
	class SceneManager
	{
	public:
		enum SceneName { Main, Gameplay, GameOver };

		SceneManager();

		~SceneManager()
		{
			std::cout << "calling destructor of scene manager" << std::endl;

			for (auto it = systems.begin(); it != systems.end(); ++it) {
				delete *it;
			}

			for (auto it = scenes.begin(); it != scenes.end(); ++it) {
				delete it->second;
			}
		}
		
		void update(double time)
		{
			activeScene->update(time);
		}

		void render()
		{
			activeScene->render();
		}

		void handleEvent(const SDL_Event& event)
		{
			activeScene->handleEvent(event);
		}

		void changeScene(const SceneName newScene)
		{
			activeScene->unloadScene();
			activeScene = scenes[newScene];
			activeScene->loadScene();
		}

		//Scene& getActiveScene() const { return *activeScene; }
		
	private:
		//Game &game;

		Scene *activeScene;
		std::unordered_map<SceneName, Scene*> scenes;

		std::vector<System*> systems;
		
		// shared_ptr ?
		//void addScene(SceneName name, Scene &scene)
		//{
		//	scenes.emplace(name, &scene);
		//}
	};
}