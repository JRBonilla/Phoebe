#include "RenderSystem.h"

namespace ph { namespace renderer {

	void RenderSystem::Init() {
		SetConsoleColor(13);
		printf("-----------------------------------------------------------------\n");
		printf(" %s, OpenGL %s\n", glGetString(GL_RENDERER), glGetString(GL_VERSION));
		printf("-----------------------------------------------------------------\n");
		SetConsoleColor(15);

		SetMultiSampling(true);

		SetDepthTesting(true);
		SetDepthFunction(DepthFunction::LESS_THAN_OR_EQUAL);

		SetBlend(true);
		SetBlendFunction(BlendFunction::SOURCE_ALPHA, BlendFunction::ONE_MINUS_SOURCE_ALPHA);
		
		SetFaceCulling(true);
		SetFrontFace(FrontFace::COUNTER_CLOCKWISE);
		SetCullFace(CullFace::BACK);
	}

	void RenderSystem::Clear(uint buffer) {
		glClear(BufferToGL(buffer));
	}

	void RenderSystem::SetDepthTesting(bool enabled) {
		if (enabled) {
			glEnable(GL_DEPTH_TEST);
		}
		else {
			glDisable(GL_DEPTH_TEST);
		}
	}

	void RenderSystem::SetBlend(bool enabled) {
		if (enabled) {
			glEnable(GL_BLEND);
		}
		else {
			glDisable(GL_BLEND);
		}
	}

	void RenderSystem::SetFaceCulling(bool enabled) {
		if (enabled) {
			glEnable(GL_CULL_FACE);
		}
		else {
			glDisable(GL_CULL_FACE);
		}
	}

	void RenderSystem::SetMultiSampling(bool enabled) {
		if (enabled) {
			glEnable(GL_MULTISAMPLE);
		}
		else {
			glDisable(GL_MULTISAMPLE);
		}
	}

	void RenderSystem::SetViewport(uint x, uint y, uint width, uint height) {
		glViewport(x, y, width, height);
	}

	void RenderSystem::SetClearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void RenderSystem::SetBlendFunction(BlendFunction source, BlendFunction destination) {
		glBlendFunc(BlendFunctionToGL(source), BlendFunctionToGL(destination));
	}

	void RenderSystem::SetDepthFunction(DepthFunction function) {
		glDepthFunc(DepthFunctionToGL(function));
	}

	void RenderSystem::SetFrontFace(FrontFace frontFace) {
		glFrontFace(FrontFaceToGL(frontFace));
	}

	void RenderSystem::SetCullFace(CullFace cullFace) {
		glCullFace(CullFaceToGL(cullFace));
	}

	uint const RenderSystem::BlendFunctionToGL(BlendFunction function) {
		switch (function) {
		case BlendFunction::ZERO:                    return GL_ZERO;
		case BlendFunction::ONE:                     return GL_ONE;
		case BlendFunction::SOURCE_ALPHA:            return GL_SRC_ALPHA;
		case BlendFunction::DESTINATION_ALPHA:       return GL_DST_ALPHA;
		case BlendFunction::ONE_MINUS_SOURCE_ALPHA:  return GL_ONE_MINUS_SRC_ALPHA;
		}
		return 0;
	}

	uint const RenderSystem::DepthFunctionToGL(DepthFunction function) {
		switch (function) {
		case DepthFunction::NEVER:                  return GL_NEVER;
		case DepthFunction::LESS:                   return GL_LESS;
		case DepthFunction::EQUAL:                  return GL_EQUAL;
		case DepthFunction::LESS_THAN_OR_EQUAL:     return GL_LEQUAL;
		case DepthFunction::GREATER:                return GL_GREATER;
		case DepthFunction::NOT_EQUAL:              return GL_NOTEQUAL;
		case DepthFunction::GREATER_THAN_OR_EQUAL:  return GL_GEQUAL;
		case DepthFunction::ALWAYS:                 return GL_ALWAYS;
		}
		return 0;
	}

	uint const RenderSystem::FrontFaceToGL(FrontFace frontFace) {
		switch (frontFace) {
		case FrontFace::CLOCKWISE:          return GL_CW;
		case FrontFace::COUNTER_CLOCKWISE:  return GL_CCW;
		}
		return 0;
	}

	uint const RenderSystem::CullFaceToGL(CullFace cullFace) {
		switch (cullFace) {
		case CullFace::BACK:            return GL_BACK;
		case CullFace::FRONT:           return GL_FRONT;
		case CullFace::FRONT_AND_BACK:  return GL_FRONT_AND_BACK;
		}
		return 0;
	}

	uint const RenderSystem::BufferToGL(uint buffer) {
		uint result = 0;
		if (buffer & COLOR_BUFFER) {
			result |= GL_COLOR_BUFFER_BIT;
		}
		if (buffer & DEPTH_BUFFER) {
			result |= GL_DEPTH_BUFFER_BIT;
		}
		if (buffer & STENCIL_BUFFER) {
			result |= GL_STENCIL_BUFFER_BIT;
		}
		return result;
	}
	
}}