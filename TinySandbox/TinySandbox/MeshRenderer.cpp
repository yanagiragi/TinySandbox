#include "MeshRenderer.hpp"

#include <glad/glad.h>

#include <Windows.h>
#include <gl/GLU.h>

#include "Scene.hpp"
#include <iostream>
#include "GLFW_Windows.hpp"

#include "includes/glmathematics/gtc/type_ptr.hpp" //value_ptr
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

void MeshRenderer::OnRender()
{
	GraphicsAPI* API = GraphicsAPI::GetAPI();

	glClear(GL_COLOR_BUFFER_BIT);
	
	const glm::mat4 viewMatrix = Scene::GetMainCamera()->ViewMatrix();
	const glm::mat4 projectionMatrix = Scene::GetMainCamera()->ProjectionMatrix();

	Material* mat = new NormalDebugMaterial("Shaders/normalDebug.vert", "Shaders/normalDebug.frag");

	mat->Use();
	mat->SetMat4("u_Model", glm::mat4(1.0f));
	mat->SetMat4("u_View", viewMatrix);
	mat->SetMat4("u_Projection", projectionMatrix);
	
	API->BindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_mesh.vertex.size());
	API->UnbindVertexArray();
}
