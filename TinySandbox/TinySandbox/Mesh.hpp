#pragma once

#include "includes/glmathematics/glm.hpp"
#include "includes/TinyObjLoader/tiny_obj_loader.h"

#define TINYOBJLOADER_IMPLEMENTATION 

namespace TinySandbox
{
	class Mesh
	{
		public:
			
			Mesh();
			Mesh(char* _filename);
			Mesh(const Mesh &val);
			Mesh& operator=(const Mesh &val);
			// Mesh& operator=(const Mesh &&val); TODO
			~Mesh();			
			
			char* filename;
			std::vector<glm::vec3> vertex;
			std::vector<glm::vec3> normal;
			std::vector<glm::vec2> uv0; // assume current only one uv set
			
			// std::vector<glm::vec3> vertexColors;
			// std::vector<glm::vec3> tangent; // no support for now
			// std::vector<glm::vec3> biTangent;			
	};
}