#ifndef ISAAC_CAMERA_HPP
#define ISAAC_CAMERA_HPP

#include <Eigen/Dense>

using Eigen::Vector3d;
using Eigen::Matrix4d;

namespace Isaac {
  class Camera {
  public:
    enum Camera_Movement {
      FORWARD,
      BACKWARD,
      LEFT,
      RIGHT
    };

    Vector3d position, up, front, right, worldUp;

    explicit Camera(const Vector3d &position_ = {0, 0, 0}, const Vector3d &up_ = {0, 1, 0}, const double &yaw_ = -90,
                    const double &pitch_ = 0) noexcept;

    Matrix4d getViewMatrix() const noexcept;

    void processKeyboard(const Camera_Movement &direction, const double &deltaTime) noexcept;

    void processMouseMovement(double xoffset, double yoffset, const bool &constrainPitch = true) noexcept;

  private:
    void updateCameraVectors() noexcept;

    double yaw, pitch, movementSpeed, mouseSensitivity, zoom;
  };
} // namespace Isaac

#endif // ISAAC_CAMERA_HPP
