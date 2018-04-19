#include <ph/renderer/MeshFactory.h>
#include <ph/renderer/Model.h>
#include <ph/renderer/TextureCube.h>
#include <ph/entity/MeshComponent.h>
#include <ph/entity/TransformComponent.h>
#include <ph/app/Application.h>
#include <ph/debug/DebugMenu.h>
#include "Test3D.h"

using namespace ph;
using namespace entity;
using namespace math;
using namespace renderer;

#define PLANE_SIZE 32

bool  rotateSphere  = false;
bool  moveRight  = true;
float glossiness = 100.0f;
float intensity  = 100.0f;
Vec3  pointLightPosition;
Vec4  pointLightColor;
Vec3  dirLightDirection;
Vec4  dirLightColor;
float fov;

Test3D::Test3D() {
	Scene::Scene();
	m_Rotation = 0.0f;
}

void Test3D::Init() {
	Scene::Init();

	fov = 65.0f;

	// Skybox
	std::string faces[6] = {
		"res/skybox/left.tga",   // xp
		"res/skybox/right.tga",  // xn
		"res/skybox/up.tga",     // yp
		"res/skybox/down.tga",   // yn
		"res/skybox/front.tga",  // zp
		"res/skybox/back.tga"    // zn
	};
	TextureCube* environment = new TextureCube("Skybox", faces);
	m_SkyboxMaterial = new Material(new Shader("Skybox", "shaders/skybox/Skybox.phsf"));
	m_SkyboxMaterial->SetRenderFlag(RenderFlag::DISABLE_DEPTH_TEST);
	m_SkyboxMaterial->SetTexture("environment_map", environment);
	Entity* skyboxEntity = new Entity();
	skyboxEntity->AddComponent(new MeshComponent(MeshFactory::CreateSkybox(m_SkyboxMaterial)));
	skyboxEntity->AddComponent(new TransformComponent(Mat4::Identity()));
	this->Add(skyboxEntity);
	
	// Entity materials
	m_SceneMaterial  = new Material(new Shader("Scene", "shaders/3d/Scene.phsf"));
	m_SceneMaterial->SetUniform("u_Glossiness", glossiness);
	Material* lampMaterial   = new Material(new Shader("Lamp", "shaders/3d/Lamp.phsf"));

	// Cyborg entity
	m_Cyborg = new Entity();
	Model* cyborgModel = new Model("res/models/nanosuit/nanosuit.phm", m_SceneMaterial);
	m_Cyborg->AddComponent(new MeshComponent(cyborgModel->GetMesh()));
	m_Cyborg->AddComponent(new TransformComponent(Mat4::Translate(Vec3(-4, 0, 0)) * Mat4::Scale(Vec3(0.7f, 0.7f, 0.7f))));
	this->Add(m_Cyborg);

	// Sphere entity
	m_Sphere = new Entity();
	Model* sphereModel = new Model("res/models/Sphere.phm", m_SceneMaterial);
	m_Sphere->AddComponent(new MeshComponent(sphereModel->GetMesh()));
	m_Sphere->AddComponent(new TransformComponent(Mat4::Translate(Vec3(4.0f, 2.5f, 0))));
	this->Add(m_Sphere);
	
	// Plane entity
	m_Plane = new Entity();
	m_Plane->AddComponent(new MeshComponent(MeshFactory::CreatePlane(PLANE_SIZE, PLANE_SIZE, Vec3(0, 1, 0), m_SceneMaterial)));
	m_Plane->AddComponent(new TransformComponent(Mat4::Identity()));
	this->Add(m_Plane);

	// Lamp that represents the current position of the point light
	m_Lamp = new Entity();
	m_Lamp->AddComponent(new MeshComponent(MeshFactory::CreateCube(1.0f, lampMaterial)));
	m_Lamp->AddComponent(new TransformComponent(Mat4::Identity()));
	this->Add(m_Lamp);

	// Light setup
	DirectionalLight* dirLight   = new DirectionalLight(Vec3(0.0f, 10.0f, 10.0f), Vec4(1.0f));
	PointLight*       pointLight = new PointLight(Vec3(0.0f, 10.0f, 10.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), intensity);
	/*
	SpotLight*        spotLight  = new SpotLight(GetCamera()->GetPosition(), GetCamera()->GetForwardDirection(), Vec4(1.0f), cos(toRadians(12.5f)), cos(toRadians(15.0f)), intensity);*/

	m_LightSetup = new LightSetup();
	m_LightSetup->Add(dirLight);
	m_LightSetup->Add(pointLight);
	PushLightSetup(m_LightSetup);

	pointLightPosition = pointLight->GetPosition();
	pointLightColor    = pointLight->GetColor();
	dirLightDirection  = dirLight->GetDirection();
	dirLightColor      = dirLight->GetColor();

	// Debug menu options
	debug::DebugMenu::Add("Point light intensity", &intensity, 0.0f, 200.0f);
	debug::DebugMenu::Add("Point light x", &pointLightPosition.x, -PLANE_SIZE, PLANE_SIZE);
	debug::DebugMenu::Add("Point light y", &pointLightPosition.y, -PLANE_SIZE, PLANE_SIZE);
	debug::DebugMenu::Add("Point light z", &pointLightPosition.z, -PLANE_SIZE, PLANE_SIZE);
	debug::DebugMenu::Add("Point light r", &pointLightColor.x, 0.0f, 1.0f);
	debug::DebugMenu::Add("Point light g", &pointLightColor.y, 0.0f, 1.0f);
	debug::DebugMenu::Add("Point light b", &pointLightColor.z, 0.0f, 1.0f);

	debug::DebugMenu::Add("Dir light direction x", &dirLightDirection.x, -PLANE_SIZE, PLANE_SIZE);
	debug::DebugMenu::Add("Dir light direction y", &dirLightDirection.y, -PLANE_SIZE, PLANE_SIZE);
	debug::DebugMenu::Add("Dir light direction z", &dirLightDirection.z, -PLANE_SIZE, PLANE_SIZE);
	debug::DebugMenu::Add("Dir light r", &dirLightColor.x, 0.0f, 1.0f);
	debug::DebugMenu::Add("Dir light g", &dirLightColor.y, 0.0f, 1.0f);
	debug::DebugMenu::Add("Dir light b", &dirLightColor.z, 0.0f, 1.0f);

	debug::DebugMenu::Add("Rotate sphere", &rotateSphere);
	debug::DebugMenu::Add("FOV", &fov, 0.0f, 65.0f);
}

void Test3D::Update() {
	Scene::Update();

	TransformComponent* cyborgTransform = m_Cyborg->GetComponent<TransformComponent>();
	TransformComponent* sphereTransform = m_Sphere->GetComponent<TransformComponent>();
	TransformComponent* lampTransform   = m_Lamp->GetComponent<TransformComponent>();
	
	if (rotateSphere) {
		Mat4 transform = Mat4::Rotate(m_Rotation, Vec3::XAxis()) * Mat4::Rotate(m_Rotation, Vec3::YAxis()) * Mat4::Rotate(m_Rotation, Vec3::ZAxis());
		sphereTransform->transform = Mat4::Translate(Vec3(4.0f, 2.5f, 0.0f)) * transform;
		m_Rotation++;
	}

	DirectionalLight* dirLight   = (DirectionalLight*)m_LightSetup->GetLights()[0];
	PointLight*       pointLight = (PointLight*)m_LightSetup->GetLights()[1];

	if (pointLight->GetIntensity() != intensity)          { pointLight->SetIntensity(intensity);         }
	if (pointLight->GetPosition()  != pointLightPosition) { pointLight->SetPosition(pointLightPosition); }
	if (pointLight->GetColor()     != pointLightColor)    { pointLight->SetColor(pointLightColor);       }
	if (dirLight->GetColor()       != dirLightColor)      { dirLight->SetColor(dirLightColor);           }
	if (dirLight->GetDirection()   != dirLightDirection)  { dirLight->SetDirection(dirLightDirection);   }

	lampTransform->transform = Mat4::Translate(pointLight->GetPosition());
	//GetCamera()->SetProjectionMatrix(Mat4::Perspective(fov, 16.0f / 9.0f, 0.1f, 1000.0f));
}