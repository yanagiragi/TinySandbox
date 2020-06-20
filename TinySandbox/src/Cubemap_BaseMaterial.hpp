#pragma once

#include "BaseMaterial.hpp"
#include "Texture.hpp"

#include <glmathematics/glm.hpp>
#include <glmathematics/gtc/matrix_transform.hpp>

namespace TinySandbox
{
	/*
	*	Note this class acts like a "base Material" instead of regular "Material"
	*	this headers defines common members and functions of Cubemap-based Materials
	*	Which is, instead of inherit Material, a cubemap-based material should inherit this instead.
	*/
	class Cubemap_BaseMaterial : public BaseMaterial
	{
		public:
			Cubemap_BaseMaterial() = delete;

			// Note that CubemapMaterial does not serve holding renderer!
			Cubemap_BaseMaterial(Renderer *_renderer, const char* _vertexShaderSource, const char* _geometryShaderSource, const char* _fragmentShaderSource) :
				BaseMaterial(_renderer, _vertexShaderSource, _geometryShaderSource, _fragmentShaderSource),
				captureProjection(glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f)),
				captureViews{
					glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
					glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
					glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
					glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
					glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
					glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
				}
			{
				// SetMainTexture(new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false));
			}

			void Use() override {
				throw "Use Use(index) instead!";
			}

			virtual void Use(int _index) = 0;

		protected:
			
			const glm::mat4 captureProjection;
			const glm::mat4 captureViews[6];

	};
}
