#include <vector>
#include <iostream>
#include <fstream>
#include <cerrno>  // errno
#include <cstring> // strerror()

#include <ogl/shader.hpp>
#include <tool/logger.hpp>

bool Shader::load_shaders(std::string vertexShaderFileName, std::string fragmentShaderFileName)
{
  Logger::log(1, "%s: loading vertex shader '%s' and fragment shader '%s'\n", __FUNCTION__, vertexShaderFileName.c_str(), fragmentShaderFileName.c_str());

  if (!this->create_shader_program(vertexShaderFileName, fragmentShaderFileName))
  {
    Logger::log(1, "%s error: shader program creation failed\n", __FUNCTION__);
    return false;
  }

  return true;
}

void Shader::clean_up()
{
  glDeleteProgram(m_shader_program);
}

void Shader::use()
{
  glUseProgram(m_shader_program);
}

GLuint Shader::load_shader(std::string shaderFileName, GLuint shaderType)
{
  std::string shaderAsText;
  shaderAsText = this->load_file_to_string(shaderFileName);
  Logger::log(4, "%s: loaded shader file '%s', size %i\n", __FUNCTION__, shaderFileName.c_str(),shaderAsText.size());

  const char* shaderSource = shaderAsText.c_str();
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, (const GLchar**) &shaderSource, 0);
  glCompileShader(shader);

  if (!this->check_compile_stats(shaderFileName, shader))
  {
    Logger::log(1, "%s error: compiling shader '%s' failed\n", __FUNCTION__, shaderFileName.c_str());
    return 0;
  }

  Logger::log(1, "%s: shader %#x loaded and compiled\n", __FUNCTION__, shader);
  return shader;
}

bool Shader::create_shader_program(std::string vertexShaderFileName, std::string fragmentShaderFileName) {
  GLuint vertexShader = this->load_shader(vertexShaderFileName, GL_VERTEX_SHADER);
  if (!vertexShader)
  {
    Logger::log(1, "%s: loading of vertex shader '%s' failed\n", __FUNCTION__, vertexShaderFileName.c_str());
    return false;
  }

  GLuint fragmentShader = this->load_shader(fragmentShaderFileName, GL_FRAGMENT_SHADER);
  if (!fragmentShader)
  {
    Logger::log(1, "%s: loading of fragment shader '%s' failed\n", __FUNCTION__, fragmentShaderFileName.c_str());
    return false;
  }

  m_shader_program = glCreateProgram();

  glAttachShader(m_shader_program, vertexShader);
  glAttachShader(m_shader_program, fragmentShader);

  glLinkProgram(m_shader_program);

  if (!this->check_link_stats(vertexShaderFileName, fragmentShaderFileName, m_shader_program))
  {
    Logger::log(1, "%s error: program linking from vertex shader '%s' / fragment shader '%s' failed\n", __FUNCTION__, vertexShaderFileName.c_str(), fragmentShaderFileName.c_str());

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return false;
  }

  /* bind UBO in shader */
  GLint uboIndex = glGetUniformBlockIndex(m_shader_program, "Matrices");
  glUniformBlockBinding(m_shader_program, uboIndex, 0);

  /* it is safe to delete the shaders here */
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  Logger::log(1, "%s: shader program %#x successfully compiled from vertex shader '%s' and fragment shader '%s'\n", __FUNCTION__, m_shader_program, vertexShaderFileName.c_str(), fragmentShaderFileName.c_str());
  return true;
}

bool Shader::check_compile_stats(std::string shaderFileName, GLuint shader)
{
  GLint isShaderCompiled;
  int logMessageLength;
  std::vector<char> shaderLog;

  glGetShaderiv(shader, GL_COMPILE_STATUS, &isShaderCompiled);
  if (!isShaderCompiled)
  {
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logMessageLength);
    shaderLog = std::vector<char>(logMessageLength + 1);
    glGetShaderInfoLog(shader, logMessageLength, &logMessageLength, shaderLog.data());
    shaderLog.at(logMessageLength) = '\0';
    Logger::log(1, "%s error: shader compile of shader '%s' failed\n", __FUNCTION__, shaderFileName.c_str());
    Logger::log(1, "%s compile log:\n%s\n", __FUNCTION__, shaderLog.data());
    return false;
  }

  return true;
}

bool Shader::check_link_stats(std::string vertexShaderFileName, std::string fragmentShaderFileName, GLuint shaderProgram)
{
  GLint isProgramLinked;
  int logMessageLength;
  std::vector<char> programLog;

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isProgramLinked);
  if (!isProgramLinked)
  {
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logMessageLength);
    programLog = std::vector<char>(logMessageLength + 1);
    glGetProgramInfoLog(shaderProgram, logMessageLength, &logMessageLength, programLog.data());
    programLog.at(logMessageLength) = '\0';
    Logger::log(1, "%s error: program linking of shaders '%s' and '%s' failed\n", __FUNCTION__, vertexShaderFileName.c_str(), fragmentShaderFileName.c_str());
    Logger::log(1, "%s compile log:\n%s\n", __FUNCTION__, programLog.data());
    return false;
  }

  return true;
}

std::string Shader::load_file_to_string(std::string fileName)
{
  std::ifstream inFile(fileName);
  std::string str;

  if (inFile.is_open())
  {
    str.clear();
    // allocate string data (no slower realloc)
    inFile.seekg(0, std::ios::end);
    str.reserve(inFile.tellg());
    inFile.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(inFile)),
                std::istreambuf_iterator<char>());
    inFile.close();
  } 
  else
  {
    Logger::log(1, "%s error: could not open file %s\n", __FUNCTION__, fileName.c_str());
    Logger::log(1, "%s error: system says '%s'\n", __FUNCTION__, strerror(errno));
    return std::string();
  }

  if (inFile.bad() || inFile.fail()) {
    Logger::log(1, "%s error: error while reading file %s\n", __FUNCTION__, fileName.c_str());
    inFile.close();
    return std::string();
  }

  inFile.close();
  Logger::log(1, "%s: file %s successfully read to string\n", __FUNCTION__, fileName.c_str());
  return str;
}

