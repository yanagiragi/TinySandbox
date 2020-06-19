#pragma once

// Forward Declaration
namespace TinySandbox {
	class Scene;
}

namespace TinySandbox {

    class Windows 
    {
        public:

			Windows(const char* _title, int _width, int _height);

			~Windows();

			void SetScene(Scene* _scene);
			
			virtual bool ShouldClose() = 0;
			virtual void Loop() = 0;

			int GetWidth() const { return m_width; }
			int GetHeight() const { return m_height; }

			static Windows* GetInstance();

			static void SetInstance(Windows*);

			void SetWidthAndHeight(int _width, int _height);

		protected:
			Scene* m_mainScene;
			static Windows *m_instance;
			int m_width, m_height;
			const char* m_name;
    };
}