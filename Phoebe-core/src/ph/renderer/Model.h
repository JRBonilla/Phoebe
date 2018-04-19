#pragma once

#include <string>
#include "Mesh.h"

namespace ph { namespace renderer {

	struct PHMFormat {
		const char* header = "PHMF";
		const char* footer = "1234";
		char* name;
		byte  nameLength;
		uint  attribs;
		uint  vertexBufferSize;
		byte* vertexData;
		uint  indexBufferSize;
		byte* indexData;
	};

	class Model {
	private:
		Mesh* m_Mesh;
	public:
		Model(const std::string& path, Material* material);
		~Model();

		inline Mesh* GetMesh() const { return m_Mesh; }

		void Render(Renderer3D& renderer);
	private:
		void Load(const std::string& path);
	};

}}