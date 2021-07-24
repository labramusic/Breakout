#include "AssetManager.hpp"

#include <filesystem>
#include <tinyxml.h>
#include <direct.h>

#include "Game.hpp"
#include "Level.hpp"

namespace breakout
{
	AssetManager::~AssetManager()
	{
		for (auto it = textures.begin(); it != textures.end(); ++it)
		{
			SDL_DestroyTexture(it->second);
		}

		for (auto it = fonts.begin(); it != fonts.end(); ++it)
		{
			TTF_CloseFont(it->second);
		}
	}

	void AssetManager::addTexture(const std::string& id, const char* path)
	{
		SDL_Surface* tmpSurface = IMG_Load(path);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(&Game::instance().getRenderer(), tmpSurface);
		SDL_FreeSurface(tmpSurface);
		textures.emplace(id, tex);
	}


	void AssetManager::addTexture(const std::string id, SDL_Texture& texture)
	{
		textures[id] = &texture;
	}

	SDL_Texture* AssetManager::getTexture(const std::string id)
	{
		return textures[id];
	}

	void AssetManager::Draw(const std::string tId, SDL_Rect src, SDL_Rect dest)
	{
		SDL_RenderCopy(&Game::instance().getRenderer(), getTexture(tId), &src, &dest);
	}

	void AssetManager::DrawBackground(const std::string tId)
	{
		SDL_Rect srcR, destR;
		srcR.x = srcR.y = 0;
		destR.x = destR.y = 0;
		srcR.w = destR.w = Game::instance().getWindowWidth();
		srcR.h = destR.h = Game::instance().getWindowHeight();
		Draw(tId, srcR, destR);
	}

	SDL_Texture* AssetManager::CreateTextureFromText(const std::string& fontId, const std::string& text, const SDL_Color color)
	{
		SDL_Surface* surf = TTF_RenderText_Blended(getFont(fontId), text.c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(&Game::instance().getRenderer(), surf);
		SDL_FreeSurface(surf);
		return texture;
	}


	void AssetManager::addFont(const std::string& id, const char* path, const int fontSize)
	{
		fonts.emplace(id, TTF_OpenFont(path, fontSize));
	}

	TTF_Font* AssetManager::getFont(const std::string id)
	{
		return fonts[id];
	}

	void AssetManager::addLevelFile(const std::string& id, const char* path)
	{
		levelFiles.emplace(id, path);
	}

	const char* AssetManager::getLevelFile(const std::string& id)
	{
		return levelFiles[id];
	}

	void AssetManager::parseLevel(Level& level)
	{
		TiXmlDocument doc;
		doc.LoadFile(getLevelFile(level.levelId));

		auto* levelNode = doc.FirstChildElement("Level");
		level.rowCount = atoi(levelNode->Attribute("RowCount"));
		level.colCount = atoi(levelNode->Attribute("ColumnCount"));
		level.rowSpacing = atoi(levelNode->Attribute("RowSpacing"));
		level.colSpacing = atoi(levelNode->Attribute("ColumnSpacing"));
		addTexture(level.levelId, levelNode->Attribute("BackgroundTexture"));

		auto* brickTypes = levelNode->FirstChildElement("BrickTypes");
		for (auto* node = brickTypes->FirstChildElement(); node; node = node->NextSiblingElement())
		{
			auto brickType = BrickType();
			brickType.id = node->Attribute("Id");
			brickType.textureId = "brick" + brickType.id;
			addTexture(brickType.textureId, node->Attribute("Texture"));
			const char* hp = node->Attribute("HitPoints");
			if (std::strcmp(hp, "Infinite") == 0)
				brickType.hitPoints = -1;
			else brickType.hitPoints = atoi(hp);
			
			// TODO sounds
			const char* hitSound = node->Attribute("HitSound");
			if (node->Attribute("BreakSound"))
				const char* breakSound = node->Attribute("BreakSound");
			
			if (node->Attribute("BreakScore"))
				brickType.breakScore = atoi(node->Attribute("BreakScore"));

			level.brickTypes.emplace(brickType.id, std::make_unique<BrickType>(brickType));
		}

		level.layout = new std::string[level.rowCount * level.colCount];
		std::string bricks(levelNode->FirstChildElement("Bricks")->FirstChild()->ToText()->Value());
		// parse level layout
		int i = 0;
		for (char brick : bricks)
		{
			std::string s(1, brick);
			if (brick == '_' || level.brickTypes.find(s) != level.brickTypes.end())
			{
				level.layout[i++] = s;
			}
		}
	}
}
