#include "EntityFactory.hpp"

#include <ECS/Components/BrickComponent.hpp>
#include <ECS/Components/RenderComponent.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/TextComponent.hpp>
#include <ECS/Components/MoveComponent.hpp>

#include "Game.hpp"
#include "AssetManager.hpp"

namespace breakout
{
	Entity& EntityFactory::createPaddle() const
	{
		Entity& paddleEntity(manager->createEntity("paddle"));
		const auto w = Game::instance().getWindowWidth();
		manager->addComponent<TransformComponent>(paddleEntity, (w-90.f)/2, 610.f, 90.f, 15.f);
		manager->addComponent<MoveComponent>(paddleEntity, 4);
		manager->addComponent<RenderComponent>(paddleEntity, "paddle");
		return paddleEntity;
	}

	Entity& EntityFactory::createBall() const
	{
		auto& ballEntity(manager->createEntity("ball"));
		const auto w = Game::instance().getWindowWidth();
		manager->addComponent<TransformComponent>(ballEntity, (w-10.f)/2, 580.f, 10.f, 10.f);
		manager->addComponent<MoveComponent>(ballEntity, Vector2D(0, -1), 5);
		manager->addComponent<RenderComponent>(ballEntity, "ball");
		return ballEntity;
	}

	Entity& EntityFactory::createBrick(const BrickType& brickType, float x, float y, float w, float h) const
	{
		auto& brickEntity(manager->createEntity("brick"));
		manager->addComponent<TransformComponent>(brickEntity, x, y, w, h);
		manager->addComponent<RenderComponent>(brickEntity, brickType.textureId);
		manager->addComponent<BrickComponent>(brickEntity, brickType);
		return brickEntity;
	}

	Entity& EntityFactory::createLabel(const std::string& tag, float x, float y, const std::string& text, SDL_Color color) const
	{
		auto& labelEntity(manager->createEntity(tag));
		manager->addComponent<TransformComponent>(labelEntity, x, y);
		auto& transform = manager->getComponent<TransformComponent>(labelEntity);
		
		manager->addComponent<TextComponent>(labelEntity, text, "gameFont", color);
		auto& textC = manager->getComponent<TextComponent>(labelEntity);
		SDL_Texture* tex = Game::instance().getAssetManager().CreateTextureFromText(textC.fontId, text, color);
		Game::instance().getAssetManager().addTexture(tag, *tex);
		SDL_QueryTexture(tex, nullptr, nullptr, &transform.width, &transform.height);

		manager->addComponent<RenderComponent>(labelEntity, tag);
		return labelEntity;
	}
}
