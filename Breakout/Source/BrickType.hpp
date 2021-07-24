#pragma once

#include <string>

namespace breakout
{
	class BrickType
	{
	public:
		std::string id;
		std::string textureId;
		int hitPoints;
		std::string hitSoundId;
		std::string breakSoundId;
		int breakScore = 0;
	};
}
