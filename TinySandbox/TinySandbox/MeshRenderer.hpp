#pragma once

#include "Component.hpp"
#include "Mesh.hpp"

namespace TinySandbox
{
	class MeshRenderer : public Component
	{
		public:

			MeshRenderer()
			{

			}

			~MeshRenderer()
			{

			}

			void SetMesh(Mesh& _mesh)
			{
				m_mesh = _mesh;
			}

			void Start() override
			{

			}

			void Update() override
			{

			}
		
			void OnGUI() override
			{

			}

		private:
			Mesh m_mesh;
	};
}
