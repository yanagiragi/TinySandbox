#include "Scene.hpp"

#include "MeshRenderer.hpp"

#include "NormalDebugMaterial.hpp"
#include "UnlitMaterial.hpp"

#include "SkyboxRenderer.hpp"
#include "SkyboxMaterial.hpp"

#include <GLFW/glfw3.h>
#include "GLFW_Windows.hpp"

// initialize static member
TinySandbox::Scene* TinySandbox::Scene::m_instance = nullptr;

namespace TinySandbox
{
	// ctor, Setup Scene
	Scene::Scene()
	{
		m_mainCamera = new Camera();
		m_SkyboxRenderer = nullptr;
	}

	Scene::~Scene()
	{
		delete m_mainCamera;
		delete m_SkyboxRenderer;
		if (Scene::Instance() != nullptr) {
			for (auto entity : Scene::Instance()->m_entitiesList)
			{
				delete entity;
			}
		}
	}

	void Scene::InitSceneSettings()
	{
		/***** Setup Graphics Setting *****/
		GraphicsAPI* API = GraphicsAPI::GetAPI();
		API->EnableDepthTest();
		
		/***** Setup Scene Entity & Setting *****/		
		TinySandbox::Entity* testEntity = new TinySandbox::Entity("Test");
		TinySandbox::MeshRenderer* meshRenderer = new TinySandbox::MeshRenderer();
		TinySandbox::Mesh* mesh = new TinySandbox::Mesh("../Resources/monkey.obj");
		Transform* testTransform = testEntity->GetTransform();

		testEntity->Add(meshRenderer); // implicitly cast to TinySandbox::Component
		meshRenderer->SetMesh(mesh);
		meshRenderer->SetMaterial(new UnlitMaterial(meshRenderer, "../Resources/test.png"));
		meshRenderer->SetMaterial(new NormalDebugMaterial(meshRenderer));
		testTransform->Rotation(glm::vec3(-90.0f, 0.0f, 90.0f));

		Scene::Instance()->Add(testEntity);
		
		// Skybox Setting
		Texture* test = new Texture("../Resources/Newport_Loft_Ref.hdr", TextureType::TEXTURE_2D, true, true, true, 1024, 512, 512, 5);
		m_SkyboxRenderer = new SkyboxRenderer();
		m_SkyboxRenderer->SetTexture(test);

		// Main Camera Setting
		m_mainCamera->NearPlaneDistance(0.01f);
		m_mainCamera->FarPlaneDistance(100.0f);
		m_mainCamera->FieldOfView(45.0f);
		m_mainCamera->Position(glm::vec3(0, 0, 5));
		m_mainCamera->Phi(90.0f);
		m_mainCamera->Theta(0.0f);
	}


	void Scene::Start()
	{
		for (auto entity : Scene::Instance()->m_entitiesList) {
			entity->Start();
		}
	}

	void Scene::Update()
	{
		for (auto entity : Scene::Instance()->m_entitiesList) {
			entity->Update();
		}
	}

	void Scene::OnGUI()
	{
		for (auto entity : Scene::Instance()->m_entitiesList) {
			entity->OnGUI();
		}
	}

	void Scene::OnRender()
	{
		for (auto entity : Scene::Instance()->m_entitiesList) {
			entity->OnRender();
		}

		m_SkyboxRenderer->OnRender(); // render at last
	}

	void Scene::Add(Entity* _entity)
	{
		Scene::Instance()->m_entitiesList.push_back(_entity);
	}

	Scene* Scene::Instance()
	{
		if (Scene::m_instance == nullptr)
		{
			Scene::m_instance = new Scene();
		}
		return m_instance;
	}

	Camera* Scene::GetMainCamera()
	{
		return Scene::Instance()->m_mainCamera;
	}

	void Scene::ProcessInput(Windows* _window)
	{
		GLFWwindow* window = dynamic_cast<GLFW_Windows*>(_window)->GetGLFWInstance();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		TinySandbox::Camera* mainCamera = TinySandbox::Scene::GetMainCamera();

		const float sentivity = 0.1;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			mainCamera->Position(mainCamera->Position() + glm::vec3(0, 0, -1) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			mainCamera->Position(mainCamera->Position() + glm::vec3(0, 0, 1) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			mainCamera->Position(mainCamera->Position() + glm::vec3(-1, 0, 0) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			mainCamera->Position(mainCamera->Position() + glm::vec3(1, 0, 0) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			mainCamera->Position(mainCamera->Position() + glm::vec3(0, 1, 0) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			mainCamera->Position(mainCamera->Position() + glm::vec3(0, -1, 0) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
			mainCamera->Theta(mainCamera->Theta() + 1);
		}

		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
			mainCamera->Theta(mainCamera->Theta() - 1);
		}

		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			mainCamera->Phi(mainCamera->Phi() + 1);
		}

		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			mainCamera->Phi(mainCamera->Phi() - 1);
		}

		// debug
		if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
			m_SkyboxRenderer->SetDisplayMode(Skybox_DisplayType::REGULAR);
		}

		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
			m_SkyboxRenderer->SetDisplayMode(Skybox_DisplayType::IRRADIANCE);
		}
	}

	void Scene::ProcessReshape(Windows* _window, int _width, int _height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, _width, _height);

		TinySandbox::Windows::GetInstance()->SetWidthAndHeight(_width, _height);
	}
}
