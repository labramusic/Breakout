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
		//Game();
		~Game();

		static Game& instance()
		{
			static Game* instance = new Game();
			return *instance;
		}

		// Initialize
		bool init(const char* title, int xpos, int ypos, int width, int height);
		// RunLoop
		int run();
		// Shutdown
		void clean();

		// shared context
		SDL_Window& getWindow() const { return *window; }
		int getWindowWidth() const { return windowWidth; }
		int getWindowHeight() const { return windowHeight; }
		SDL_Renderer& getRenderer() const { return *renderer; }

		AssetManager& getAssetManager() const { return *assetManager; }
		EntityManager& getEntityManager() const { return *entityManager; }
		EntityFactory& getEntityFactory() const { return *entityFactory; }
		SceneManager& getSceneManager() const { return *sceneManager; }
		//
		
	private:
		Game();
		
		// ProcessInput
		void handleEvents();
		// UpdateGame
		void update(double time);
		// GenerateOutput
		void render();

		int windowWidth;
		int windowHeight;
		bool isRunning;
		SDL_Event event;
		
		//
		SDL_Window* window;
		SDL_Renderer* renderer;
		AssetManager* assetManager;
		EntityManager* entityManager;
		EntityFactory* entityFactory;
		SceneManager* sceneManager;
		// 
	};
}