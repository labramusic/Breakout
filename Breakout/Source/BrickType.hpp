#pragma once

#include <string>
#include <tinyxml.h>
#include <string>

namespace breakout
{
	class BrickType
	{
	public:
		BrickType(const TiXmlElement &node) : id(node.Attribute("Id")[0]), textureId("brick_"), hitSoundId(node.Attribute("HitSound")), breakScore(0)
		{
			textureId += id;

			const char *hp = node.Attribute("HitPoints");
			if (std::strcmp(hp, "Infinite") == 0) hitPoints = -1;
			else hitPoints = std::stoi(hp);

			// TODO sounds
			if (node.Attribute("BreakSound"))
				breakSoundId = node.Attribute("BreakSound");

			if (node.Attribute("BreakScore"))
				breakScore = std::stoi(node.Attribute("BreakScore"));
		}

		char GetId() const { return id; }
		std::string GetTextureId() const { return textureId; }
		int GetHitPoints() const { return hitPoints; }
		std::string GetHitSoundId() const { return hitSoundId; }
		std::string GetBreakSoundId() const { return breakSoundId; }
		int GetBreakScore() const { return breakScore; }

	private:
		char id;
		std::string textureId;
		int hitPoints;
		std::string hitSoundId;
		std::string breakSoundId;
		int breakScore;
	};
}
