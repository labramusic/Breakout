#pragma once

#include "System.hpp"

namespace breakout
{
	class AssetManager;

	class RenderSystem : public System
	{
	public:
		explicit RenderSystem(Game &game);
		virtual ~RenderSystem();
		RenderSystem(const RenderSystem&) = delete;
		void operator=(const RenderSystem&) = delete;
		
		void Update() const;

	private:
		AssetManager &assetManager;
	};
}