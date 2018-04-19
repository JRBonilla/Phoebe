#include "ForwardRenderer.h"
#include "RenderSystem.h"
#include "ph/utils/Log.h"

namespace ph { namespace renderer {

	using namespace math;

	enum SystemUniformIndices {
		SystemUniformIndex_ProjectionMatrix = 0,
		SystemUniformIndex_ViewMatrix       = 1,
		SystemUniformIndex_ModelMatrix      = 2,
		SystemUniformIndex_CameraPosition   = 3,
		SystemUniformIndex_Size
	};

	enum LightingUniformIndices {
		LightingUniformIndex_DirLight   = 0,
		LightingUniformIndex_PointLight = 1,
		LightingUniformIndex_SpotLight  = 2,
		LightingUniformIndex_Size
	};

	ForwardRenderer::ForwardRenderer() {
		Init();
	}

	ForwardRenderer::~ForwardRenderer() {
		delete m_DirectionalLightBuffer;
		delete m_PointLightBuffer;
		delete m_SpotLightBuffer;
		delete m_LightingUniformBuffer;
		delete m_SystemUniformBuffer;
	}

	void ForwardRenderer::Init() {
		// System uniforms
		m_SystemUniformBuffer = new UniformBufferData(sizeof(Mat4) + sizeof(Mat4) + sizeof(Mat4) + sizeof(Vec3));
		m_SystemUniformBuffer->SetNumberOfOffsets(SystemUniformIndex_Size);
		
		m_SystemUniformBuffer->SetOffset(SystemUniformIndex_ProjectionMatrix, 0);
		m_SystemUniformBuffer->SetOffset(SystemUniformIndex_ViewMatrix, m_SystemUniformBuffer->GetOffset(SystemUniformIndex_ProjectionMatrix) + sizeof(Mat4));
		m_SystemUniformBuffer->SetOffset(SystemUniformIndex_ModelMatrix, m_SystemUniformBuffer->GetOffset(SystemUniformIndex_ViewMatrix) + sizeof(Mat4));
		m_SystemUniformBuffer->SetOffset(SystemUniformIndex_CameraPosition, m_SystemUniformBuffer->GetOffset(SystemUniformIndex_ModelMatrix) + sizeof(Mat4));

		// Directional lighting
		m_DirectionalLightBuffer = new UniformBufferData(DIRECTIONAL_LIGHT_SIZE);
		m_DirectionalLightBuffer->SetNumberOfOffsets(DirectionalLightIndex_Size);

		m_DirectionalLightBuffer->SetOffset(DirectionalLightIndex_Direction, 0);
		m_DirectionalLightBuffer->SetOffset(DirectionalLightIndex_Color, m_DirectionalLightBuffer->GetOffset(DirectionalLightIndex_Color) + sizeof(Vec3));

		// Point lighting
		m_PointLightBuffer = new UniformBufferData(POINT_LIGHT_SIZE);
		m_PointLightBuffer->SetNumberOfOffsets(PointLightIndex_Size);

		m_PointLightBuffer->SetOffset(PointLightIndex_Position,  0);
		m_PointLightBuffer->SetOffset(PointLightIndex_Color,     m_PointLightBuffer->GetOffset(PointLightIndex_Position) + sizeof(Vec3));
		m_PointLightBuffer->SetOffset(PointLightIndex_Intensity, m_PointLightBuffer->GetOffset(PointLightIndex_Color)    + sizeof(Vec4));

		// Spot lighting
		m_SpotLightBuffer = new UniformBufferData(SPOT_LIGHT_SIZE);
		m_SpotLightBuffer->SetNumberOfOffsets(SpotLightIndex_Size);

		m_SpotLightBuffer->SetOffset(SpotLightIndex_Position,    0);
		m_SpotLightBuffer->SetOffset(SpotLightIndex_Direction,   m_SpotLightBuffer->GetOffset(SpotLightIndex_Position)    + sizeof(Vec3));
		m_SpotLightBuffer->SetOffset(SpotLightIndex_Color,       m_SpotLightBuffer->GetOffset(SpotLightIndex_Direction)   + sizeof(Vec3));
		m_SpotLightBuffer->SetOffset(SpotLightIndex_CutOff,      m_SpotLightBuffer->GetOffset(SpotLightIndex_Color)       + sizeof(Vec4));
		m_SpotLightBuffer->SetOffset(SpotLightIndex_OuterCutOff, m_SpotLightBuffer->GetOffset(SpotLightIndex_CutOff)      + sizeof(float));
		m_SpotLightBuffer->SetOffset(SpotLightIndex_Intensity,   m_SpotLightBuffer->GetOffset(SpotLightIndex_OuterCutOff) + sizeof(float));

		// Lighting uniform buffer
		m_LightingUniformBuffer = new UniformBufferData(DIRECTIONAL_LIGHT_SIZE + POINT_LIGHT_SIZE + SPOT_LIGHT_SIZE);
		m_LightingUniformBuffer->SetNumberOfOffsets(LightingUniformIndex_Size);
		
		m_LightingUniformBuffer->SetOffset(LightingUniformIndex_DirLight,   0);
		m_LightingUniformBuffer->SetOffset(LightingUniformIndex_PointLight, m_LightingUniformBuffer->GetOffset(LightingUniformIndex_DirLight)   + DIRECTIONAL_LIGHT_SIZE);
		m_LightingUniformBuffer->SetOffset(LightingUniformIndex_SpotLight,  m_LightingUniformBuffer->GetOffset(LightingUniformIndex_PointLight) + POINT_LIGHT_SIZE);
	}

	void ForwardRenderer::Begin() {
		m_CommandQueue.clear();
	}

	void ForwardRenderer::BeginScene(Camera* camera) {
		m_SystemUniformBuffer->SetUniformData(SystemUniformIndex_ProjectionMatrix, camera->GetProjectionMatrix());
		m_SystemUniformBuffer->SetUniformData(SystemUniformIndex_ViewMatrix,       camera->GetViewMatrix());
		m_SystemUniformBuffer->SetUniformData(SystemUniformIndex_CameraPosition,   camera->GetPosition());
	}

	void ForwardRenderer::Submit(const RenderCommand& command) {
		m_CommandQueue.push_back(command);
	}

	void ForwardRenderer::SubmitMesh(Mesh* mesh, const math::Mat4& transform) {
		RenderCommand command;
		command.mesh = mesh;
		command.transform = transform;
		command.shader = mesh->GetMaterial()->GetShader();

		Submit(command);
	}

	void ForwardRenderer::SubmitLightSetup(const LightSetup& lightSetup) {
		for (uint i = 0; i < lightSetup.GetLights().size(); i++) {
			Light* currentLight = lightSetup.GetLights()[i];

			if (currentLight->GetType() == Light::Type::DIRECTIONAL_LIGHT) {
				DirectionalLight* light = (DirectionalLight*)currentLight;
				PushDirectionalLight(light);
			}
			else if (currentLight->GetType() == Light::Type::POINT_LIGHT) {
				PointLight* light = (PointLight*)currentLight;
				PushPointLight(light);
			}
			else if (currentLight->GetType() == Light::Type::SPOT_LIGHT) {
				SpotLight* light = (SpotLight*)currentLight;
				PushSpotLight(light);
			}
		}
	}

	void ForwardRenderer::PushDirectionalLight(DirectionalLight* light) {
		m_DirectionalLightBuffer->SetUniformData(DirectionalLightIndex_Direction, light->GetDirection());
		m_DirectionalLightBuffer->SetUniformData(DirectionalLightIndex_Color,     light->GetColor());

		m_LightingUniformBuffer->SetUniformData(LightingUniformIndex_DirLight, m_DirectionalLightBuffer->GetData(), DIRECTIONAL_LIGHT_SIZE);
	}

	void ForwardRenderer::PushPointLight(PointLight* light) {
		m_PointLightBuffer->SetUniformData(PointLightIndex_Position,  light->GetPosition());
		m_PointLightBuffer->SetUniformData(PointLightIndex_Color,     light->GetColor());
		m_PointLightBuffer->SetUniformData(PointLightIndex_Intensity, light->GetIntensity());

		m_LightingUniformBuffer->SetUniformData(LightingUniformIndex_PointLight, m_PointLightBuffer->GetData(), POINT_LIGHT_SIZE);
	}

	void ForwardRenderer::PushSpotLight(SpotLight* light) {
		m_SpotLightBuffer->SetUniformData(SpotLightIndex_Position,    light->GetPosition());
		m_SpotLightBuffer->SetUniformData(SpotLightIndex_Direction,   light->GetDirection());
		m_SpotLightBuffer->SetUniformData(SpotLightIndex_Color,       light->GetColor());
		m_SpotLightBuffer->SetUniformData(SpotLightIndex_CutOff,      light->GetCutOff());
		m_SpotLightBuffer->SetUniformData(SpotLightIndex_OuterCutOff, light->GetOuterCutOff());
		m_SpotLightBuffer->SetUniformData(SpotLightIndex_Intensity,   light->GetIntensity());

		m_LightingUniformBuffer->SetUniformData(LightingUniformIndex_SpotLight, m_SpotLightBuffer->GetData(), SPOT_LIGHT_SIZE);
	}

	void ForwardRenderer::EndScene() {
	}

	void ForwardRenderer::End() {
	}

	void ForwardRenderer::SetSystemUniforms(Shader* shader) {
		shader->SetSystemUniformBuffer(m_SystemUniformBuffer->GetData());
	}

	void ForwardRenderer::SetLighting(Shader* shader) {
		shader->SetLightingUniformBuffer(m_LightingUniformBuffer->GetData());
	}

	void ForwardRenderer::SetModelMatrix(const Mat4& modelMatrix) {
		m_SystemUniformBuffer->SetUniformData(SystemUniformIndex_ModelMatrix, modelMatrix);
	}

	void ForwardRenderer::Present() {
		for (RenderCommand command : m_CommandQueue) {
			command.shader->Bind();
			int flags = command.mesh->GetMaterial()->GetRenderFlags();
			bool depthTest = (flags & (int)RenderFlag::DISABLE_DEPTH_TEST) == 0;
			RenderSystem::SetDepthTesting(depthTest);
			SetModelMatrix(command.transform);
			SetSystemUniforms(command.shader);
			if (command.shader->UsesLights()) {
				SetLighting(command.shader);
			}
			command.mesh->Render(*this);
		}
	}

}}