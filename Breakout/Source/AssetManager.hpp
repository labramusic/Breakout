#pragma once

#include <SDL_ttf.h>

#include <map>
#include <string>

namespace breakout
{
	class Game;
	class Level;
	class TextComponent;

	class AssetManager
	{
	public:
		explicit AssetManager(Game &game);
		~AssetManager();
		AssetManager(const AssetManager&) = delete;
		void operator=(const AssetManager&) = delete;

		// texture management
		void AddTexture(const std::string &id, const char *path);
		void AddTexture(const std::string &id, SDL_Texture &texture);
		SDL_Texture *GetTexture(const std::string &id);
		void Draw(const std::string &tId, SDL_Rect src, SDL_Rect dest);
		void DrawBackground(const std::string &tId);
		SDL_Texture *CreateTextureFromText(const std::string &fontId, const std::string &text, const SDL_Color color);

		// fonts
		void AddFont(const std::string &id, const char *path, const int fontSize);
		TTF_Font *GetFont(const std::string &id);

		// level files
		void AddLevelFile(const std::string &id, const char *path);
		const char *GetLevelFile(const std::string &id);
		//std::vector<std::string> GetLevelFiles();
		void ParseLevel(Level &level);

	private:
		Game &game;
		SDL_Renderer &renderer;

		std::map<std::string, SDL_Texture*> textures;
		std::map<std::string, TTF_Font*> fonts;
		std::map<std::string, const char*> levelPaths;
	};
}