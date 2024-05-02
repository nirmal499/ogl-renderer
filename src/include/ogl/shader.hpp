#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
  public:
    bool load_shaders(std::string vertexShaderFileName, std::string fragmentShaderFileName);
    void use();
    void clean_up();

  private:
    GLuint m_shader_program = 0;

    bool create_shader_program(std::string vertexShaderFileName, std::string fragmentShaderFileName);
    GLuint load_shader(std::string shaderFileName, GLuint shaderType);
    std::string load_file_to_string(std::string filename);
    bool check_compile_stats(std::string shaderFileName, GLuint shader);
    bool check_link_stats(std::string vertexShaderFileName, std::string fragmentShaderFileName, GLuint shaderProgram);
};
