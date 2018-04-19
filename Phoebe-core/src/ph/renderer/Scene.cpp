#include "Scene.h"
#include "ForwardRenderer.h"
#include "ph/entity/MeshComponent.h"
#include "ph/entity/TransformComponent.h"

namespace ph { namespace renderer {

	using namespace entity;

	Scene::Scene(bool visible) :
		m_Camera(new EditorCamera(math::Mat4::Perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f))),
		m_Renderer(new ForwardRenderer()),
		m_EntityManager(new EntityManager()),
		m_Initialized(false),
		m_Visible(visible) {
	}

	Scene::Scene(Camera* camera, bool visible) :
		m_Camera(camera),
		m_Renderer(new ForwardRenderer()),
		m_EntityManager(new EntityManager()),
		m_Initialized(false),
		m_Visible(visible) {
	}

	Scene::~Scene() {
		for (uint i = 0; i < m_LightSetups.size(); i++) {
			delete m_LightSetups[i];
		}
		m_LightSetups.clear();
		delete m_EntityManager;
		delete m_Camera;
		delete m_Renderer;
	}

	void Scene::Init() {
		m_Camera->Focus();
		m_Initialized = true;
	}

	void Scene::Add(Entity* entity) {
		m_EntityManager->Add(entity);
	}

	Entity* Scene::Remove(Entity* entity) {
		m_EntityManager->Remove(entity);
		return entity;
	}

	void Scene::PushLightSetup(LightSetup* lightSetup) {
		m_LightSetups.push_back(lightSetup);
	}

	LightSetup* Scene::PopLightSetup() {
		LightSetup* lightSetup = m_LightSetups.back();
		m_LightSetups.pop_back();
		return lightSetup;
	}

	void Scene::Update() {
		m_Camera->Update();
	}

	void Scene::Render() {
		m_Renderer->Begin();
		m_Renderer->BeginScene(m_Camera);

		for (LightSetup* lightSetup : m_LightSetups) {
			m_Renderer->SubmitLightSetup(*lightSetup);
		}

		for (Entity* entity : m_EntityManager->GetEntities()) {
			MeshComponent* meshComponent = entity->GetComponent<MeshComponent>();
			if (meshComponent) {
				TransformComponent* transformComponent = entity->GetComponent<TransformComponent>();
				PH_ASSERT(transformComponent, "Mesh does not have a transform!");
				m_Renderer->SubmitMesh(meshComponent->mesh, transformComponent->transform);
			}
		}

		m_Renderer->EndScene();
		m_Renderer->End();
		m_Renderer->Present();
	}

}}