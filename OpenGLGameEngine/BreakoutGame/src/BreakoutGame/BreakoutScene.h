#pragma once
#include <string.h>
#include <unordered_map>
#include <GameEngine.h>
#include "BreakoutSceneInputHandler.h"
#include "Ball.h"
#include "Paddle.h"
namespace BreakoutGame
{
	class BreakoutScene : public Scene
	{
	public:
		BreakoutScene();
		BreakoutScene(BreakoutSceneInputHandler* inputHandler);
		~BreakoutScene();
		void Initialize() override;
		void Start() override;
		void Update(GLfloat deltaTime) override;
	private:
		float m_ObjectMoveSpeed;
		float m_DeltaTime;

		BreakoutSceneInputHandler* m_InputHandler;
		void initializeInputCallbacks();
		void changeCameraType();

		void handleOnLeftKey();
		void handleOnRightKey();
		void handleOnDownKey();
		void handleOnUpKey();
		void handleOnBallDebugKey();

		std::shared_ptr<Ball> m_Ball;
		std::shared_ptr<Paddle> m_Paddle;
		std::shared_ptr<IMovable> m_ControlledMovableObject;
	};


}
