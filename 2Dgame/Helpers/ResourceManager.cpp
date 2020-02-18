#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::s_LoadedShaders;
std::map<std::string, Texture> ResourceManager::s_LoadedTextures;