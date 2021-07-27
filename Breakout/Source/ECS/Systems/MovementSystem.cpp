#include "MovementSystem.hpp"

#include <SDL_events.h>
#include <string>

#include <ECS/Entities/EntityManager.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/MoveComponent.hpp>
#include <Scenes/SceneGameplay.hpp>
#include <Game.hpp>

namespace breakout
{
	MovementSystem::MovementSystem(Game &game) : System(game), gameplayScene(nullptr)
	{
	}

	MovementSystem::~MovementSystem() 
	{
	}

	void MovementSystem::Update(double time) const
	{
		// move paddle
		const Entity *paddle = entityManager.GetEntityByTag("paddle");
		TransformComponent &paddleTransform = entityManager.GetComponent<TransformComponent>(*paddle);
		MoveComponent &paddleMove = entityManager.GetComponent<MoveComponent>(*paddle);

		if (movingLeft) paddleMove.SetVelocityX(-1.f);
		else if (movingRight) paddleMove.SetVelocityX(1.f);
		else paddleMove.SetVelocityX(0.f);

		paddleTransform.SetPosition(paddleTransform.GetPosition()
			+ paddleMove.GetMovementSpeed() * paddleMove.GetVelocity().Normalize() * time);

		// clamp to screen
		if (paddleTransform.GetPosition().x < 0) paddleTransform.SetPositionX(0.f);
		if (paddleTransform.GetPosition().x + paddleTransform.GetWidth() > game.GetWindowWidth())
			paddleTransform.SetPositionX(static_cast<float>(game.GetWindowWidth() - paddleTransform.GetWidth()));
		
		// move ball
		const Entity *ball = entityManager.GetEntityByTag("ball");
		TransformComponent &ballTransform = entityManager.GetComponent<TransformComponent>(*ball);
		MoveComponent &ballMove = entityManager.GetComponent<MoveComponent>(*ball);

		ballTransform.SetPosition(ballTransform.GetPosition() 
			+ ballMove.GetMovementSpeed() * ballMove.GetVelocity().Normalize() * time);

		// hits borders
		if (ballTransform.GetPosition().x <= 0 || ballTransform.GetPosition().x + ballTransform.GetWidth() >= game.GetWindowWidth())
		{
			ballMove.SetVelocityX(-ballMove.GetVelocity().x);
		}
		if (ballTransform.GetPosition().y < 25)
		{
			ballMove.SetVelocityY(-ballMove.GetVelocity().y);
		}

		// out of bounds
		if (ballTransform.GetPosition().y + ballTransform.GetHeight() > game.GetWindowHeight())
		{
			ResetPositions();
			gameplayScene->LoseLife();
		}
	}

	void MovementSystem::ResetPositions() const
	{
		const Entity &paddle = *entityManager.GetEntityByTag("paddle");
		const Entity &ball = *entityManager.GetEntityByTag("ball");

		TransformComponent &paddleTr = entityManager.GetComponent<TransformComponent>(paddle);
		TransformComponent &ballTr = entityManager.GetComponent<TransformComponent>(ball);
		paddleTr.SetPosition(paddleTr.GetInitialPos());
		ballTr.SetPosition(ballTr.GetInitialPos());

		entityManager.GetComponent<MoveComponent>(paddle).SetVelocity(Vector2D(0.f, 0.f));
		entityManager.GetComponent<MoveComponent>(ball).SetVelocity(Vector2D(0.f, -1.f));
	}

	void MovementSystem::OnEvent(const SDL_Event &event)
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
