#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>

#include "../Shader.h"
#include "../Texture.h"

class ResourceManager
{
public:
	ResourceManager() = delete;
	static std::map<std::string, Shader> s_LoadedShaders;
	static std::map<std::string, Texture> s_LoadedTextures;
	static void AddLoadedShader(std::string name, const Shader& shader)
	{
		s_LoadedShaders[name] = shader;
	}
	static void AddLoadedTexture(std::string name, const Texture& texture)
	{
		s_LoadedTextures[name] = texture;
	}
	static Shader& GetLoadedShader(std::string name)
	{
		return s_LoadedShaders[name];
	}
	static Texture& GetLoadedTexture(std::string name)
	{
		return s_LoadedTextures[name];
	}
};

#endif
