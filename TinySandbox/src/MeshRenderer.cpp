#include "MeshRenderer.hpp"

#include <glad/glad.h>

#include <Windows.h>
#include <gl/GLU.h>

#include "Scene.hpp"
#include <iostream>
#include "GLFW_Windows.hpp"

#include "NormalDebugMaterial.hpp"

using namespace TinySandbox;

void MeshRenderer::Start()
{
	
}

void MeshRenderer::Update()
{

}

void MeshRenderer::OnGUI()
{

}

void MeshRenderer::SetEntity(Entity* _entity)
{
	entity = _entity;
	if (m_material) {
		m_material->entity = _entity;
	}
}

void MeshRenderer::OnRender()
{
	GraphicsAPI* API = GraphicsAPI::GetAPI();

	// Bind Material
	m_material->Use();
	
	// Draw Mesh
	API->BindVertexArray(m_VAO);
	API->DrawArrays(GraphicsAPI_DataType::TRIANGLES, m_mesh.vertex.size());
	
	// Clean up
	API->UnbindVertexArray();
	API->UnbindProgram();
}
