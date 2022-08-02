#include "Shader.h"

//顶点片元着色器
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. 从文件路径中获取顶点/片段着色器
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        //std::cout <<"vertexCode: \n" << vertexCode << std::endl;
        //std::cout <<"fragmentCode: \n" << fragmentCode << std::endl;
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();


    // 2. 编译着色器
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // 顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // 打印编译错误（如果有的话）
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // 片段着色器也类似
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // 打印编译错误（如果有的话）
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // 着色器程序
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // 打印连接错误（如果有的话）
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

//几何作色器
void Shader::load_geometry_shader(const char* shaderPath)
{
    std::cout << "init geometry shader: " << shaderPath << std::endl;
    // 1. 从文件路径中获取顶点/片段着色器
    std::string shaderCode;
    std::ifstream shaderFile;
    // 保证ifstream对象可以抛出异常：
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // 打开文件
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        // 读取文件的缓冲内容到数据流中
        shaderStream << shaderFile.rdbuf();
        // 关闭文件处理器
        shaderFile.close();
        // 转换数据流到string
        shaderCode = shaderStream.str();

        //std::cout <<"vertexCode: \n" << vertexCode << std::endl;
        //std::cout <<"fragmentCode: \n" << fragmentCode << std::endl;
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }
    const char* code = shaderCode.c_str();

    // 2. 编译着色器
    unsigned int geometryShader;
    int success;
    char infoLog[512];

    // 顶点着色器
    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &code, NULL);
    glCompileShader(geometryShader);
    // 打印编译错误（如果有的话）
    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
        std::cout << "ERROR::GEOMETRY_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // 着色器程序
    glAttachShader(ID, geometryShader);
    glLinkProgram(ID);
    // 打印连接错误（如果有的话）
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::GEOMETRY_SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(geometryShader);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::set_uniform(std::string name, bool value) const noexcept
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), int(value));
}

void Shader::set_uniform(std::string name, int value) const noexcept
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_uniform(std::string name, float value) const noexcept
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_uniform(std::string name, float value1, float value2, float value3, float value4) const noexcept
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}

void Shader::set_uniform(std::string name, float value1, float value2, float value3) const noexcept
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}

void Shader::set_uniform(std::string name, glm::vec2 vec2) const noexcept
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), vec2.x, vec2.y);
}

void Shader::set_uniform(std::string name, glm::vec3 vec3) const noexcept
{
    set_uniform(name, vec3.x, vec3.y, vec3.z);
}

void Shader::set_uniform(std::string name, glm::vec4 vec4) const noexcept
{
    set_uniform(name, vec4.x, vec4.y, vec4.z, vec4.w);
}

void Shader::set_uniform(std::string name, int count, bool transpose, const float* value) const noexcept
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), count, transpose, value);
}

void Shader::clear()
{
    glDeleteProgram(ID);
}
