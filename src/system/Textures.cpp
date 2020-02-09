#include <vector>
#include "Textures.h"


namespace Assets
{
	namespace Textures
	{
		Texture *defaultT = nullptr;
		std::vector<Texture*> textures;
		
		void init()
		{
			defaultT = new Texture("res/textures/default.png");
			textures.push_back(defaultT);
		}
		
		void destroy()
		{
			for (Texture *ptr : textures)
				delete ptr;
		}
		
		
		Texture *load(const std::string &filepath)
		{
			Texture *tex = new Texture(filepath);
			textures.push_back(tex);
			return tex;
		}
	}
}