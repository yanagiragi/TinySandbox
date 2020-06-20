#include "GraphicsAPI.hpp"

using namespace TinySandbox;

GraphicsAPI* GraphicsAPI::m_api;
GraphicsAPI_Type GraphicsAPI::m_type;
int TinySandbox::GraphicsAPI::Max_Supported_Light = 4;
int TinySandbox::GraphicsAPI::Max_Supported_Lod = 4;