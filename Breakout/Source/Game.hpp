#pragma once

#include <SDL_render.h>
#include <SDL_events.h>

#define SDL_MAIN_HANDLED

namespace breakout
{
	class AssetManager;
	class EntityManager;
	class EntityFactory;
	class SceneManager;

	class Game {
	public:
		Game();
		~Game();
		Game(const Game&) = delete;
		void operator=(const Game&) = delete;

		bool Init(const char *title, int xpos, int ypos, int width, int height);
		int Run();
		void Clean() const;

		// shared context
		SDL_Window &GetWindow() const { return *window; }
		int GetWindowWidth() const { return windowWidth; }
		int GetWindowHeight() const { return windowHeight; }
		SDL_Renderer &GetRenderer() const { return *renderer; }

		AssetManager &GetAssetManager() const { return *assetManager; }
		EntityManager &GetEntityManager() const { return *entityManager; }
		EntityFactory &GetEntityFactory() const { return *entityFactory; }
		SceneManager &GetSceneManager() const { return *sceneManager; }
		//
		
	private:		
		void handleEvents();
		void update(double time) const;
		void render() const;

		int windowWidth;
		int windowHeight;
		bool isRunning;
		SDL_Event event;
		
		SDL_Window* window;
		SDL_Renderer* renderer;
		AssetManager* assetManager;
		EntityManager* entityManager;
		EntityFactory* entityFactory;
		SceneManager* sceneManager;
	};
}