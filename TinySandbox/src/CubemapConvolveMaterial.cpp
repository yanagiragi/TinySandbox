#include "CubemapConvolveMaterial.hpp"

namespace TinySandbox
{
	CubemapConvolveMaterial::CubemapConvolveMaterial() :
		Cubemap_BaseMaterial(nullptr, "../Shaders/cubemap.vert", "", "../Shaders/CubemapIrradianceConvolution.frag")
	{
		SetMainTexture(new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false));
	}

	CubemapConvolveMaterial::CubemapConvolveMaterial(Renderer* _renderer) :
		Cubemap_BaseMaterial(_renderer, "../Shaders/cubemap.vert", "", "../Shaders/CubemapIrradianceConvolution.frag")
	{
		SetMainTexture(new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false));
	}

	void CubemapConvolveMaterial::OnGUI()
	{

	}

	void CubemapConvolveMaterial::Use(int index)
	{
		m_api->BindProgram(m_program);
		m_api->EnableTexture2D();

		// Note: this is TextureCubemap, since it takes enviornmentMap as input
		this->SetTextureCubemap("u_environmentMap", GetMainTexture()->GetID());
		this->SetMat4("u_projectionMatrix", captureProjection);
		this->SetMat4("u_viewMatrix", captureViews[index]);
	}

	void CubemapConvolveMaterial::Unuse()
	{
		m_api->DisableTexture2D();

		BaseMaterial::Unuse();
	}
}