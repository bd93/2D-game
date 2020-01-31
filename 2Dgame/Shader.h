#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>

#include <string>


class Shader
{
private:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
public:
	Shader(std::string vertexShaderFile, std::string fragmentShaderFile)
	{
		std::string vertexShaderString = getShaderSource(vertexShaderFile);
		std::string fragmentShaderString = getShaderSource(fragmentShaderFile);
		
		const char* vertexShaderSource   = vertexShaderString.c_str();
		const char* fragmentShaderSource = fragmentShaderString.c_str();

		vertexShader   = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertexShader,   1, &vertexShaderSource,   NULL);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);

		checkCompileError(vertexShader,   "VERTEX");
		checkCompileError(fragmentShader, "FRAGMENT");

		shaderProgram = glCreateProgram();


		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram (shaderProgram);

		checkLinkError();

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	Shader()
	{
	}
	~Shader()
	{
	}
	GLuint getShaderProgram()
	{
		return shaderProgram;
	}
	std::string getShaderSource(std::string filePath)
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
	}
	void setFloat(const GLchar* name, GLfloat value, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform1f(glGetUniformLocation(this->shaderProgram, name), value);
	}
	void setInteger(const GLchar* name, GLint value, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform1i(glGetUniformLocation(this->shaderProgram, name), value);
	}
	void setVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform2f(glGetUniformLocation(this->shaderProgram, name), value.x, value.y);
	}
	void setVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform3f(glGetUniformLocation(this->shaderProgram, name), value.x, value.y, value.z);
	}
	void setVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniform4f(glGetUniformLocation(this->shaderProgram, name), value.x, value.y, value.z, value.w);
	}
	void setMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader)
	{
		if (useShader)
			this->use();
		glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void checkCompileError(GLuint shader, std::string type)
	{
		int  success;
		char infoLog[512];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << "/n";
		}
	}
	void checkLinkError()
	{
		int  success;
		char infoLog[512];

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "/n";
		}
	}
	void use()
	{
		glUseProgram(shaderProgram);
	}
};


#endif