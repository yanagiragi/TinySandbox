#pragma once

#include "Material.hpp"

namespace TinySandbox
{
	class NormalDebugMaterial : public Material
	{
		public:
			NormalDebugMaterial(const char* _vertexShaderSource, const char* _fragmentShaderSource)
				: Material(_vertexShaderSource, "", _fragmentShaderSource)
			{

			}

			NormalDebugMaterial(const char* _vertexShaderSource, const char* _geometryShaderSource, const char* _fragmentShaderSource)
				: Material(_vertexShaderSource, _geometryShaderSource, _fragmentShaderSource)
			{

			}

			void OnGUI() override
			{

			}

			void Use() override
			{
				GraphicsAPI* API = GraphicsAPI::GetAPI();
				API->BindProgram(m_program);

				// Bind Uniform Variables
			}
	};
}