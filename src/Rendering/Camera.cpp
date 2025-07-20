#include <Rendering/Camera.hpp>
#include <cmath>

namespace Isaac {

  Camera::Camera(const Vector3d &position_, const Vector3d &up_, const double &yaw_, const double &pitch_) noexcept {
    position = position_;
    up = up_;
    yaw = yaw_;
    pitch = pitch_;
    updateCameraVectors();
  }

  Matrix4d Camera::getViewMatrix() const noexcept {
    Matrix4d view;
    Vector3d center = position + front;
    Vector3d direction = (position - center).normalized();
    Vector3d right = worldUp.cross(direction).normalized();
    Vector3d up = direction.cross(right);

    view << right.x(), up.x(), direction.x(), 0,
            right.y(), up.y(), direction.y(), 0,
            right.z(), up.z(), direction.z(), 0,
            0, 0, 0, 1;

    Matrix4d translation;
    translation << 1, 0, 0, -position.x(),
                   0, 1, 0, -position.y(),
                   0, 0, 1, -position.z(),
                   0, 0, 0, 1;

    return view * translation;
  }

  void Camera::updateCameraVectors() noexcept {
    Vector3d front_;
    front_.x() = cos(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
    front_.y() = sin(pitch * M_PI / 180.0f);
    front_.z() = sin(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
    front = front_.normalized();
    right = front.cross(worldUp).normalized();
    up = right.cross(front).normalized();
  }

} // namespace Isaac