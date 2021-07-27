#include "RenderSystem.hpp"

#include <ECS/Entities/EntityManager.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/RenderComponent.hpp>
#include <Game.hpp>
#include <AssetManager.hpp>

namespace breakout
{
	RenderSystem::RenderSystem(Game &game) : System(game), assetManager(game.GetAssetManager())
	{
	}

	RenderSystem::~RenderSystem() {}

	void RenderSystem::Update() const
	{
		SDL_Rect srcRect, destRect;
		srcRect.x = srcRect.y = 0;

		std::vector<Entity*> entities = entityManager.GetEntitiesWithComponent<TransformComponent>();
		for (Entity* const &entity : entities)
		{
			const TransformComponent &transform = entityManager.GetComponent<TransformComponent>(*entity);
			if (!entityManager.HasComponent<RenderComponent>(*entity)) continue;
			const RenderComponent &render = entityManager.GetComponent<RenderComponent>(*entity);

			srcRect.w = transform.GetWidth();
			srcRect.h = transform.GetHeight();
			
			destRect.x = static_cast<int>(transform.GetPosition().x);
			destRect.y = static_cast<int>(transform.GetPosition().y);
			destRect.w = transform.GetWidth() * transform.GetScale();
			destRect.h = transform.GetHeight() * transform.GetScale();

			assetManager.Draw(render.GetTId(), srcRect, destRect);
		}
	}
}
