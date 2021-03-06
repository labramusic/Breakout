﻿#pragma once

#include <map>
#include <SDL_ttf.h>
#include "Level.hpp"

namespace breakout
{
	class AssetManager
	{
	public:
		~AssetManager();

		// texture management
		void addTexture(const std::string& id, const char* path);
		void addTexture(std::string id, SDL_Texture& texture);
		SDL_Texture* getTexture(std::string id);
		void Draw(std::string tId, SDL_Rect src, SDL_Rect dest);
		void DrawBackground(std::string tId);
		SDL_Texture* CreateTextureFromText(const std::string& fontId, const std::string& text, SDL_Color color);

		// fonts
		void addFont(const std::string& id, const char* path, int fontSize);
		TTF_Font* getFont(std::string id);

		// level files
		void addLevelFile(const std::string& id, const char* path);
		const char* getLevelFile(const std::string& id);
		//std::vector<std::string> getLevelFiles();
		void parseLevel(Level& level);

	private:
		std::map<std::string, SDL_Texture*> textures;
		std::map<std::string, TTF_Font*> fonts;
		std::map<std::string, const char*> levelFiles;
	};

}