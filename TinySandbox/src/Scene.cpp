#include "Scene.hpp"

#include "MeshRenderer.hpp"

#include "NormalDebugMaterial.hpp"
#include "UnlitMaterial.hpp"

#include "SkyboxRenderer.hpp"
#include "SkyboxMaterial.hpp"

// initialize static member
TinySandbox::Scene* TinySandbox::Scene::m_instance = nullptr;

namespace TinySandbox
{
	// ctor, Setup Scene
	Scene::Scene()
	{
		m_mainCamera = new Camera();
		Texture* test = new Texture("../Resources/Newport_Loft_8k.jpg", TextureType::TEXTURE_2D, false, true, 512);
		m_SkyboxRenderer = new SkyboxRenderer();
		m_SkyboxRenderer->SetTexture(test);
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
		//meshRenderer->SetMaterial(new UnlitMaterial(meshRenderer, "../Resources/Newport_Loft_8k.jpg"));
		meshRenderer->SetMaterial(new NormalDebugMaterial(meshRenderer));
		testTransform->Rotation(glm::vec3(-90.0f, 0.0f, 90.0f));

		Scene::Instance()->Add(testEntity);
		
		// Skybox Setting
		// m_SkyboxRenderer->SetTexture();

		// Main Camera Setting
		m_mainCamera->Aspect(1.33f);
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
		// GraphicsAPI::GetAPI()->UnbindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER);

		// m_SkyboxRenderer->OnRender();

		for (auto entity : Scene::Instance()->m_entitiesList) {
			entity->OnRender();
		}

		m_SkyboxRenderer->OnRender();
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

	/*void Scene::ProcessInput(GLFWwindow *window)
	{
		//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		//	glfwSetWindowShouldClose(window, true);
	}

	void Scene::framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);

		// std::cout << window->name << std::endl;
	}*/
}
