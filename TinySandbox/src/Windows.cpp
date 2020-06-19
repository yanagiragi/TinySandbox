#include "Windows.hpp"

#include "Scene.hpp"

TinySandbox::Windows* TinySandbox::Windows::m_instance = nullptr;

namespace TinySandbox {

	Windows::Windows(const char* _title, int _width, int _height) : m_name(_title), m_width(_width), m_height(_height)
	{
		m_mainScene = nullptr;
	}

	/*Windows::Windows(int width, int height, Scene&& _mainLoop)
	{
		// mainScene = new Scene(_mainLoop);
	}*/

	Windows::~Windows()
	{
		delete m_mainScene;
	}

	void Windows::SetScene(Scene* _scene)
	{
		m_mainScene = _scene;
	}

	Windows* Windows::GetInstance() {
		if (Windows::m_instance == nullptr) {
			throw "Should SetInstance() Before GetInstance()!";
		}
		return Windows::m_instance;
	}

	void Windows::SetInstance(Windows* _instance)
	{
		if (Windows::m_instance) {
			delete Windows::m_instance;
		}
		Windows::m_instance = _instance;
	}

	void Windows::SetWidthAndHeight(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;
	}
}