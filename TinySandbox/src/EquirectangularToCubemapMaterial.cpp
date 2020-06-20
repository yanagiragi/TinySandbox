#include "EquirectangularToCubemapMaterial.hpp"

#include <glmathematics/glm.hpp>
#include <glmathematics/gtc/matrix_transform.hpp>

#include "CubemapConverter.hpp"

namespace TinySandbox
{
	EquirectangularToCubemapMaterial::EquirectangularToCubemapMaterial(Renderer* _renderer) : 
		Cubemap_BaseMaterial(_renderer, "../Shaders/cubemap.vert", "", "../Shaders/EquirectangularToCubemap.frag")
	{
		m_renderer = _renderer;
		SetMainTexture( new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false) );
	}

	void EquirectangularToCubemapMaterial::OnGUI()
	{

	}

	void EquirectangularToCubemapMaterial::Use(int index)
	{
		m_api->BindProgram(m_program);
		m_api->EnableTexture2D();
		
		// Note: this is Texture2D, since it is a equirectangular projected 2d image
		this->SetTexture2D("u_equirectangularMap", GetMainTexture()->GetID());		
		this->SetMat4("u_projectionMatrix", captureProjection);
		this->SetMat4("u_viewMatrix", captureViews[index]);
	}

	void EquirectangularToCubemapMaterial::Unuse()
	{
		m_api->DisableTexture2D();

		BaseMaterial::Unuse();
	}
}