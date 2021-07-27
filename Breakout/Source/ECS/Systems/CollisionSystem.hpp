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
		explicit CollisionSystem(Game &game);
		virtual ~CollisionSystem();
		CollisionSystem(const CollisionSystem&) = delete;
		void operator=(const CollisionSystem&) = delete;

		void OnEvent(const SDL_Event &event) const;
		void Update(double time) const;

		void SetScene(SceneGameplay &scene) { gameplayScene = &scene; }

	private:
		static bool checkBallCollision(const TransformComponent &t1, const TransformComponent &t2);
		static bool paddleTopCollision(const TransformComponent &ballTr, const TransformComponent &paddleTr);
		static void handleBallCollisionWithBrick(const TransformComponent &ballTr, MoveComponent &ballM, const TransformComponent &brickTr) ;
		static void handleBallCollisionWithPaddle(const TransformComponent &ballTr, MoveComponent &ballM, const TransformComponent &paddleTr) ;

		SceneGameplay* gameplayScene;
	};
}
