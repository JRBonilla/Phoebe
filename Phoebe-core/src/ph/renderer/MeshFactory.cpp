#include "MeshFactory.h"

namespace ph { namespace renderer { namespace MeshFactory {

	Mesh* CreatePlane(float width, float height, const math::Vec3& normal, Material* material) {
		using namespace math;

		Vec3 Vec = normal * 90.0f;
		Mat4 rotation = Mat4::Rotate(Vec.z, Vec3(1, 0, 0)) * Mat4::Rotate(Vec.y, Vec3(0, 1, 0)) * Mat4::Rotate(Vec.x, Vec3(0, 0, 1));

		Vertex data[4];
		memset(data, 0, 4 * sizeof(Vertex));

		data[0].position = rotation * Vec3(-width / 2.0f, 0.0f, -height / 2.0f);
		data[0].normal = normal;

		data[1].position = rotation * Vec3(-width / 2.0f, 0.0f,  height / 2.0f);
		data[1].normal = normal;

		data[2].position = rotation * Vec3( width / 2.0f, 0.0f,  height / 2.0f);
		data[2].normal = normal;

		data[3].position = rotation * Vec3( width / 2.0f, 0.0f, -height / 2.0f);
		data[3].normal = normal;

		VertexBuffer* buffer = new VertexBuffer(BufferUsage::STATIC);
		buffer->SetData(8 * sizeof(Vertex), &data[0]);

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

		uint* indices = new uint[6]{
			0, 1, 2,
			2, 3, 0
		};

		IndexBuffer* ib = new IndexBuffer(&indices[0], 6);
		return new Mesh(va, ib, material);
	}

	Mesh* CreateCube(float size, Material* material) {
		using namespace math;

		Vertex data[8];

		memset(data, 0, 8 * sizeof(Vertex));

		data[0].position = Vec3(-size / 2.0f,  size / 2.0f, -size / 2.0f); // 0
		data[1].position = Vec3(-size / 2.0f, -size / 2.0f, -size / 2.0f); // 1
		data[2].position = Vec3( size / 2.0f, -size / 2.0f, -size / 2.0f); // 2
		data[3].position = Vec3( size / 2.0f,  size / 2.0f, -size / 2.0f); // 3
		data[4].position = Vec3(-size / 2.0f, -size / 2.0f,  size / 2.0f); // 4
		data[5].position = Vec3(-size / 2.0f,  size / 2.0f,  size / 2.0f); // 5
		data[6].position = Vec3( size / 2.0f, -size / 2.0f,  size / 2.0f); // 6
		data[7].position = Vec3( size / 2.0f,  size / 2.0f,  size / 2.0f); // 7

		data[0].normal = Vec3(-1.0f,  1.0f, -1.0f); // 0
		data[1].normal = Vec3(-1.0f, -1.0f, -1.0f); // 1
		data[2].normal = Vec3( 1.0f, -1.0f, -1.0f); // 2
		data[3].normal = Vec3( 1.0f,  1.0f, -1.0f); // 3
		data[4].normal = Vec3(-1.0f, -1.0f,  1.0f); // 4
		data[5].normal = Vec3(-1.0f,  1.0f,  1.0f); // 5
		data[6].normal = Vec3( 1.0f, -1.0f,  1.0f); // 6
		data[7].normal = Vec3( 1.0f,  1.0f,  1.0f); // 7

		VertexBuffer* buffer = new VertexBuffer(BufferUsage::STATIC);
		buffer->SetData(8 * sizeof(Vertex), data);

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
		
		uint* indices = new uint[36]{
			0, 1, 2,  2, 3, 0,
			4, 1, 0,  0, 5, 4,
			2, 6, 7,  7, 3, 2,
			4, 5, 7,  7, 6, 4,
			0, 3, 7,  7, 5, 0,
			1, 4, 6,  6, 2, 1
		};

		IndexBuffer* ib = new IndexBuffer(indices, 36);
		return new Mesh(va, ib, material);
	}

	Mesh* MeshFactory::CreateSkybox(Material* material) {
		using namespace math;

		struct SkyboxVertex {
			math::Vec3 position;
		};

		SkyboxVertex data[8];

		memset(data, 0, 8 * sizeof(SkyboxVertex));

		data[0].position = Vec3(-1.0f,  1.0f, -1.0f); // 0
		data[1].position = Vec3(-1.0f, -1.0f, -1.0f); // 1
		data[2].position = Vec3( 1.0f, -1.0f, -1.0f); // 2
		data[3].position = Vec3( 1.0f,  1.0f, -1.0f); // 3
		data[4].position = Vec3(-1.0f, -1.0f,  1.0f); // 4
		data[5].position = Vec3(-1.0f,  1.0f,  1.0f); // 5
		data[6].position = Vec3( 1.0f, -1.0f,  1.0f); // 6
		data[7].position = Vec3( 1.0f,  1.0f,  1.0f); // 7

		VertexBuffer* buffer = new VertexBuffer(BufferUsage::STATIC);
		buffer->SetData(8 * sizeof(SkyboxVertex), &data);

		VertexArray* va = new VertexArray();
		va->Bind();

		BufferLayout layout;
		layout.Push<Vec3>("position");
		buffer->SetLayout(layout);

		buffer->Unbind();
		va->Unbind();

		uint* indices = new uint[36]{
			0, 1, 2,  2, 3, 0,
			4, 1, 0,  0, 5, 4,
			2, 6, 7,  7, 3, 2,
			4, 5, 7,  7, 6, 4,
			0, 3, 7,  7, 5, 0,
			1, 4, 6,  6, 2, 1
		};

		IndexBuffer* ib = new IndexBuffer(indices, 36);
		return new Mesh(va, ib, material);
	}

}}}