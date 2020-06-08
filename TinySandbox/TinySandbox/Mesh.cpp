#include "Mesh.hpp"

#include <iostream>

namespace TinySandbox
{
	Mesh::Mesh()
	{

	}

	Mesh::Mesh(char* _filename) : filename(_filename)
	{
		std::string inputfile = "Resources/bunnyLow.obj";
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

		if (!warn.empty()) {
			std::cout << warn << std::endl;
		}

		if (!err.empty()) {
			std::cerr << err << std::endl;
		}

		if (!ret) {
			exit(1);
		}

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) { // Loop over faces(polygon)

			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

					tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
					tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
					tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
					vertex.push_back(glm::vec3(vx, vy, vz));

					tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
					tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
					tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
					normal.push_back(glm::vec3(nx, ny, nz));

					tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
					uv0.push_back(glm::vec2(tx, ty));

					// Optional: vertex colors
					// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
					// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
					// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
				}

				index_offset += fv;

				// per-face material
				// shapes[s].mesh.material_ids[f];
			}
		}
	}
	
	Mesh::Mesh(const Mesh &val)
	{
		filename = val.filename;
	}

	Mesh& Mesh::operator=(const Mesh &val)
	{
		return *this;
	}
	
	Mesh::~Mesh()
	{
		free(filename);
		vertex.clear();
		normal.clear();
		uv0.clear();
	}

}
