#pragma once
#include <SDL_events.h>

#include "System.hpp"
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/MoveComponent.hpp>

namespace breakout
{
	class SceneGameplay;
	class CollisionSystem : public System
	{
	public:
		CollisionSystem(EntityManager& entityManager, SceneGameplay& scene) : System(entityManager)
		{
			this->scene = &scene;
		}
		CollisionSystem() : System(), scene(nullptr)
		{
		}

		void update(double time);
		void onEvent(const SDL_Event& event);

	private:
		bool checkBallCollision(const TransformComponent& t1, const TransformComponent& t2) const;
		bool paddleTopCollision(const TransformComponent& ballTr, const TransformComponent& paddleTr) const;
		void handleBallCollisionWithBrick(const TransformComponent& ballTr, MoveComponent& ballM, const TransformComponent& brickTr) const;
		void handleBallCollisionWithPaddle(const TransformComponent& ballTr, MoveComponent& ballM, const TransformComponent& paddleTr) const;

		SceneGameplay* scene;
	};
}
