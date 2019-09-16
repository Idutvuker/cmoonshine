#include "ModelLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"


void ModelLoader::load(const std::string &path, Node *to, std::shared_ptr<BaseMaterial> material)
{
	bool normals = true;
	bool texcoords = false;
	
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	
	std::string warning;
	std::string error;
	
	tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, path.c_str());
	
	if (!warning.empty())
		Log::d(warning);
	
	if (!error.empty())
		Log::d(error);
	
	for (auto & shape : shapes)
	{
		size_t vertNum = shape.mesh.num_face_vertices.size() * 3;
		std::vector<float> vertices = std::vector<float>(vertNum * (3 + 3 * normals + 2 * texcoords));
		size_t p = 0;
		
		size_t index_offset = 0;
		
		for (size_t face = 0; face < shape.mesh.num_face_vertices.size(); face++)
		{
			int fv = shape.mesh.num_face_vertices[face];
			
			assert(fv == 3 && "Mesh should contain only triangles");
			
			for (size_t v = 0; v < fv; v++)
			{
				tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
				
				int id = idx.vertex_index;
				tinyobj::real_t vx = attrib.vertices[3*id+0];
				tinyobj::real_t vy = attrib.vertices[3*id+1];
				tinyobj::real_t vz = attrib.vertices[3*id+2];
				
				vertices[p++] = vx;
				vertices[p++] = vy;
				vertices[p++] = vz;
				
				
				if (normals)
				{
					id = idx.normal_index;
					if (id == -1)
					{
						p += 3;
						//Log::d(shape.name, "Face normals are missing");
					}
					
					else {
						tinyobj::real_t nx = attrib.normals[3 * id + 0];
						tinyobj::real_t ny = attrib.normals[3 * id + 1];
						tinyobj::real_t nz = attrib.normals[3 * id + 2];
						
						vertices[p++] = nx;
						vertices[p++] = ny;
						vertices[p++] = nz;
						//Log::d(nx * nx + ny * ny + nz * nz);
					}
				}
				
				if (texcoords)
				{
					id = idx.texcoord_index;
					if (id == -1)
					{
						p += 2;
						//Log::d(shape.name, "Face tex coords are missing");
					}
					
					else {
						tinyobj::real_t u = attrib.normals[2 * id + 0];
						tinyobj::real_t v = attrib.normals[2 * id + 1];
						
						vertices[p++] = u;
						vertices[p++] = v;
					}
				}
				
				
				
			}
			
			index_offset += fv;
		}
		
		Mesh * mesh = new Mesh(vertices, material);
		mesh->name = shape.name;
		to->addChild(mesh);
	}
}
