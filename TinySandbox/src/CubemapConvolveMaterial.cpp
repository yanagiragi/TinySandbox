#include "CubemapConvolveMaterial.hpp"

namespace TinySandbox
{
	CubemapConvolveMaterial::CubemapConvolveMaterial(Renderer* _renderer) :
		Cubemap_BaseMaterial("../Shaders/cubemap.vert", "", "../Shaders/CubemapIrradianceConvolution.frag")
	{
		m_renderer = _renderer;
		m_mainTexture = new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false);
	}

	void CubemapConvolveMaterial::OnGUI()
	{

	}

	void CubemapConvolveMaterial::Use(int index)
	{
		m_api->BindProgram(m_program);
		m_api->EnableTexture2D();

		// Note: this is TextureCubemap, since it takes enviornmentMap as input
		this->SetTextureCubemap("u_environmentMap", m_mainTexture->GetID());
		this->SetMat4("u_projectionMatrix", captureProjection);
		this->SetMat4("u_viewMatrix", captureViews[index]);
	}

	void CubemapConvolveMaterial::Unuse()
	{
		m_api->DisableTexture2D();

		BaseMaterial::Unuse();
	}
}