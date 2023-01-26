#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  /* the formula is obtained from the course textbook */
  double A, B, C, discriminant, t1, t2;

  A=ray.direction.dot(ray.direction);
  B=2*ray.direction.dot(ray.origin-center);
  C=(ray.origin-center).dot(ray.origin-center) - radius*radius;
  discriminant = B*B - 4*A*C;

  if(discriminant<0) {
    return false;
  } else if(discriminant == 0) {
    t = -B/(2*A);
  } else {
    t1 = (-B + sqrt(discriminant))/(2*A);
    t2 = (-B - sqrt(discriminant))/(2*A);
    t = std::min(t1, t2);
    if(t1<min_t || t2<min_t) {
      t = std::max(t1, t2);
    }
  }

  if(t<min_t) {
    return false;
  } else {
    Eigen::Vector3d p=ray.origin+t*ray.direction;
    n=(p-center)/radius;
    return true;
  }

}