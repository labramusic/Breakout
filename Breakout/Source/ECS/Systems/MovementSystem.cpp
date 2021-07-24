#include "MovementSystem.hpp"

#include <SDL_events.h>
#include <string>

#include <ECS/Entities/EntityManager.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/MoveComponent.hpp>
#include <Scenes/SceneGameplay.hpp>
#include "Game.hpp"

namespace breakout
{
	MovementSystem::MovementSystem(EntityManager& entityManager) : System(entityManager), gameplayScene(nullptr)
	{
	}

	MovementSystem::~MovementSystem() 
	{
	}

	void MovementSystem::update(double time)
	{
		// TODO for each entity with move component apply movement
		// depending on transform component, clamp, bounciness etc.

		// move paddle
		const auto* paddle = entityManager.getEntityByTag("paddle");
		auto& paddleTransform = entityManager.getComponent<TransformComponent>(*paddle);
		auto& paddleMove = entityManager.getComponent<MoveComponent>(*paddle);

		if (movingLeft) paddleMove.velocity.x = -1;
		else if (movingRight) paddleMove.velocity.x = 1;
		else paddleMove.velocity.x = 0;

		paddleTransform.position += paddleMove.movementSpeed * paddleMove.velocity.Normalize() * time;

		// clamp to screen
		if (paddleTransform.position.x < 0) paddleTransform.position.x = 0;
		if (paddleTransform.position.x + paddleTransform.width > Game::instance().getWindowWidth())
			paddleTransform.position.x = Game::instance().getWindowWidth() - paddleTransform.width;

		
		// move ball
		const auto* ball = entityManager.getEntityByTag("ball");
		auto& ballTransform = entityManager.getComponent<TransformComponent>(*ball);
		auto& ballMove = entityManager.getComponent<MoveComponent>(*ball);
		ballTransform.position += ballMove.movementSpeed * ballMove.velocity.Normalize() * time;

		// hits borders
		if (ballTransform.position.x < 0 || ballTransform.position.x + ballTransform.width > Game::instance().getWindowWidth())
		{
			ballMove.velocity.x *= -1;
		}
		if (ballTransform.position.y < 25)
		{
			ballMove.velocity.y *= -1;
		}

		// out of bounds
		if (ballTransform.position.y + ballTransform.height > Game::instance().getWindowHeight())
		{
			resetPositions();
			
			--gameplayScene->lives;
			if (gameplayScene->lives == 0)
			{
				gameplayScene->gameOver();
			}
			else
			{
				gameplayScene->updateHUD("livesHUD", "Lives: " + std::to_string(gameplayScene->lives));
			}
		}

	}

	void MovementSystem::resetPositions()
	{
		auto& paddle = entityManager.getComponent<TransformComponent>(*entityManager.getEntityByTag("paddle"));
		auto& ball = entityManager.getComponent<TransformComponent>(*entityManager.getEntityByTag("ball"));
		paddle.position = paddle.initialPos;
		ball.position = ball.initialPos;
	}

	// input system/component ?
	void MovementSystem::onEvent(const SDL_Event& event)
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
				movingLeft = true;
			if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
				movingRight = true;
		}

		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
				movingLeft = false;
			if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
				movingRight = false;
		}
	}
}
