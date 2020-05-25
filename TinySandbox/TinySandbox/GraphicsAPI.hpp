#pragma once

namespace TinySandbox
{
    enum class GraphicsAPI_Type
    {
        OPENGL,
        OPENGL_ES,
        DIRECT_X,
        LEN
    };

    class GraphicsAPI
    {
        public:
            GraphicsAPI() {
                GraphicsAPI::type = GraphicsAPI_Type::LEN;
            };

            // virtual void Init();

            // define virtual functions
            // i.e., virtual void BindTextures(Texture, uint_32t);

            static GraphicsAPI_Type type;
    };

    class GraphicsAPI_OpenGL : public GraphicsAPI
    {
        public:
            GraphicsAPI_OpenGL() {
                GraphicsAPI::type = GraphicsAPI_Type::OPENGL;
            };

            /*void Init () override {
                
            }*/
    };
}
