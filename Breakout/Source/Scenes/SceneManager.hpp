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

		explicit SceneManager(Game &game);
		~SceneManager();
		SceneManager(const SceneManager&) = delete;
		void operator=(const SceneManager&) = delete;

		void Update(double time);
		void Render();
		void HandleEvent(const SDL_Event& event);
		void ChangeScene(SceneName newScene);

		Scene &GetActiveScene() const { return *activeScene; }
		
	private:
		Game &game;

		std::unordered_map<SceneName, std::unique_ptr<Scene>> scenes;
		std::vector<std::unique_ptr<System>> systems;

		Scene *activeScene;
	};
}