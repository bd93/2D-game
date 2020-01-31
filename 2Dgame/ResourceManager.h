#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <fstream>
#include <sstream>
#include <map>

#include "Shader.h"

class ResourceManager
{
private:
	std::map<std::string, Shader> loadedShaders;
public:
	void addToMap(std::string name, Shader shader)
	{
		loadedShaders[name] = shader;
	}
	Shader getLoadedShader(std::string name)
	{
		return loadedShaders[name];
	}
	/*std::string getShaderSource(std::string filePath)
	{
		std::ifstream inFile;
		std::string str;

		try
		{
			inFile.open(filePath);
			std::stringstream strStream;
			strStream << inFile.rdbuf();
			inFile.close();
			str = strStream.str();
		}
		catch (std::ifstream::failure error)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ/n";
		}

		return str;
	}*/
};

#endif
