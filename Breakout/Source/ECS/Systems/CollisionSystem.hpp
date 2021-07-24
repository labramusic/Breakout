#pragma once

#include "System.hpp"
#include <SDL_events.h>

namespace breakout
{
	class SceneGameplay;
	class TransformComponent;
	class MoveComponent;

	class CollisionSystem : public System
	{
	public:
		CollisionSystem(EntityManager& entityManager);
		//CollisionSystem() : System(), scene(nullptr) {}
		virtual ~CollisionSystem();

		void update(double time);
		void onEvent(const SDL_Event& event);

		void setScene(SceneGameplay& scene) { gameplayScene = &scene; }

	private:
		bool checkBallCollision(const TransformComponent& t1, const TransformComponent& t2) const;
		bool paddleTopCollision(const TransformComponent& ballTr, const TransformComponent& paddleTr) const;
		void handleBallCollisionWithBrick(const TransformComponent& ballTr, MoveComponent& ballM, const TransformComponent& brickTr) const;
		void handleBallCollisionWithPaddle(const TransformComponent& ballTr, MoveComponent& ballM, const TransformComponent& paddleTr) const;

		SceneGameplay* gameplayScene;
	};
}
