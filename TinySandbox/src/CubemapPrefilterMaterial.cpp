#include "CubemapPrefilterMaterial.hpp"

namespace TinySandbox
{
	CubemapPrefilterMaterial::CubemapPrefilterMaterial(Renderer* _renderer) :
		Cubemap_BaseMaterial(_renderer, "../Shaders/cubemap.vert", "", "../Shaders/CubemapPrefilter.frag")
	{
		SetMainTexture(new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false));
	}

	void CubemapPrefilterMaterial::OnGUI()
	{

	}

	void CubemapPrefilterMaterial::Use(int _index, int _lod, int _maxLod)
	{
		m_api->BindProgram(m_program);
		m_api->EnableTexture2D();

		float roughness = (float)_lod / (float)(_maxLod - 1);
		this->SetFloat("u_roughness", roughness);

		// Note: this is TextureCubemap, since it takes cubemap as input
		this->SetTextureCubemap("u_environmentMap", GetMainTexture()->GetID());
		this->SetMat4("u_projectionMatrix", captureProjection);
		this->SetMat4("u_viewMatrix", captureViews[_index]);
	}

	void CubemapPrefilterMaterial::Unuse()
	{
		m_api->DisableTexture2D();

		BaseMaterial::Unuse();
	}
}