#pragma once

#include "Material.h"
#include "ph/math/Math.h"
#include "objects/IndexBuffer.h"
#include "objects/VertexArray.h"

namespace ph { namespace renderer {

	class Renderer3D;

	struct Vertex {
		math::Vec3 position;
		math::Vec3 normal;
		math::Vec2 uv;
		math::Vec3 tangent;
		math::Vec3 bitangent;
	};

	class Mesh {
	private:
		VertexArray*  m_VertexArray;
		IndexBuffer*  m_IndexBuffer;
		Material*     m_Material;
	public:
		Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, Material* material);
		Mesh(const Mesh* mesh);
		~Mesh();

		inline void SetMaterial(Material* material) { m_Material = material; }
		inline Material* GetMaterial() const { return m_Material; }

		void Render(Renderer3D& renderer);
	};

}}