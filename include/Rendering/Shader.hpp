#ifndef ISAAC_SHADER_HPP
#define ISAAC_SHADER_HPP

#include <string>

#include <Eigen/Dense>

using Eigen::Vector4d;

namespace Isaac {
  class Shader {
  public:
    Shader();

    Shader(const std::string &vertexShader, const std::string &fragmentShader);

    unsigned int GetID() const noexcept;

    void Use() const noexcept;

    void setBool(const std::string &name, const bool &value) const noexcept;

    void setInt(const std::string &name, const int &value) const noexcept;

    void setFloat(const std::string &name, const float &value) const noexcept;

    void setVector4(const std::string &name, const Vector4d &value) const noexcept;

  private:
    unsigned int ID;

    static void checkCompileErrors(const unsigned int &shader, const std::string &type);
  };
} // namespace Isaac

#endif // ISAAC_SHADER_HPP
