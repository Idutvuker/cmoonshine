#include "Materials.h"

namespace Assets
{
	namespace Materials
	{
		BaseMaterial *defaultM = nullptr;
		BaseMaterial *wireframe = nullptr;
		
		std::vector<BaseMaterial *> materials;
		
		
		void init()
		{
			BaseMaterial::Definition def;
			def.vertexShaderFilepath = "res/shaders/simple.vert";
			def.fragmentShaderFilepath = "res/shaders/simple.frag";
			defaultM = new BaseMaterial(def);
			
			def.vertexShaderFilepath = "res/shaders/wireframe.vert";
			def.fragmentShaderFilepath = "res/shaders/wireframe.frag";
			wireframe = new BaseMaterial(def);
		}
		
		void destroy()
		{
			for (BaseMaterial *ptr : materials)
				delete ptr;
		}
		
		BaseMaterial *load(const BaseMaterial::Definition &def) {
			auto *mat = new BaseMaterial(def);
			materials.push_back(mat);
			
			return mat;
		}
	}
}