#pragma once

#include "../graphics/renderables/Renderable.h"
#include "../graphics/Renderer.h"
#include "../graphics/shaders/Shader.h"
#include "../graphics/camera/OrthographicCamera.h"

namespace ph { namespace graphics {

	class Layer {
	protected:
		bool						m_Visible;
		Renderer*					m_Renderer;
		std::vector<Renderable*>	m_Renderables;
		Shader*						m_Shader;
		Mat4						m_ProjectionMatrix;
		OrthographicCamera*			m_Camera;
	public:
		Layer(Renderer* renderer, Shader* shader, const math::Mat4& projectionMatrix, bool visible = true);
		virtual ~Layer();
		
		virtual void Init();
		virtual void Update();
		virtual void Render();
		
		virtual void Add(Renderable* renderable);
		inline const std::vector<Renderable*>& GetRenderables() const { return m_Renderables; }

		inline Shader* GetShader() const { return m_Shader; }
		inline void SetShader(Shader* shader) { m_Shader = shader; }

		inline OrthographicCamera* GetCamera() const { return m_Camera; }
		inline void SetCamera(OrthographicCamera* camera) { m_Camera = camera; }

		inline bool IsVisible() const { return m_Visible; }
		inline void SetVisible(bool visible) { m_Visible = visible; }
	};

}}
