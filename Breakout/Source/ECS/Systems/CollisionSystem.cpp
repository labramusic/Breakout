#include "CollisionSystem.hpp"

#include <cmath>
#include <Vector2D.hpp>
#include <ECS/Entities/EntityManager.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/BrickComponent.hpp>
#include <ECS/Components/TextComponent.hpp>
#include <ECS/Components/MoveComponent.hpp>
#include <Game.hpp>

#include <Scenes/SceneGameplay.hpp>

namespace breakout
{
	CollisionSystem::CollisionSystem(EntityManager& entityManager) : System(entityManager), gameplayScene(nullptr)
	{
	}

	CollisionSystem::~CollisionSystem() 
	{
	}

	void CollisionSystem::update(double time)
	{
		// TODO get each entity with appropriate components and apply logic 
		// npr za laser i ship dohvati sve asteroide pa provjeravaj if coll

		// collision data components za lakse izracunavanje ?

		const Entity *ball = entityManager.getEntityByTag("ball");
		if (ball == nullptr) return;
		auto& ballTransform = entityManager.getComponent<TransformComponent>(*ball);

		auto entities = entityManager.getEntitiesWithComponent<TransformComponent>();
		for (auto const& entity : entities)
		{
			auto& otherTransform = entityManager.getComponent<TransformComponent>(*entity);
			auto& ballMove = entityManager.getComponent<MoveComponent>(*ball);
			if (entity->getTag() == "brick")
			{
				if (checkBallCollision(ballTransform, otherTransform))
				{
					handleBallCollisionWithBrick(ballTransform, ballMove, otherTransform);

					// TODO refactor with observer pattern
					auto& brickComponent = entityManager.getComponent<BrickComponent>(*entity);
					// -1 reserved for impenetrable
					if (brickComponent.hitPoints > 0) 
						--brickComponent.hitPoints;
					if (brickComponent.hitPoints == 0)
					{
						// increase score
						gameplayScene->score += brickComponent.brickType->breakScore;
						gameplayScene->updateHUD("scoreHUD", "Score: " + std::to_string(gameplayScene->score));

						entityManager.removeEntity(*entity);
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

		// if there are bricks other than impenetrable remaining
		auto bricks = entityManager.getEntitiesWithComponent<BrickComponent>();
		for (auto* brick : bricks)
		{
			if (entityManager.getComponent<BrickComponent>(*brick).brickType->hitPoints != -1)
			{
				return;
			}
		}
		
		gameplayScene->nextLevel();
	}

	void CollisionSystem::onEvent(const SDL_Event& event)
	{
	}


	bool CollisionSystem::checkBallCollision(const TransformComponent& t1, const TransformComponent& t2) const
	{
		// AABB
		return t1.position.x + t1.width >= t2.position.x &&
			t2.position.x + t2.width >= t1.position.x &&
			t1.position.y + t1.height >= t2.position.y &&
			t2.position.y + t2.height >= t1.position.y;
	}


	bool CollisionSystem::paddleTopCollision(const TransformComponent& ballTr, const TransformComponent& paddleTr) const
	{
		return paddleTr.position.y <= ballTr.position.y + ballTr.height;
	}

	void CollisionSystem::handleBallCollisionWithBrick(const TransformComponent& ballTr, MoveComponent& ballM, const TransformComponent& brickTr) const
	{
		const float overlapLeft{ ballTr.position.x + ballTr.width - brickTr.position.x };
		const float overlapRight{ brickTr.position.x + brickTr.width - ballTr.position.x };
		const float overlapTop{ ballTr.position.y + ballTr.height - brickTr.position.y };
		const float overlapBottom{ brickTr.position.y + brickTr.height - ballTr.position.y };

		const bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
		const bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

		const float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
		const float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

		if (abs(minOverlapX) < abs(minOverlapY))
			ballM.velocity.x = ballFromLeft ? -abs(ballM.velocity.x) : abs(ballM.velocity.x);
		else
			ballM.velocity.y = ballFromTop ? -abs(ballM.velocity.y) : abs(ballM.velocity.y);
	}

	void CollisionSystem::handleBallCollisionWithPaddle(const TransformComponent& ballTr, MoveComponent& ballM, const TransformComponent& paddleTr) const
	{
		double offset = paddleTr.position.x + (paddleTr.width / 2.f) - ballTr.position.x - (ballTr.width / 2.f);
		double normalizedOffset = offset / (paddleTr.width / 2.f);
		double angleOffset = normalizedOffset * 60 * (M_PI / 180);
		double angle = angleOffset + M_PI / 2;
		ballM.velocity = Vector2D(cos(angle), sin(angle));

		ballM.velocity.y *= -1;
	}
}
