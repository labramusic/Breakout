#pragma once

#include <unordered_map>
#include <memory>
#include <SDL_events.h>


namespace breakout
{
	class Game;
	class Scene;
	class System;

	class SceneManager
	{
	public:
		enum class SceneName { Main, Gameplay, GameOver };

		explicit SceneManager(const Game &game);
		~SceneManager();
		
		void update(double time);
		void render();
		void handleEvent(const SDL_Event& event);
		void changeScene(const SceneName newScene);

		//Scene& getActiveScene() const { return *activeScene; }
		
	private:
		const Game &game;

		std::unordered_map<SceneName, std::unique_ptr<Scene>> scenes;
		std::vector<std::unique_ptr<System>> systems;

		Scene *activeScene;
	};
}