#include "Scene.hpp"

#include "TestComponent.hpp"

namespace TinySandbox
{
	// ctor, Setup Scene
	Scene::Scene()
	{
		TinySandbox::Component* testComponent = new TinySandbox::TestComponent();

		TinySandbox::Entity* testEntity = new TinySandbox::Entity();
		testEntity->Add(testComponent);

		Add(testEntity);
	}
}
