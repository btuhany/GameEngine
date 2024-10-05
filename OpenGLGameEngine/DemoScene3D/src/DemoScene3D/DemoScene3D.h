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
	MeshData* createCubeMeshData();
	MeshData* createPlainMeshData();
	std::shared_ptr<ModelEntity> m_HelicopterSmall;
	std::shared_ptr<ModelEntity> ironman;
	std::shared_ptr<MeshEntity> spidermanPlain;
	std::shared_ptr<MeshEntity> spidermanCube;
	std::shared_ptr<ModelEntity> m_HelicopterBig;
	void handleOnRightKey();
	void handleOnLeftKey();
	void handleOnUpKey();
	void handleOnDownKey();
	void handleOnShiftKey();
	void handleOnShiftReleasedKey();
	void handleOnSpaceKey();
	DemoSceneInputHandler* m_InputReader;
	float m_CameraSpeed;
	float m_DeltaTime;

};

