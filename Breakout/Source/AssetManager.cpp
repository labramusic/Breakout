#include "AssetManager.hpp"

#include <SDL_image.h>
#include <filesystem>
#include <tinyxml.h>

#include "Game.hpp"
#include "Level.hpp"

namespace breakout
{
	AssetManager::AssetManager(Game &game) : game(game), renderer(game.GetRenderer())
	{
	}

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

	void AssetManager::AddTexture(const std::string &id, const char* path)
	{
		SDL_Surface *tmpSurface = IMG_Load(path);
		SDL_Texture *tex = SDL_CreateTextureFromSurface(&renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
		textures.emplace(id, tex);
	}

	void AssetManager::AddTexture(const std::string &id, SDL_Texture &texture)
	{
		if (textures[id])
		{
			SDL_DestroyTexture(textures[id]);
		}

		textures[id] = &texture;
	}

	SDL_Texture *AssetManager::GetTexture(const std::string &id)
	{
		return textures[id];
	}

	void AssetManager::Draw(const std::string &tId, SDL_Rect src, SDL_Rect dest)
	{
		SDL_RenderCopy(&renderer, GetTexture(tId), &src, &dest);
	}

	void AssetManager::DrawBackground(const std::string &tId)
	{
		SDL_Rect srcR, destR;
		srcR.x = srcR.y = 0;
		destR.x = destR.y = 0;
		srcR.w = destR.w = game.GetWindowWidth();
		srcR.h = destR.h = game.GetWindowHeight();
		Draw(tId, srcR, destR);
	}

	SDL_Texture *AssetManager::CreateTextureFromText(const std::string &fontId, const std::string &text, const SDL_Color color)
	{
		SDL_Surface *surf = TTF_RenderText_Blended(GetFont(fontId), text.c_str(), color);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(&renderer, surf);
		SDL_FreeSurface(surf);
		return texture;
	}

	void AssetManager::AddFont(const std::string &id, const char *path, const int fontSize)
	{
		fonts.emplace(id, TTF_OpenFont(path, fontSize));
	}

	TTF_Font *AssetManager::GetFont(const std::string &id)
	{
		return fonts[id];
	}

	void AssetManager::AddLevelFile(const std::string &id, const char *path)
	{
		levelPaths.emplace(id, path);
	}

	const char *AssetManager::GetLevelFile(const std::string &id)
	{
		return levelPaths[id];
	}

	void AssetManager::ParseLevel(Level &level)
	{
		TiXmlDocument doc;
		doc.LoadFile(GetLevelFile(level.GetLevelId()));

		TiXmlElement *levelNode = doc.FirstChildElement("Level");
		level.SetRowCount(std::stoi(levelNode->Attribute("RowCount")));
		level.SetColCount(std::stoi(levelNode->Attribute("ColumnCount")));
		level.SetRowSpacing(std::stoi(levelNode->Attribute("RowSpacing")));
		level.SetColSpacing(std::stoi(levelNode->Attribute("ColumnSpacing")));
		AddTexture(level.GetLevelId(), levelNode->Attribute("BackgroundTexture"));

		std::unordered_map<char, std::unique_ptr<BrickType>> brickTypesMap;
		TiXmlElement *brickTypes = levelNode->FirstChildElement("BrickTypes");
		for (TiXmlElement *node = brickTypes->FirstChildElement(); node; node = node->NextSiblingElement())
		{
			BrickType brickType(*node);
			brickTypesMap.emplace(brickType.GetId(), std::make_unique<BrickType>(brickType));
			AddTexture(brickType.GetTextureId(), node->Attribute("Texture"));
		}
		level.SetBrickTypes(brickTypesMap);

		std::string bricks(levelNode->FirstChildElement("Bricks")->FirstChild()->ToText()->Value());
		// parse level layout
		std::string layout;
		for (char brick : bricks)
		{
			if (brick == '_' || level.GetBrickTypes().find(brick) != level.GetBrickTypes().end())
			{
				layout += brick;
			}
		}
		level.SetLayout(layout);
	}
}
