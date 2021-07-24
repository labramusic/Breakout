#pragma once

#include <unordered_map>
#include <SDL_events.h>

namespace breakout
{
	class Scene;
	class System;

	class SceneManager
	{
	public:
		enum SceneName { Main, Gameplay, GameOver };

		SceneManager();
		~SceneManager();
		
		void update(double time);
		void render();
		void handleEvent(const SDL_Event& event);
		void changeScene(const SceneName newScene);

		//Scene& getActiveScene() const { return *activeScene; }
		
	private:
		//Game &game;

		Scene *activeScene;
		std::unordered_map<SceneName, Scene*> scenes;

		std::vector<System*> systems;
	};
}