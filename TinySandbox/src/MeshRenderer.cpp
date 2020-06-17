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

float time = 0;

void MeshRenderer::OnRender()
{
	GraphicsAPI* API = GraphicsAPI::GetAPI();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);
	
	const glm::mat4 viewMatrix = Scene::GetMainCamera()->ViewMatrix();
	const glm::mat4 projectionMatrix = Scene::GetMainCamera()->ProjectionMatrix();

	Material* mat = new NormalDebugMaterial("../Shaders/normalDebug.vert", "../Shaders/normalDebug.frag");

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1) * sin(time));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	
	time += 0.01f;

	mat->Use();
	mat->SetMat4("u_Model", modelMatrix);
	mat->SetMat4("u_View", viewMatrix);
	mat->SetMat4("u_Projection", projectionMatrix);
	
	API->BindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_mesh.vertex.size());
	API->UnbindVertexArray();
}
