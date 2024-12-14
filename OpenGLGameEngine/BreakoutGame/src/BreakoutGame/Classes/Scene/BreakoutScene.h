#pragma once
#include <string.h>
#include <unordered_map>
#include <GameEngine.h>
#include "../Input/BreakoutSceneInputHandler.h"
#include "../Objects/Ball.h"
#include "../Objects/Paddle.h"
#include "../Managers/UIManager.h"
#include "../Managers/BrickManager.h"
#include "../Managers/GameManager.h"
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
		void initializeBoundaryObjects();
		void initializeMainShader();
		void initializeMainCamera();
		void changeCameraType();

		void onBallColliderEnter(std::shared_ptr<GameEntity> gameEntity);

		void handleOnLeftKey();
		void handleOnRightKey();
		void handleOnDownKey();
		void handleOnUpKey();
		void handleOnBallDebugKey();
		void handleOnBallReleasedKey();

		std::shared_ptr<Ball> m_Ball;
		std::shared_ptr<Paddle> m_Paddle;
		std::shared_ptr<UIManager> m_UIManager;
		std::shared_ptr<BrickManager> m_BrickManager;
		std::shared_ptr<GameManager> m_GameManager;
		
		std::shared_ptr<Shader> m_MainShader;
		//For debug purposes
		std::shared_ptr<IMovable> m_ControlledMovableObject;
	};


}
