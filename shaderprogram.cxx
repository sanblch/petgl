#include "shaderprogram.h"
#include <GL/glew.h>
#include <iostream>
#include <string>

static const GLuint shader_type[3]{GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER,
                                   GL_VERTEX_SHADER};
static const char *shader_str[3]{"FRAGMENT", "GEOMETRY", "VERTEX"};

std::tuple<GLint, GLuint> add_shader(ShaderType type, const char *shader) {
  GLuint handle = glCreateShader(shader_type[static_cast<unsigned int>(type)]);
  glShaderSource(handle, 1, &shader, NULL);
  glCompileShader(handle);
  GLint success;
  glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint length = 0;
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
    if (length > 1) {
      std::string log;
      log.resize(static_cast<std::string::size_type>(length));
      glGetShaderInfoLog(handle, length, nullptr, &log[0]);
      std::cout
          << "ERROR::SHADER_COMPILATION_ERROR of type: "
          << shader_str[static_cast<unsigned int>(type)] << "\n"
          << log
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  }
  return std::tie(success, handle);
}


ShaderProgram::ShaderProgram(
    const std::vector<std::pair<ShaderType, const char *>> &shaders) {
  GLuint handle = glCreateProgram();
  m_id = static_cast<unsigned int>(handle);
  std::vector<GLuint> shader_handles;
  for (const auto &[type, shader] : shaders) {
    auto [ok, shader_handle] = add_shader(type, shader);
    if (ok) {
      glAttachShader(handle, shader_handle);
      shader_handles.push_back(shader_handle);
    }
  }
  glLinkProgram(handle);
  GLint success;
  glGetProgramiv(handle, GL_LINK_STATUS, &success);
  if (!success) {
    GLint length = 0;
    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
    if (length > 1) {
      std::string log;
      log.resize(static_cast<std::string::size_type>(length));
      glGetProgramInfoLog(handle, length, nullptr, &log[0]);
      std::cout
          << "ERROR::PROGRAM_LINKING_ERROR: \n"
          << log
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  }
  for (const auto &handle : shader_handles) {
    glDeleteShader(handle);
  }
}

void ShaderProgram::use() { glUseProgram(m_id); }

void ShaderProgram::setVal(const std::string &name, int val) {
  glUniform1i(glGetUniformLocation(static_cast<GLuint>(m_id), name.c_str()),
              val);
}

void ShaderProgram::setVal(const std::string &name, float val) {
  glUniform1f(glGetUniformLocation(static_cast<GLuint>(m_id), name.c_str()),
              val);
}

void ShaderProgram::setVal(const std::string &name, double val) {
 glUniform1d(glGetUniformLocation(static_cast<GLuint>(m_id), name.c_str()),
              val);
}
