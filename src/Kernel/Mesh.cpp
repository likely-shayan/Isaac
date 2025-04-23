#include "Kernel/Mesh.hpp"
#include "Kernel/Constants.hpp"

namespace Isaac
{

  Mesh::Mesh(const std::vector<Isaac::Shape>& shapes_) noexcept : shapes(shapes_), meshSize(shapes_.size()), Velocities(shapes_.size(), {0, 0}) {}

  Mesh::Mesh(const Mesh&& mesh_) noexcept : Mesh(mesh_.getShapes()) {}

  int Mesh::getMeshSize() const noexcept {return shapes.size();}

  std::vector<Isaac::Shape> Mesh::getShapes() const noexcept {return shapes;}

  Vector2f Mesh::getPosition(const int& index) const
  {

    if (index < 0 || index >= getMeshSize()) throw std::invalid_argument("Invalid index of Shape in Mesh");

    return shapes[index].getPositionVector();
  }

  float Mesh::getMass(const int& index) const
  {

    if (index < 0 || index >= getMeshSize()) throw std::invalid_argument("Invalid index of Shape in Mesh");

    return shapes[index].getMass();
  }

  Vector2f Mesh::getNetForce(const int& index) const
  {

    if (index < 0 || index >= getMeshSize()) throw std::invalid_argument("Invalid index of Shape in Mesh");

    Vector2f netForce(0.0f, 0.0f);

    for (int i = 0; i < getMeshSize(); ++i)
    {
      if (index == i) continue;

      Vector2f directionVector = getPosition(i) - getPosition(index);

      netForce += ((GRAVITATIONAL_CONSTANT * getMass(i) * getMass(index)) / directionVector.squaredNorm()) * directionVector.normalized();
    }

    return netForce;
  }

  Vector2f Mesh::getNetAcceleration(const int& index) const
  {

    if (index < 0 || index >= getMeshSize()) throw std::invalid_argument("Invalid index of Shape in Mesh");

    return getNetForce(index) / getMass(index);
  }

  Vector2f Mesh::getVelocity(const int& index) const
  {

    if (index < 0 || index >= getMeshSize()) throw std::invalid_argument("Invalid index of Shape in Mesh");

    return Velocities[index];
  }

  void Mesh::updateVelocity(const int& index)
  {

    if (index < 0 || index >= getMeshSize()) throw std::invalid_argument("Invalid index of Shape in Mesh");


    Velocities[index] += getNetAcceleration(index) * TIME_PRECISION;
  }

  void Mesh::updatePostion(const int& index)
  {

    if (index < 0 || index >= getMeshSize()) throw std::invalid_argument("Invalid index of Shape in Mesh");

    updateVelocity(index);

    shapes[index].setPositionVector(getPosition(index) + (getVelocity(index) * TIME_PRECISION));
  }

}; // namespace Isaac