#pragma once
#include <GameEngine.h>
#include "DemoSceneInputHandler.h"
#include <GameEngine/Event/EventManager.h>

class DemoScene3D : public Scene
{
public:
	DemoScene3D();
	DemoScene3D(DemoSceneInputHandler* input);
	~DemoScene3D();
	void Initialize() override;
	void Start() override;
	void Update(GLfloat deltaTime) override;
private:
	void initializeSkybox();
	void initializeInputCallbacks();
	void initializeGameObjects();
	void initializeShadowShaders();
	void initializeLights();
	std::shared_ptr<MeshData> createCubeMeshData();
	std::shared_ptr<MeshData> createPlainMeshData();
	std::shared_ptr<ModelEntity> m_HelicopterSmall;
	std::shared_ptr<ModelEntity> ironman;
	std::shared_ptr<MeshEntity> spidermanPlain;
	std::shared_ptr<MeshEntity> spidermanCube;
	std::shared_ptr<ModelEntity> m_HelicopterBig;
	void handleOnRightKey();
	void handleOnLeftKey();
	void handleOnUpKey();
	void handleOnDownKey();
	void handleOnShiftKey(int keyState);
	void handleOnSpaceKey();
	void handleOnCtrlKey();
	void handleOnEnableDisableKey();
	void handleOnRotateLeftKey();
	void handleOnRotateRightKey();
	void handleOnPauseKey();
	void handleOnShaderChangeKey();
	void handleOnSelectRightObjectKey();
	void handleOnSelectLeftObjectKey();
	DemoSceneInputHandler* m_InputReader;
	float m_ObjectMoveSpeed;
	float m_ObjectRotateSpeed;
	float m_DeltaTime;
	std::shared_ptr<Shader> m_MainRenderShader;
	std::shared_ptr<Shader> m_NormalRenderShader;
	bool m_StopUpdate;
};

