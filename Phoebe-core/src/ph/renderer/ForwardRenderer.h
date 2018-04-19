#pragma once

#include "Renderer3D.h"

namespace ph { namespace renderer {

	class ForwardRenderer : public Renderer3D {
	private:
		UniformBufferData*  m_SystemUniformBuffer;
		UniformBufferData*  m_DirectionalLightBuffer;
		UniformBufferData*  m_PointLightBuffer;
		UniformBufferData*  m_SpotLightBuffer;
		UniformBufferData*  m_LightingUniformBuffer;
	public:
		ForwardRenderer();
		~ForwardRenderer();

		void Init();
		void Begin();
		void BeginScene(Camera* camera);

		void Submit(const RenderCommand& command);
		void SubmitMesh(Mesh* mesh, const math::Mat4& transform);
		void SubmitLightSetup(const LightSetup& lightSetup);

		void EndScene();
		void End();
		void Present();
	private:
		void PushDirectionalLight(DirectionalLight* light);
		void PushPointLight(PointLight* light);
		void PushSpotLight(SpotLight* light);

		void SetSystemUniforms(Shader* shader);
		void SetLighting(Shader* shader);
		void SetModelMatrix(const math::Mat4& modelMatrix);
	};

}}