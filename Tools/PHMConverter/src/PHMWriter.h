#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Utils.h"

namespace ph { namespace tools {

	enum VertexAttribute {
		POSITION  = BIT(0),
		NORMAL    = BIT(1),
		UV        = BIT(2),
		TANGENT   = BIT(3),
		BITANGENT = BIT(4)
	};

	struct PHMFormat {
		const char* header = "PHMF";
		const char* footer = "1234";
		const char* name;
		byte  nameLength;
		uint  attribs;
		uint  vertexBufferSize;
		byte* vertexData;
		uint  indexBufferSize;
		byte* indexData;
	};

	class PHMWriter {
	private:
		PHMFormat m_Format;
	public:
		PHMWriter(const std::string& name, uint attribs, const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		~PHMWriter();

		void WriteBytes(FILE* file, const byte* data, uint size);
		void Write(const std::string& filename);
	};

}}