#pragma once

#include "../objects/RenderObject.h"
#include "../Renderer.h"
#include "../shaders/Shader.h"
#include "../camera/OrthographicCamera.h"

namespace fl { namespace graphics {

	class Layer
	{
	protected:
		bool m_Visible;
		Renderer* m_Renderer;
		std::vector<RenderObject*> m_Objects;
		Shader* m_Shader;
		mat4 m_ProjectionMatrix;
		OrthographicCamera* m_Camera;
	public:
		Layer(Renderer* renderer, Shader* shader, const math::mat4& projectionMatrix, bool visible = true);
		virtual ~Layer();
		
		virtual void Init();
		virtual void Update();
		virtual void Render();
		
		virtual void Add(RenderObject* renderable);
		inline const std::vector<RenderObject*>& GetObjects() const { return m_Objects; }

		inline Shader* GetShader() const { return m_Shader; }
		inline void SetShader(Shader* shader) { m_Shader = shader; }

		inline OrthographicCamera* GetCamera() const { return m_Camera; }
		inline void SetCamera(OrthographicCamera* camera) { m_Camera = camera; }

		inline bool IsVisible() const { return m_Visible; }
		inline void SetVisible(bool visible) { m_Visible = visible; }
	};

}}
