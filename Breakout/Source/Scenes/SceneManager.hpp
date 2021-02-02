#pragma once

#include <unordered_map>

#include "Scenes/Scene.hpp"
#include "SceneGameplay.hpp"


namespace breakout
{
	class SceneManager
	{
	public:
		enum SceneName { Main, Gameplay, GameOver };

		SceneManager()
		{
			//Scene* main = new SceneMain();
			//Scene* gameOver = new SceneGameOver();

			Scene* gameplay = new SceneGameplay();
			addScene(Gameplay, *gameplay);

			// start with main scene
			activeScene = scenes[Gameplay];
			activeScene->loadScene();
		}

		~SceneManager()
		{
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
			scenes[newScene]->loadScene();
			activeScene = scenes[newScene];
		}
		
	private:
		Scene* activeScene;
		std::unordered_map<SceneName, Scene*> scenes;
		
		void addScene(SceneName name, Scene& scene)
		{
			scenes.emplace(name, &scene);
		}
	};
}