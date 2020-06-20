#pragma once

#include "BaseMaterial.hpp"

namespace TinySandbox
{
	class BRDFLutMaterial : public BaseMaterial
	{
		public:
			BRDFLutMaterial();

			BRDFLutMaterial(Renderer* _renderer);

			void OnGUI() override;

			/*void Unuse() override;

			void Use() override;*/
	};
}