#pragma once

#include <iostream>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	/*Shader() = delete;
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;*/
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	void set_uniform(std::string name, bool value) const noexcept;
	void set_uniform(std::string name, int value) const noexcept;
	void set_uniform(std::string name, float value) const noexcept;
	void set_uniform(std::string name, float value1, float value2, float value3, float value4) const noexcept;
	void set_uniform(std::string name, float value1, float value2, float value3) const noexcept;
	void set_uniform(std::string name, int count, bool transpose, const float* value) const noexcept;

	void clear();
private:
	unsigned int ID;
};
