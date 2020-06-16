#pragma once

#include "GraphicsAPI.hpp"

namespace TinySandbox
{
	class GraphicsAPI_OpenGL : public GraphicsAPI
	{
	public:
		// bind "this" to GraphicsAPI::m_api
		// if multiple api instances exists, you should explicitly call SetAPI() instead.
		GraphicsAPI_OpenGL() : GraphicsAPI(this) {}

		int GetType(GraphicsAPI_DataType _type) override;
		
		void SetupVAO(unsigned int* _VAO, Mesh* _mesh, GraphicsAPI_DataType _type) override;

	private:
		void GenerateBuffers(unsigned int* _ids, int _length) override;
		void BindBuffer(GraphicsAPI_DataType _type, unsigned int _id) override;
		void UnbindBuffer(GraphicsAPI_DataType _type) override;
		void SetBuffers(GraphicsAPI_DataType _type, size_t _size, const void *_data, GraphicsAPI_DataType _additionalType) override;

		void GenerateVertexArrays(unsigned int* _ids, int _length) override;
		void BindVertexArray(unsigned int _id) override;
		void UnbindVertexArray() override;
		void EnableVertexArrayAttribute(unsigned int _VAOid) override;
		void DisableVertexArrayAttribute(unsigned int _VAOid) override;
		void SetVertexArray(unsigned int _VAOid, unsigned int _size, GraphicsAPI_DataType _type, GraphicsAPI_DataType _normalized, unsigned int _stride, const void* ptr) override;

	};
}
