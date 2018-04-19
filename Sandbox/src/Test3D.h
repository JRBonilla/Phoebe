#pragma once

#include <ph/renderer/Scene.h>

class Test3D : public ph::renderer::Scene {
private:
	ph::renderer::LightSetup* m_LightSetup;

	ph::renderer::Material* m_SceneMaterial;
	ph::renderer::Material* m_SkyboxMaterial;

	ph::entity::Entity* m_Cyborg;
	ph::entity::Entity* m_Sphere;
	ph::entity::Entity* m_Plane;
	ph::entity::Entity* m_Lamp;

	float m_Rotation;
public:
	Test3D();
	void Init() override;
	void Update() override;
};