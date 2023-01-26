#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  double x1, z, x2;

  /* convert degrees to radians */
  x1 = xzx(0) * M_PI / 180.0;
  z = xzx(1) * M_PI / 180.0;
  x2 = xzx(2) * M_PI / 180.0;

  Eigen::Matrix4d X1, Z, X2;

  X1<<1, 0, 0, 0,
      0, cos(x1), -sin(x1), 0,
      0, sin(x1), cos(x1), 0,
      0, 0, 0, 1;

  Z<<cos(z), -sin(z), 0, 0,
     sin(z), cos(z), 0, 0,
     0, 0, 1, 0,
     0, 0, 0, 1;

  X2<<1, 0, 0, 0,
      0, cos(x2), -sin(x2), 0,
      0, sin(x2), cos(x2), 0,
      0, 0, 0, 1;

  Eigen::Affine3d A;
  A = X2 * Z * X1;

  return A;

}