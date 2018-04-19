#include "Model.h"

namespace ph { namespace renderer {

	using namespace math;

	Model::Model(const std::string& path, Material* material) {
		Load(path);
		m_Mesh->SetMaterial(material);
	}

	Model::~Model() {
		delete m_Mesh;
	}

	void Model::Load(const std::string& path) {
		PH_ASSERT(FileManager::GetFileExtension(path) == "phm", "Incorrect file format!");
		FILE* file = fopen(path.c_str(), "rb");
		PH_ASSERT(file, "Could not open " << path << "!");
		PHMFormat format;
		{
			{
				byte header[4];
				FileManager::ReadBytes(file, header, 4);
				PH_ASSERT(memcmp(header, format.header, 4) == 0, "Incorrect header found in file: " << path);
			}
			{
				byte buffer[1];
				FileManager::ReadBytes(file, buffer, 1);
				format.nameLength = *buffer;
			}
			{
				format.name = new char[format.nameLength + 1];
				FileManager::ReadBytes(file, (byte*)format.name, format.nameLength);
				format.name[format.nameLength] = '\0';
			}
			{
				byte buffer[4];
				FileManager::ReadBytes(file, buffer, 4);
				format.attribs = *(uint*)buffer;
			}
			{
				byte buffer[4];
				FileManager::ReadBytes(file, buffer, 4);
				format.vertexBufferSize = *(uint*)buffer;
			}
			{
				format.vertexData = new byte[format.vertexBufferSize];
				FileManager::ReadBytes(file, format.vertexData, format.vertexBufferSize);
			}
			{
				byte buffer[4];
				FileManager::ReadBytes(file, buffer, 4);
				format.indexBufferSize = *(uint*)buffer;
			}
			{
				format.indexData = new byte[format.indexBufferSize];
				FileManager::ReadBytes(file, format.indexData, format.indexBufferSize);
			}
			{
				byte footer[4];
				FileManager::ReadBytes(file, footer, 4);
				PH_ASSERT(memcmp(footer, format.footer, 4) == 0, "Incorrect footer found in file: " << path);
			}
		}
		fclose(file);

		PH_INFO("Successfully loaded model " << path);

		VertexBuffer* buffer = new VertexBuffer(BufferUsage::STATIC);
		buffer->SetData(format.vertexBufferSize, format.vertexData);

		VertexArray* va = new VertexArray();
		va->Bind();

		BufferLayout layout;
		layout.Push<Vec3>("position");
		layout.Push<Vec3>("normal");
		layout.Push<Vec2>("uv");
		layout.Push<Vec3>("tangent");
		layout.Push<Vec3>("bitangent");
		buffer->SetLayout(layout);

		buffer->Unbind();
		va->Unbind();

		IndexBuffer* ib = new IndexBuffer((uint*)format.indexData, format.indexBufferSize / sizeof(uint));
		m_Mesh = new Mesh(va, ib, nullptr);
	}

	void Model::Render(Renderer3D& renderer) {
		m_Mesh->Render(renderer);
	}

}}