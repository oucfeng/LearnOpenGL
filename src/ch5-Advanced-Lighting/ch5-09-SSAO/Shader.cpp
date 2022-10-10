#include "Shader.h"

//����ƬԪ��ɫ��
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ��֤ifstream��������׳��쳣��
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // ���ļ�
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // ��ȡ�ļ��Ļ������ݵ���������
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // �ر��ļ�������
        vShaderFile.close();
        fShaderFile.close();
        // ת����������string
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


    // 2. ������ɫ��
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // ������ɫ��
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // ��ӡ�����������еĻ���
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // Ƭ����ɫ��Ҳ����
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // ��ӡ�����������еĻ���
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // ��ɫ������
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // ��ӡ���Ӵ�������еĻ���
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

//������ɫ��
void Shader::load_geometry_shader(const char* shaderPath)
{
    std::cout << "init geometry shader: " << shaderPath << std::endl;
    // 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��
    std::string shaderCode;
    std::ifstream shaderFile;
    // ��֤ifstream��������׳��쳣��
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // ���ļ�
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        // ��ȡ�ļ��Ļ������ݵ���������
        shaderStream << shaderFile.rdbuf();
        // �ر��ļ�������
        shaderFile.close();
        // ת����������string
        shaderCode = shaderStream.str();

        //std::cout <<"vertexCode: \n" << vertexCode << std::endl;
        //std::cout <<"fragmentCode: \n" << fragmentCode << std::endl;
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }
    const char* code = shaderCode.c_str();

    // 2. ������ɫ��
    unsigned int geometryShader;
    int success;
    char infoLog[512];

    // ������ɫ��
    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &code, NULL);
    glCompileShader(geometryShader);
    // ��ӡ�����������еĻ���
    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
        std::cout << "ERROR::GEOMETRY_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // ��ɫ������
    glAttachShader(ID, geometryShader);
    glLinkProgram(ID);
    // ��ӡ���Ӵ�������еĻ���
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::GEOMETRY_SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
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

void Shader::set_uniform(std::string name, glm::mat4& mat4) const noexcept
{
    set_uniform(name, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::set_uniform(std::string name, int count, bool transpose, const float* value) const noexcept
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), count, transpose, value);
}

void Shader::clear()
{
    glDeleteProgram(ID);
}