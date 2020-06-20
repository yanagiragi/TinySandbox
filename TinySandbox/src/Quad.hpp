#pragma once

#include "Mesh.hpp"

namespace TinySandbox
{
	class Quad : public Mesh
	{
		public:

			Quad() : Mesh("../Resources/quad.obj") {}

			~Quad() {}
	};
}
