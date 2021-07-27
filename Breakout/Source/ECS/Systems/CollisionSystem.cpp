#include "CollisionSystem.hpp"

#include <cmath>
#include <Vector2D.hpp>
#include <ECS/Entities/EntityManager.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/BrickComponent.hpp>
#include <ECS/Components/MoveComponent.hpp>
#include <Game.hpp>

#include <Scenes/SceneGameplay.hpp>

namespace breakout
{
	CollisionSystem::CollisionSystem(Game &game) : System(game), gameplayScene(nullptr)
	{
	}

	CollisionSystem::~CollisionSystem() 
	{
	}

	void CollisionSystem::Update(double time) const
	{
		const Entity *ball = entityManager.GetEntityByTag("ball");
		if (!ball) return;
		TransformComponent &ballTransform = entityManager.GetComponent<TransformComponent>(*ball);

		std::vector<Entity*> entities = entityManager.GetEntitiesWithComponent<TransformComponent>();
		for (Entity* const &entity : entities)
		{
			TransformComponent &otherTransform = entityManager.GetComponent<TransformComponent>(*entity);
			MoveComponent &ballMove = entityManager.GetComponent<MoveComponent>(*ball);
			if (entity->getTag() == "brick")
			{
				if (checkBallCollision(ballTransform, otherTransform))
				{
					handleBallCollisionWithBrick(ballTransform, ballMove, otherTransform);

					BrickComponent &brickComponent = entityManager.GetComponent<BrickComponent>(*entity);
					// -1 reserved for impenetrable
					if (brickComponent.GetHitPoints() > 0)
						brickComponent.TakeHit();
					if (brickComponent.GetHitPoints() == 0)
					{
						gameplayScene->AddScore(brickComponent.GetBrickType().GetBreakScore());

						entity->SetActive(false);
						break;
					}
				}
			}
			else if (entity->getTag() == "paddle")
			{
				if (checkBallCollision(ballTransform, otherTransform) && paddleTopCollision(ballTransform, otherTransform))
					handleBallCollisionWithPaddle(ballTransform, ballMove, otherTransform);
			}
		}
	}

	void CollisionSystem::OnEvent(const SDL_Event &event) const
	{
	}

	bool CollisionSystem::checkBallCollision(const TransformComponent &t1, const TransformComponent &t2)
	{
		// AABB
		return t1.GetPosition().x + t1.GetWidth() >= t2.GetPosition().x &&
			t2.GetPosition().x + t2.GetWidth() >= t1.GetPosition().x &&
			t1.GetPosition().y + t1.GetHeight() >= t2.GetPosition().y &&
			t2.GetPosition().y + t2.GetHeight() >= t1.GetPosition().y;
	}


	bool CollisionSystem::paddleTopCollision(const TransformComponent &ballTr, const TransformComponent &paddleTr)
	{
		return paddleTr.GetPosition().y <= ballTr.GetPosition().y + static_cast<float>(ballTr.GetHeight());
	}

	void CollisionSystem::handleBallCollisionWithBrick(const TransformComponent &ballTr, MoveComponent &ballM, const TransformComponent &brickTr) 
	{
		const float overlapLeft{ ballTr.GetPosition().x + ballTr.GetWidth() - brickTr.GetPosition().x };
		const float overlapRight{ brickTr.GetPosition().x + brickTr.GetWidth() - ballTr.GetPosition().x };
		const float overlapTop{ ballTr.GetPosition().y + ballTr.GetHeight() - brickTr.GetPosition().y };
		const float overlapBottom{ brickTr.GetPosition().y + brickTr.GetHeight() - ballTr.GetPosition().y };

		const bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
		const bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

		const float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
		const float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

		if (abs(minOverlapX) < abs(minOverlapY))
			ballM.SetVelocityX(ballFromLeft ? -abs(ballM.GetVelocity().x) : abs(ballM.GetVelocity().x));
		else
			ballM.SetVelocityY(ballFromTop ? -abs(ballM.GetVelocity().y) : abs(ballM.GetVelocity().y));
	}

	void CollisionSystem::handleBallCollisionWithPaddle(const TransformComponent &ballTr, MoveComponent &ballM, const TransformComponent &paddleTr) 
	{
		const double offset = paddleTr.GetPosition().x + (paddleTr.GetWidth() / 2.) - ballTr.GetPosition().x - (ballTr.GetWidth() / 2.);
		const double normalizedOffset = offset / (paddleTr.GetWidth() / 2.);
		const double angleOffset = normalizedOffset * 60 * (M_PI / 180);
		const double angle = angleOffset + M_PI / 2;
		ballM.SetVelocity(Vector2D(static_cast<float>(cos(angle)), static_cast<float>(sin(angle))));
		ballM.SetVelocityY(-ballM.GetVelocity().y);
	}
}
