#include "BRDFLutMaterial.hpp"

namespace TinySandbox
{
	BRDFLutMaterial::BRDFLutMaterial() : BaseMaterial(nullptr, "../Shaders/BrdfLut.vert", "", "../Shaders/BrdfLut.frag")
	{

	}

	BRDFLutMaterial::BRDFLutMaterial(Renderer* _renderer) : BaseMaterial(_renderer, "../Shaders/BrdfLut.vert", "", "../Shaders/BrdfLut.frag")
	{

	}

	void BRDFLutMaterial::OnGUI()
	{

	}
}