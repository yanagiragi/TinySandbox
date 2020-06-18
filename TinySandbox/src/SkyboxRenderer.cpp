#include "SkyboxRenderer.hpp"

#include "GraphicsAPI.hpp"
#include "SkyboxMaterial.hpp"
#include "Cube.hpp"

namespace TinySandbox
{
	SkyboxRenderer::SkyboxRenderer()
	{
		m_mesh = new Cube();
	}

	SkyboxRenderer::~SkyboxRenderer()
	{

	}

	void SkyboxRenderer::OnRender()
	{
		// Bind Material
		m_material->Use();

		// Draw Mesh
		m_api->BindVertexArray(m_VAO);
		m_api->DrawArrays(GraphicsAPI_DataType::TRIANGLES, m_mesh->vertex.size());

		// Clean up
		m_api->UnbindVertexArray();
		m_api->UnbindProgram();
	}

	void SkyboxRenderer::SetTexture(Texture* _other)
	{
		SkyboxMaterial* mat = static_cast<SkyboxMaterial*>(m_material);
		mat->SetMainTexture(_other);
	}
}