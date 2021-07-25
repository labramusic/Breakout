#include "RenderSystem.hpp"

#include <ECS/Entities/EntityManager.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/RenderComponent.hpp>
#include <Game.hpp>
#include <AssetManager.hpp>


namespace breakout
{
	RenderSystem::RenderSystem(const Game &game) : System(game)
	{
	}

	RenderSystem::~RenderSystem() {}

	void RenderSystem::update()
	{
		SDL_Rect srcRect, destRect;
		srcRect.x = srcRect.y = 0;

		auto entities = entityManager.getEntitiesWithComponent<TransformComponent>();
		for (auto const& entity : entities)
		{
			const auto& transform = entityManager.getComponent<TransformComponent>(*entity);
			if (!entityManager.hasComponent<RenderComponent>(*entity)) continue;
			const auto& render = entityManager.getComponent<RenderComponent>(*entity);

			srcRect.w = transform.width;
			srcRect.h = transform.height;
			
			destRect.x = static_cast<int>(transform.position.x);
			destRect.y = static_cast<int>(transform.position.y);
			destRect.w = transform.width * transform.scale;
			destRect.h = transform.height * transform.scale;

			// TODO ref
			// tko crta tu ??? system bi trebao
			game.getAssetManager().Draw(render.tId, srcRect, destRect);
		}
	}
}
