#include "PHMWriter.h"

namespace ph { namespace tools {

	PHMWriter::PHMWriter(const std::string& name, uint attribs, const std::vector<Vertex>& vertices, const std::vector<uint>& indices) {
		m_Format.nameLength       = (byte)name.length();
		m_Format.name             = &name[0];
		m_Format.attribs          = attribs;
		m_Format.vertexBufferSize = vertices.size() * sizeof(Vertex);
		m_Format.vertexData       = (byte*)&vertices[0];
		m_Format.indexBufferSize  = indices.size() * sizeof(uint);
		m_Format.indexData        = (byte*)&indices[0];
	}

	PHMWriter::~PHMWriter() {
	}

	void PHMWriter::WriteBytes(FILE* file, const byte* data, uint size) {
		fwrite(data, 1, size, file);
	}

	void PHMWriter::Write(const std::string& filename) {
		const PHMFormat& format = m_Format;

		FILE* file = fopen(filename.c_str(), "wb");
		WriteBytes(file, (byte*)format.header, 4);
		WriteBytes(file, &format.nameLength, 1);
		WriteBytes(file, (byte*)format.name, format.nameLength);
		WriteBytes(file, (byte*)&format.attribs, sizeof(uint));
		WriteBytes(file, (byte*)&format.vertexBufferSize, sizeof(uint));
		WriteBytes(file, format.vertexData, format.vertexBufferSize);
		WriteBytes(file, (byte*)&format.indexBufferSize, sizeof(uint));
		WriteBytes(file, format.indexData, format.indexBufferSize);
		WriteBytes(file, (byte*)format.footer, 4);
		fclose(file);

		printf("Successfully wrote %s.\n", filename.c_str());
	}

}}