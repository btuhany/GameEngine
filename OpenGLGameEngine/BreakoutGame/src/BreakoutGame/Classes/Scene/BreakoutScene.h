#pragma once
#include <string.h>
#include <unordered_map>
#include <GameEngine.h>
#include "../Input/BreakoutSceneInputHandler.h"

#include "../Managers/UIManager.h"

#include "../Managers/StateManager.h"
#include "../Data/InputTypeEnum.h"
#include "../StateControllers/InGameStateController.h"
namespace BreakoutGame
{
	class BreakoutScene : public Scene
	{
	public:
		BreakoutScene();
		BreakoutScene(BreakoutSceneInputHandler* inputHandler);
		~BreakoutScene();
		void Initialize(float viewPortWidth, float viewPortHeight) override;
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


		void instantiateEntities(std::vector<std::shared_ptr<GameEntity>> entityList);
	
		void onGameQuitCallback();
		void onInputCallback(InputType inputType);

		std::shared_ptr<UIManager> m_UIManager;
		std::shared_ptr<StateManager> m_StateManager;
		std::shared_ptr<Shader> m_MainShader;
	};


}
