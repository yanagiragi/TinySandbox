#include "SkyboxRenderer.hpp"

#include "GraphicsAPI.hpp"
#include "SkyboxMaterial.hpp"
#include "Cube.hpp"

namespace TinySandbox
{
	SkyboxRenderer::SkyboxRenderer()
	{
		m_material = new SkyboxMaterial(this);
		
		m_mesh = new Cube();
		this->BindVAO();

		SetDisplayMode(Skybox_DisplayType::REGULAR);
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
		m_material->Unuse();
		m_api->UnbindVertexArray();
		m_api->UnbindProgram();
	}

	void SkyboxRenderer::SetDisplayMode(Skybox_DisplayType _mode)
	{
		SkyboxMaterial* mat = dynamic_cast<SkyboxMaterial*>(m_material);
		mat->SetDisplayMode(_mode);
	}

	void SkyboxRenderer::SetTexture(Texture* _other)
	{
		SkyboxMaterial* mat = dynamic_cast<SkyboxMaterial*>(m_material);
		mat->SetMainTexture(_other);
	}
}