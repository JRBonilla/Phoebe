#pragma once

#include "Renderer2D.h"
#include "camera/OrthographicCamera.h"
#include "renderables/Renderable2D.h"
#include "shaders/Shader.h"

namespace ph { namespace renderer {

	class Layer2D {
	protected:
		bool                        m_Visible;
		bool                        m_Initialized;
		Renderer2D*                 m_Renderer;
		std::vector<Renderable2D*>  m_Renderables;
		Shader*                     m_Shader;
		math::Mat4                  m_ProjectionMatrix;
		OrthographicCamera*         m_Camera;
	public:
		Layer2D(Shader* shader, const math::Mat4& projectionMatrix, bool visible = true);
		virtual ~Layer2D();
		
		virtual void Init();
		virtual void Update();
		virtual void Render();
		
		virtual void Add(Renderable2D* renderable);
		inline const std::vector<Renderable2D*>& GetRenderables() const { return m_Renderables; }

		inline Shader* GetShader() const { return m_Shader; }
		inline void SetShader(Shader* shader) { m_Shader = shader; }

		inline OrthographicCamera* GetCamera() const { return m_Camera; }
		inline void SetCamera(OrthographicCamera* camera) { m_Camera = camera; }

		inline bool IsInitialized() const { return m_Initialized; }
		inline bool IsVisible()     const { return m_Visible; }
		inline void SetVisibility(bool visible) { m_Visible = visible; }
	};

}}
