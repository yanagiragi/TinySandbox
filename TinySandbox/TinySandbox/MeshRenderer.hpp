#pragma once

#include "GraphicsAPI.hpp"

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
				
				BindVAO(); // update VAO
			}

			const Mesh& GetMesh() const
			{
				return m_mesh;
			}

			void BindVAO()
			{
				GraphicsAPI* API = GraphicsAPI::GetAPI();

				API->SetupVAO(&m_VAO, &m_mesh, GraphicsAPI_DataType::STATIC_DRAW);
			}

			void Start() override;

			void Update() override;
		
			void OnGUI() override;

			void OnRender() override;

		private:
			Mesh m_mesh;
			unsigned int m_VAO;
	};
}
