#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  /* this->d is the direction from light to the scene
   * simply reverse the direction */ 
  d = -this->d;
  d = d.normalized();

  /* we can think of the light is from the sun
   * therefore the distance can be evaluated as inf */
  max_t = std::numeric_limits<double>::infinity();
}