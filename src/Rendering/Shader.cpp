#include <fstream>
#include <iostream>
#include <sstream>

#include <Eigen/Dense>
#include <glad/gl.h>

#include <Rendering/Shader.hpp>

using Eigen::Vector4f;
using Eigen::Matrix4f;
using Eigen::Vector4d;
using Eigen::Matrix4d;

namespace Isaac {
  Shader::Shader() = default;

  Shader::Shader(const std::string &vertexShader, const std::string &fragmentShader) {
    std::string vertexShaderCode, fragmentShaderCode;

    std::ifstream vertexShaderFile, fragmentShaderFile;

    vertexShaderFile.open(vertexShader);
    fragmentShaderFile.open(fragmentShader);

    std::stringstream vertexShaderStream, fragmentShaderStream;

    vertexShaderStream << vertexShaderFile.rdbuf();
    fragmentShaderStream << fragmentShaderFile.rdbuf();

    vertexShaderFile.close();
    fragmentShaderFile.close();

    vertexShaderCode = vertexShaderStream.str();
    fragmentShaderCode = fragmentShaderStream.str();

    unsigned int vertex, fragment;

    const char *vertexShaderCodeRaw = vertexShaderCode.c_str();
    const char *fragmentShaderCodeRaw = fragmentShaderCode.c_str();

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCodeRaw, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCodeRaw, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  unsigned int Shader::GetID() const noexcept {
    return ID;
  }

  void Shader::Use() const noexcept {
    glUseProgram(ID);
  }

  void Shader::setBool(const std::string &name, const bool &value) const noexcept {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
  }

  void Shader::setInt(const std::string &name, const int &value) const noexcept {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }

  void Shader::setFloat(const std::string &name, const float &value) const noexcept {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }

  void Shader::setVector4(const std::string &name, const Vector4d &value) const noexcept {
    Vector4f floatValue = value.cast<float>();
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, floatValue.data());
  }

  void Shader::setMatrix4(const std::string &name, const Matrix4d &value) const noexcept {
    Matrix4f floatValue = value.cast<float>();
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, floatValue.data());
  }


  void Shader::checkCompileErrors(const unsigned int &shader, const std::string &type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog <<
            "\n -- --------------------------------------------------- -- " << std::endl;
      }
    } else {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog <<
            "\n -- --------------------------------------------------- -- " << std::endl;
      }
    }
  }
} // namespace Isaac
