#pragma once

#include <unordered_map>
#include <SDL_events.h>

namespace breakout
{
	class Game;
	class Scene;
	class System;

	class SceneManager
	{
	public:
		enum SceneName { Main, Gameplay, GameOver };

		SceneManager(const Game &game);
		~SceneManager();
		
		void update(double time);
		void render();
		void handleEvent(const SDL_Event& event);
		void changeScene(const SceneName newScene);

		//Scene& getActiveScene() const { return *activeScene; }
		
	private:
		const Game &game;

		Scene *activeScene;
		std::unordered_map<SceneName, Scene*> scenes;

		std::vector<System*> systems;
	};
}