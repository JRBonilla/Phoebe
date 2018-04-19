#include "Mesh.h"

namespace ph { namespace renderer {

	Mesh::Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, Material* material)
		: m_VertexArray(vertexArray), m_IndexBuffer(indexBuffer), m_Material(material) {
	}

	Mesh::Mesh(const Mesh* mesh)
		: m_VertexArray(mesh->m_VertexArray), m_IndexBuffer(mesh->m_IndexBuffer), m_Material(mesh->m_Material) {
	}

	Mesh::~Mesh() {
		delete m_VertexArray;
		delete m_IndexBuffer;
		delete m_Material;
	}

	void Mesh::Render(Renderer3D& renderer) {
		m_Material->Bind();

		m_VertexArray->Bind();
		m_IndexBuffer->Bind();
		m_VertexArray->Draw(m_IndexBuffer->GetCount());
		m_IndexBuffer->Unbind();
		m_VertexArray->Unbind();

		m_Material->Unbind();
	}

}}