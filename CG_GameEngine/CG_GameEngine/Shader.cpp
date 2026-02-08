#include "pch.h"
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;

	{
		std::ifstream vShaderFile(vertexPath, std::ios::in | std::ios::binary);
		if (!vShaderFile) {
			std::cerr << "ERROR::SHADER::FILE_NOT_FOUND: " << vertexPath << std::endl;
			id = 0;
			return;
		}
		std::ostringstream ss;
		ss << vShaderFile.rdbuf();
		vertexCode = ss.str();
		//std::cout << "Loaded vertex shader '" << vertexPath << "' (" << vertexCode.size() << " bytes)" << std::endl;
	}

	{
		std::ifstream fShaderFile(fragmentPath, std::ios::in | std::ios::binary);
		if (!fShaderFile) {
			std::cerr << "ERROR::SHADER::FILE_NOT_FOUND: " << fragmentPath << std::endl;
			id = 0;
			return;
		}
		std::ostringstream ss;
		ss << fShaderFile.rdbuf();
		fragmentCode = ss.str();
		//std::cout << "Loaded fragment shader '" << fragmentPath << "' (" << fragmentCode.size() << " bytes)" << std::endl;
	}

	if (vertexCode.empty()) {
		std::cerr << "ERROR::SHADER::EMPTY_VERTEX_SOURCE: " << vertexPath << std::endl;
		id = 0;
		return;
	}
	if (fragmentCode.empty()) {
		std::cerr << "ERROR::SHADER::EMPTY_FRAGMENT_SOURCE: " << fragmentPath << std::endl;
		id = 0;
		return;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//std::cout << "Compiling shaders..." << std::endl;

	GLuint vertex = compileShader(GL_VERTEX_SHADER, vShaderCode);
	GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fShaderCode);

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	checkCompileErrors(id, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	//std::cout << "Shader program linked (id = " << id << ")" << std::endl;
}



Shader::~Shader()
{
	if (id != 0) {
		glDeleteProgram(id);
	}
}

void Shader::setVertexAttribPointer(const char* param, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) const
{
	GLint posAttrib = glGetAttribLocation(id, param);
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, size, type, normalized, stride, pointer);
}

void Shader::use() const
{
	if (id != 0)
		glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set3Float(const std::string& name, float v0, float v1, float v2) const {
	glUniform3f(glGetUniformLocation(id, name.c_str()), v0, v1, v2);
}

void Shader::set4Float(const std::string& name, float v0, float v1, float v2, float v3) const {
	glUniform4f(glGetUniformLocation(id, name.c_str()), v0, v1, v2, v3);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);

}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

GLuint Shader::compileShader(GLenum type, const char* source)
{
	const char* typeStr = (type == GL_VERTEX_SHADER) ? "VERTEX" :
		(type == GL_FRAGMENT_SHADER) ? "FRAGMENT" : "SHADER";

	//std::cout << "Compiling " << typeStr << " shader..." << std::endl;

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	checkCompileErrors(shader, typeStr);

	return shader;
}

void Shader::checkCompileErrors(GLuint shader, const std::string& type) const
{
	GLint success = 0;
	GLchar infoLog[1024] = { 0 };

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
		else {
			//std::cout << type << " shader compiled successfully." << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << std::endl;
		}
		else {
			//std::cout << "Program linked successfully." << std::endl;
		}
	}
}