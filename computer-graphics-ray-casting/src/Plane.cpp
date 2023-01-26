#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  /* denominator cannot be zero */
  if(normal.dot(ray.direction) == 0) {
    return false;
  }

  /* the formula is obtained from the course textbook */
  double temp_t = - normal.dot(ray.origin - point) / normal.dot(ray.direction);

  if(temp_t<min_t){
    return false;
  } else {
    t = temp_t;
    n = normal;
    return true;
  }

}