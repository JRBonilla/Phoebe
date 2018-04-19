#pragma once

#include "Renderer3D.h"
#include "camera/Camera.h"
#include "camera/EditorCamera.h"
#include "camera/FPSCamera.h"
#include "lights/LightSetup.h"
#include "ph/entity/EntityManager.h"

namespace ph { namespace renderer {

	class Scene {
	private:
		entity::EntityManager*  m_EntityManager;
		LightSetupStack         m_LightSetups;
		bool                    m_Visible;
		bool                    m_Initialized;
		Camera*                 m_Camera;
		Renderer3D*             m_Renderer;
	public:
		Scene(bool visible = true);
		Scene(Camera* camera, bool visible = true);
		~Scene();

		virtual void Init();
		virtual void Update();
		virtual void Render();

		void Add(entity::Entity* entity);
		entity::Entity* Remove(entity::Entity* entity);

		inline Camera* GetCamera() const { return m_Camera; }
		inline void SetCamera(Camera* camera) { m_Camera = camera; }

		void PushLightSetup(LightSetup* lightSetup);
		LightSetup* PopLightSetup();
		
		inline bool IsInitialized() const { return m_Initialized; }
		inline bool IsVisible()     const { return m_Visible; }
		inline void SetVisibility(bool visible) { m_Visible = visible; }
	};

}}