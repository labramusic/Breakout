#pragma once

#include <string>
#include <tinyxml.h>

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
			else hitPoints = atoi(hp);

			// TODO sounds
			if (node.Attribute("BreakSound"))
				breakSoundId = node.Attribute("BreakSound");

			if (node.Attribute("BreakScore"))
				breakScore = atoi(node.Attribute("BreakScore"));
		}

		char id;
		std::string textureId;
		int hitPoints;
		std::string hitSoundId;
		std::string breakSoundId;
		int breakScore;
	};
}
