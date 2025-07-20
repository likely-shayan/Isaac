#ifndef ISAAC_CAMERA_HPP
#define ISAAC_CAMERA_HPP

#include <Eigen/Dense>

using Eigen::Vector3d;
using Eigen::Matrix4d;

namespace Isaac {

  class Camera {
  public:

    Vector3d position, front, up, right, worldUp;
    double yaw, pitch, movementSpeed, mouseSensitivity, zoom;

    explicit Camera(const Vector3d& position_ = {0, 0, 0}, const Vector3d& up_ = {0, 1, 0}, const double& yaw_ = -90, const double& pitch_ = 0) noexcept;

    Matrix4d getViewMatrix() const noexcept;

  private:
    void updateCameraVectors() noexcept;
  };

} // namespace Isaac

#endif // ISAAC_CAMERA_HPP
