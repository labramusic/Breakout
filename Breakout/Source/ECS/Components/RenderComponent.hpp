#pragma once

namespace breakout
{
	class RenderComponent : public Component
	{
	public:
		//RenderComponent() = default;
		RenderComponent(const std::string tId) : tId(tId) {}

		std::string tId;
	};

}