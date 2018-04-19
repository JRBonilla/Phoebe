#pragma once

#include <glad/glad.h>
#include "ph/utils/Log.h"

using namespace ph;

void GLCheckError() {
	glGetError();
}

bool GLLogCall(const char* function, const char* file, int line) {
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		PH_ERROR("[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line);
		return false;
	}
	return true;
}