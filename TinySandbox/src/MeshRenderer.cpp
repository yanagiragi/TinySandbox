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
}

void MeshRenderer::OnRender()
{
	// Bind Material
	m_material->Use();

	// Draw Mesh
	m_api->BindVertexArray(m_VAO);
	m_api->DrawArrays(GraphicsAPI_DataType::TRIANGLES, m_mesh->vertex.size());
	
	// Clean up
	m_api->UnbindVertexArray();
	m_api->UnbindProgram();
	m_material->Unuse();
}
