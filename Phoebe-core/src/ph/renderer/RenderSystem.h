#pragma once

#include <glad\glad.h>
#include "ph\Common.h"
#include "ph\Types.h"
#include "ph\utils\Log.h"

namespace ph { namespace renderer {

	enum BufferType {
		COLOR_BUFFER   = BIT(0),
		DEPTH_BUFFER   = BIT(1),
		STENCIL_BUFFER = BIT(2)
	};

	enum class BlendFunction {
		ZERO,
		ONE,
		SOURCE_ALPHA,
		DESTINATION_ALPHA,
		ONE_MINUS_SOURCE_ALPHA
	};

	enum class DepthFunction {
		NEVER,
		LESS,
		EQUAL,
		LESS_THAN_OR_EQUAL,
		GREATER,
		NOT_EQUAL,
		GREATER_THAN_OR_EQUAL,
		ALWAYS
	};

	enum class FrontFace {
		CLOCKWISE,
		COUNTER_CLOCKWISE
	};

	enum class CullFace {
		BACK,
		FRONT,
		FRONT_AND_BACK
	};
	
	class RenderSystem {
	public:
		static void Init();

		static void Clear(uint buffer);

		static void SetDepthTesting(bool enabled);
		static void SetBlend(bool enabled);
		static void SetFaceCulling(bool enabled);
		static void SetMultiSampling(bool enabled);
		static void SetViewport(uint x, uint y, uint width, uint height);
		static void SetClearColor(float r, float g, float b, float a);

		static void SetBlendFunction(BlendFunction source, BlendFunction destination);
		static void SetDepthFunction(DepthFunction function);
		static void SetFrontFace(FrontFace frontFace);
		static void SetCullFace(CullFace cullFace);
	private:
		static uint const BlendFunctionToGL(BlendFunction function);
		static uint const DepthFunctionToGL(DepthFunction function);
		static uint const FrontFaceToGL(FrontFace frontFace);
		static uint const CullFaceToGL(CullFace cullFace);
		static uint const BufferToGL(uint buffer);
	private:
		RenderSystem() {}
	};

}}