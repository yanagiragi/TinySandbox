#include "Scene.hpp"

#include "MeshRenderer.hpp"
#include "Quad.hpp"
#include "Cube.hpp"
#include "DirectionalLight.hpp"

#include "NormalDebugMaterial.hpp"
#include "UnlitMaterial.hpp"
#include "CookTorranceMaterial.hpp"

#include "SkyboxRenderer.hpp"
#include "SkyboxMaterial.hpp"

#include "RotateAxis.hpp"

#include <GLFW/glfw3.h>
#include "GLFW_Windows.hpp"

#include <type_traits>
#include <string>

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

		float shift = 14;

		// 1. Outer part of FOL
		TinySandbox::Entity* outerEntity = new TinySandbox::Entity("Test (Outer)");
		TinySandbox::MeshRenderer* outerMeshRenderer = new TinySandbox::MeshRenderer();
		TinySandbox::Mesh* outerMesh = new TinySandbox::Mesh("../Resources/outer.obj");
		Transform* outerTransform = outerEntity->GetTransform();

		outerEntity->Add(outerMeshRenderer); // implicitly cast to TinySandbox::Component
		outerMeshRenderer->SetMesh(outerMesh);
		
		CookTorranceMaterial* outerMaterial = new CookTorranceMaterial();
		outerMaterial->SetMetallic(1.0);
		outerMaterial->SetRoughness(0.2);
		outerMaterial->SetTint(glm::vec3(1, 112, 44) / 255.0f);
		outerMeshRenderer->SetMaterial(outerMaterial);
		outerTransform->Rotation(glm::vec3(-90.0f, 0.0f, 90.0f));
		outerTransform->Position(glm::vec3(shift + 0, 0, 0));
		
		Scene::Instance()->Add(outerEntity);

		// 2. Inner part of FOL
		TinySandbox::Entity* innerEntity = new TinySandbox::Entity("Test (Inner)");
		TinySandbox::MeshRenderer* innerMeshRenderer = new TinySandbox::MeshRenderer();
		TinySandbox::Mesh* innerMesh = new TinySandbox::Mesh("../Resources/inner.obj");
		Transform* innerTransform = innerEntity->GetTransform();

		innerEntity->Add(innerMeshRenderer); // implicitly cast to TinySandbox::Component
		innerMeshRenderer->SetMesh(innerMesh);
		
		CookTorranceMaterial* innerMaterial = new CookTorranceMaterial();
		innerMaterial->SetMetallic(1.0);
		innerMaterial->SetRoughness(0.8);
		innerMaterial->SetTint(glm::vec3(0.38, 0, 0));

		innerMeshRenderer->SetMaterial(innerMaterial);
		innerTransform->Rotation(glm::vec3(-90.0f, 0.0f, 90.0f));
		innerTransform->Position(glm::vec3(shift + 0, 0, 0));

		Scene::Instance()->Add(innerEntity);

		// 3. Suzanne Monkey
		TinySandbox::Entity* monkeyEntity = new TinySandbox::Entity("Suzanne");
		TinySandbox::MeshRenderer* monkeyMeshRenderer = new TinySandbox::MeshRenderer();
		Transform* monkeyTransform = monkeyEntity->GetTransform();

		monkeyEntity->Add(monkeyMeshRenderer); // implicitly cast to TinySandbox::Component
		monkeyMeshRenderer->SetMesh(new Mesh("../Resources/monkey.obj"));
		monkeyMeshRenderer->SetMaterial(new NormalDebugMaterial());
		monkeyTransform->Rotation(glm::vec3(-90.0f, 0.0f, 90.0f));
		monkeyTransform->Position(glm::vec3(shift -3, 0, 0));

		Scene::Instance()->Add(monkeyEntity);

		// 4. Draw Quad with logo
		TinySandbox::Entity* quadEntity = new TinySandbox::Entity("Quad");
		TinySandbox::MeshRenderer* quadMeshRenderer = new TinySandbox::MeshRenderer();
		Transform* quadTransform = quadEntity->GetTransform();

		quadEntity->Add(quadMeshRenderer); // implicitly cast to TinySandbox::Component
		quadMeshRenderer->SetMesh(new Quad());
		quadMeshRenderer->SetMaterial(new UnlitMaterial("../Resources/logo.jpg", false));
		quadTransform->Rotation(glm::vec3(0.0f, 0.0f, 90.0f));
		quadTransform->Position(glm::vec3(shift + 3, 0, 0));

		Scene::Instance()->Add(quadEntity);

		// 5. Add Light to scene
		TinySandbox::Entity* sunEntity = new TinySandbox::Entity("Sun");
		DirectionalLight* sunLight = new DirectionalLight(3.0, glm::vec3(1, 1, 1));
		sunEntity->Add(sunLight);
		sunEntity->Add(new RotateAxis());

		Scene::Instance()->Add(sunEntity);

		// 6. Add Spheres
		
		const int row = 5, col = 5, sphereSpacing = 3.0;
		auto clamp = [](float x, float min, float max) -> float {
			return x < min ? min : x > max ? max : x;
		};

		TinySandbox::Mesh* sphereMesh = new TinySandbox::Mesh("../Resources/sphere.obj");
		for (int i = 0; i < col; ++i) {
			for (int j = 0; j < row; ++j) {
				
				TinySandbox::Entity* sphereEntity = new TinySandbox::Entity("Test (" + std::to_string(i) + "_" + std::to_string(j) + ")");
				TinySandbox::MeshRenderer* sphereMeshRenderer = new TinySandbox::MeshRenderer();
				Transform* sphereTransform = sphereEntity->GetTransform();
				CookTorranceMaterial* sphereMaterial = new CookTorranceMaterial();

				sphereMaterial->SetMetallic((float)i / (float)row);
				sphereMaterial->SetRoughness(clamp((float)j / (float)col, 0.05f, 1.0f));
				sphereMaterial->SetAmbientOcculusion(1.0f);
				
				sphereEntity->Add(sphereMeshRenderer); // implicitly cast to TinySandbox::Component
				sphereMeshRenderer->SetMesh(sphereMesh);
				
				sphereMeshRenderer->SetMaterial(sphereMaterial);
				sphereTransform->Rotation(glm::vec3(-90.0f, 0.0f, 90.0f));
				sphereTransform->Position(glm::vec3(
					(float)((col / 2) - j) * sphereSpacing,
					(float)((col / 2) - i) * sphereSpacing, -2.0));

				Scene::Instance()->Add(sphereEntity);
			}
		}
		
		// Skybox Setting
		Texture* test = new Texture("../Resources/Newport_Loft_Ref.hdr", TextureType::TEXTURE_2D, true, true, true, 1024, 512, 512, 5);
		m_SkyboxRenderer = new SkyboxRenderer();
		m_SkyboxRenderer->SetTexture(test);

		// Main Camera Setting
		m_mainCamera->NearPlaneDistance(0.01f);
		m_mainCamera->FarPlaneDistance(100.0f);
		m_mainCamera->FieldOfView(45.0f);
		// m_mainCamera->Position(glm::vec3(0, 0, 10));
		// m_mainCamera->Position(glm::vec3(0, 0, 4.899));
		m_mainCamera->Position(glm::vec3(20.6, 0, 15.69));
		m_mainCamera->Phi(123.0f);
		m_mainCamera->Theta(0.0f);

		// ViewPort Setting
		Windows* window = Windows::GetInstance();
		API->SetViewport(0, 0, window->GetWidth(), window->GetHeight());
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

		// update LightList
		auto components = _entity->GetComponents();
		for (Component* component : components) {
			BaseLight* derived = dynamic_cast<BaseLight*>(component);
			if (derived) {
				Scene::Instance()->m_lightList.push_back(derived);
			}
		}
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

	SkyboxMaterial* Scene::GetSkybox()
	{
		return dynamic_cast<SkyboxMaterial*>( Scene::Instance()->m_SkyboxRenderer->GetMaterial() );
	}

	std::vector<BaseLight*>& Scene::GetLightList()
	{
		return Scene::Instance()->m_lightList;
	}

	void Scene::ProcessInput(Windows* _window)
	{
		GLFWwindow* window = dynamic_cast<GLFW_Windows*>(_window)->GetGLFWInstance();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		// Should Set Input State and let Component Reacts to it

		// For Debug, Direct Manipulate the Entity for now

		TinySandbox::Camera* mainCamera = TinySandbox::Scene::GetMainCamera();

		float sentivity = 0.1;

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
		
		if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS) {
			m_SkyboxRenderer->SetDisplayMode(Skybox_DisplayType::PREFILTER);
		}

		if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
			m_SkyboxRenderer->SetLod(m_SkyboxRenderer->GetLod() + 0.1);
		}

		if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
			m_SkyboxRenderer->SetLod(m_SkyboxRenderer->GetLod() - 0.1);
		}

		/*sentivity = 10;

		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
			const glm::vec3 pos = m_entitiesList[2]->GetTransform()->Position();
			m_entitiesList[2]->GetTransform()->Position(pos + glm::vec3(1, 0, 0) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
			const glm::vec3 pos = m_entitiesList[2]->GetTransform()->Position();
			m_entitiesList[2]->GetTransform()->Position(pos + glm::vec3(-1, 0, 0) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
			const glm::vec3 pos = m_entitiesList[3]->GetTransform()->Rotation();
			m_entitiesList[3]->GetTransform()->Rotation(pos + glm::vec3(1, 0, 0) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
			const glm::vec3 pos = m_entitiesList[3]->GetTransform()->Rotation();
			m_entitiesList[3]->GetTransform()->Rotation(pos + glm::vec3(-1, 0, 0) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
			const glm::vec3 pos = m_entitiesList[3]->GetTransform()->Rotation();
			m_entitiesList[3]->GetTransform()->Rotation(pos + glm::vec3(0, 1, 0) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
			const glm::vec3 pos = m_entitiesList[3]->GetTransform()->Rotation();
			m_entitiesList[3]->GetTransform()->Rotation(pos + glm::vec3(0, -1, 0) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
			const glm::vec3 pos = m_entitiesList[3]->GetTransform()->Rotation();
			m_entitiesList[3]->GetTransform()->Rotation(pos + glm::vec3(0, 0, 1) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
			const glm::vec3 pos = m_entitiesList[3]->GetTransform()->Rotation();
			m_entitiesList[3]->GetTransform()->Rotation(pos + glm::vec3(0, 0, -1) * sentivity);
		}

		if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS) {
			
			Entity* innerEntity = m_entitiesList[1];
			auto components = innerEntity->GetComponents();

			for (auto component : components)
			{
				MeshRenderer* renderer = dynamic_cast<MeshRenderer*>(component);
				if (renderer) {
					const glm::vec2 offset = renderer->GetMaterial()->GetOffset();
					renderer->GetMaterial()->SetOffset(offset + glm::vec2(0, 1) * -0.01f);

					break;
				}
			}
		}

		if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS) {
			Entity* innerEntity = m_entitiesList[1];
			auto components = innerEntity->GetComponents();

			for (auto component : components)
			{
				MeshRenderer* renderer = dynamic_cast<MeshRenderer*>(component);
				if (renderer) {
					const glm::vec2 offset = renderer->GetMaterial()->GetOffset();
					renderer->GetMaterial()->SetOffset(offset + glm::vec2(0, 1) * 0.01f);

					break;
				}
			}
		}*/
	}

	void Scene::ProcessReshape(Windows* _window, int _width, int _height)
	{
		// special take care when window is mimimized
		const int width = _width == 0 ? 1 : _width;
		const int height = _height == 0 ? 1 : _height;

		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		const GraphicsAPI* m_api = GraphicsAPI::GetAPI();
		m_api->SetViewport(0, 0, width, height);

		TinySandbox::Windows::GetInstance()->SetWidthAndHeight(width, height);
	}
}
