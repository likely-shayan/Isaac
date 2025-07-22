#include <Rendering/Camera.hpp>
#include <Kernel/Constants.hpp>
#include <cmath>

namespace Isaac {
  Camera::Camera(const Vector3d &position_, const Vector3d &up_, const double &yaw_,
                 const double &pitch_) noexcept : front({0, 0, -1}), movementSpeed(CAMERA_MOVEMENT_SPEED),
                                                  mouseSensitivity(MOUSE_SENSITIVITY), zoom(CAMERA_FOV) {
    position = position_;
    worldUp = up_;
    yaw = yaw_;
    pitch = pitch_;
    updateCameraVectors();
  }

  Matrix4d Camera::getViewMatrix() const noexcept {
    const Vector3d f = front.normalized();
    const Vector3d r = f.cross(worldUp).normalized();
    const Vector3d u = r.cross(f).normalized();

    Matrix4d viewMatrix = Matrix4d::Identity();

    viewMatrix(0, 0) = r.x();
    viewMatrix(0, 1) = r.y();
    viewMatrix(0, 2) = r.z();
    viewMatrix(1, 0) = u.x();
    viewMatrix(1, 1) = u.y();
    viewMatrix(1, 2) = u.z();
    viewMatrix(2, 0) = -f.x();
    viewMatrix(2, 1) = -f.y();
    viewMatrix(2, 2) = -f.z();
    viewMatrix(0, 3) = -r.dot(position);
    viewMatrix(1, 3) = -u.dot(position);
    viewMatrix(2, 3) = f.dot(position);
    viewMatrix(3, 0) = 0.0;
    viewMatrix(3, 1) = 0.0;
    viewMatrix(3, 2) = 0.0;
    viewMatrix(3, 3) = 1.0;

    return viewMatrix;
  }

  void Camera::processKeyboard(const Camera_Movement &direction, const double &deltaTime) noexcept {
    const double velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)
      position += front * velocity;
    if (direction == BACKWARD)
      position -= front * velocity;
    if (direction == LEFT)
      position -= right * velocity;
    if (direction == RIGHT)
      position += right * velocity;
  }

  void Camera::processMouseMovement(double xoffset, double yoffset, const bool &constrainPitch) noexcept {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
      if (pitch > 89.0)
        pitch = 89.0;
      if (pitch < -89.0)
        pitch = -89.0;
    }

    updateCameraVectors();
  }

  void Camera::updateCameraVectors() noexcept {
    Vector3d front_;
    front_.x() = cos(yaw * M_PI / 180.0) * cos(pitch * M_PI / 180.0);
    front_.y() = sin(pitch * M_PI / 180.0);
    front_.z() = sin(yaw * M_PI / 180.0) * cos(pitch * M_PI / 180.0f);
    front = front_.normalized();
    right = front.cross(worldUp).normalized();
    up = right.cross(front).normalized();
  }
} // namespace Isaac
