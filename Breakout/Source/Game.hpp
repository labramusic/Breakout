#pragma once

#define SDL_MAIN_HANDLED

#include <SDL_render.h>

#include "AssetManager.hpp"
#include "Scenes/SceneManager.hpp"

namespace breakout
{
	class Game {
	public:
		~Game();

		static Game& instance()
		{
			static Game* instance = new Game();
			return *instance;
		}

		void init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags);
		int run();
		void clean();

		// shared context
		SDL_Window& getWindow() const { return *window; }
		int getWindowWidth() const { return windowWidth; }
		int getWindowHeight() const { return windowHeight; }
		SDL_Renderer& getRenderer() const { return *renderer; }
		AssetManager& getAssetManager() const { return *assetManager; }
		EntityManager& getEntityManager() const { return *entityManager; }
		SceneManager& getSceneManager() const { return *sceneManager; }
		//
		
	private:
		Game();
		
		void handleEvents();
		void update(double time);
		void render();

		int windowWidth;
		int windowHeight;
		bool running;
		SDL_Event event;
		
		//
		SDL_Window* window;
		SDL_Renderer* renderer;
		AssetManager* assetManager;
		EntityManager* entityManager;
		SceneManager* sceneManager;
		// 
	};
}