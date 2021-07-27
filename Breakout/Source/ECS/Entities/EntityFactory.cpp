#include "EntityFactory.hpp"

#include <Game.hpp>
#include <AssetManager.hpp>

#include <ECS/Components/BrickComponent.hpp>
#include <ECS/Components/RenderComponent.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/TextComponent.hpp>
#include <ECS/Components/MoveComponent.hpp>

namespace breakout
{
	EntityFactory::EntityFactory(Game &game) : game(game), manager(game.GetEntityManager())
	{
	}

	Entity &EntityFactory::CreatePaddle() const
	{
		Entity& paddleEntity(manager.createEntity("paddle"));
		const int w = game.GetWindowWidth();
		manager.addComponent<TransformComponent>(paddleEntity, (static_cast<float>(w) - 90.f) / 2.f, 610.f, 90.f, 15.f);
		manager.addComponent<MoveComponent>(paddleEntity, 4);
		manager.addComponent<RenderComponent>(paddleEntity, "paddle");
		return paddleEntity;
	}

	Entity &EntityFactory::CreateBall() const
	{
		Entity &ballEntity(manager.createEntity("ball"));
		const int w = game.GetWindowWidth();
		manager.addComponent<TransformComponent>(ballEntity, (static_cast<float>(w) - 10.f) / 2.f, 580.f, 10.f, 10.f);
		manager.addComponent<MoveComponent>(ballEntity, Vector2D(0.f, -1.f), 5);
		manager.addComponent<RenderComponent>(ballEntity, "ball");
		return ballEntity;
	}

	Entity &EntityFactory::CreateBrick(const BrickType &brickType, float x, float y, float w, float h) const
	{
		Entity &brickEntity(manager.createEntity("brick"));
		manager.addComponent<TransformComponent>(brickEntity, x, y, w, h);
		manager.addComponent<RenderComponent>(brickEntity, brickType.GetTextureId());
		manager.addComponent<BrickComponent>(brickEntity, brickType);
		return brickEntity;
	}

	Entity &EntityFactory::CreateLabel(const std::string &tag, float x, float y, const std::string &text, SDL_Color color) const
	{
		Entity &labelEntity(manager.createEntity(tag));
		manager.addComponent<TransformComponent>(labelEntity, x, y);
		TransformComponent &transform = manager.GetComponent<TransformComponent>(labelEntity);
		
		manager.addComponent<TextComponent>(labelEntity, text, "gameFont", color);
		TextComponent &textC = manager.GetComponent<TextComponent>(labelEntity);
		SDL_Texture *tex = game.GetAssetManager().CreateTextureFromText(textC.GetFontId(), text, color);
		game.GetAssetManager().AddTexture(tag, *tex);
		int w, h;
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		transform.SetWidth(w);
		transform.SetHeight(h);

		manager.addComponent<RenderComponent>(labelEntity, tag);
		return labelEntity;
	}
}
