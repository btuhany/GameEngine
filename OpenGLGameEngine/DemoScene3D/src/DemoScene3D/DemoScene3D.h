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
	void Initialize(float viewPortWidth, float viewPortHeight) override;
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
	void handleOnRightKey();
	void handleOnLeftKey();
	void handleOnUpKey();
	void handleOnDownKey();
	void handleOnShiftKey(int keyState);
	void handleOnSpaceKey();
	void handleOnCtrlKey();
	void handleOnEnableDisableKey();
	void handleOnDestroyObjectKey();
	void handleOnRotateLeftKey();
	void handleOnRotateRightKey();
	void handleOnPauseKey();
	void handleOnShaderChangeKey();
	void handleOnSelectRightObjectKey();
	void handleOnSelectLeftObjectKey();
	void handleOnScaleUpKey();
	void handleOnScaleDownKey();
	DemoSceneInputHandler* m_InputReader;
	float m_ObjectMoveSpeed;
	float m_ObjectRotateSpeed;
	float m_ObjectScaleSpeed;
	float m_DeltaTime;
	std::shared_ptr<Shader> m_MainRenderShader;
	std::shared_ptr<Shader> m_NormalRenderShader;
	bool m_StopUpdate;
	int m_CurrentObjectIndex = -1;
};

