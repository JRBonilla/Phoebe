#pragma once

#include "Mesh.h"
#include "camera/Camera.h"
#include "lights/LightSetup.h"

namespace ph { namespace renderer {

	struct RenderCommand {
		Mesh* mesh;
		Shader* shader;
		math::Mat4 transform;
	};

	typedef std::vector<RenderCommand> CommandQueue;

	class Renderer3D {
	protected:
		CommandQueue m_CommandQueue;
	public:
		virtual ~Renderer3D() {}

		virtual void Init() = 0;
		virtual void Begin() = 0;
		virtual void BeginScene(Camera* camera) = 0;
		
		virtual void Submit(const RenderCommand& command) = 0;
		virtual void SubmitMesh(Mesh* mesh, const math::Mat4& transform) = 0;
		virtual void SubmitLightSetup(const LightSetup& lightSetup) = 0;

		virtual void EndScene() = 0;
		virtual void End() = 0;
		virtual void Present() = 0;
	};

}}