#pragma once

#include "GraphicsAPI.hpp"

#include "Renderer.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

namespace TinySandbox
{
	class MeshRenderer : public Renderer
	{
		public:

			MeshRenderer()
			{

			}

			~MeshRenderer()
			{
				if (m_mesh) {
					delete m_mesh;
				}
			}

			void SetMesh(Mesh* _mesh)
			{
				m_mesh = _mesh;
				
				BindVAO(); // update VAO
			}

			const Mesh* GetMesh() const
			{
				return m_mesh;
			}

			void BindVAO()
			{
				m_api->SetupVAO(&m_VAO, m_mesh, GraphicsAPI_DataType::STATIC_DRAW);
			}

			void Start() override;

			void Update() override;
		
			virtual void OnGUI() override;

			virtual void OnRender() override;

			void SetEntity(Entity* _entity) override;

		protected:
			Mesh* m_mesh;
			unsigned int m_VAO;
	};
}