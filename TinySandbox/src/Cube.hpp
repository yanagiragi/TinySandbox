#pragma once

#include "Mesh.hpp"

namespace TinySandbox
{
	class Cube : public Mesh
	{
		public:
			
			Cube() 
			{
				Mesh::Mesh("../Resources/cube.obj");
			}

			~ Cube() 
			{

			}
	};
}
