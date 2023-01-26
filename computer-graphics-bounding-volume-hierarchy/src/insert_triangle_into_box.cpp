#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  double x_min, y_min, z_min, x_max, y_max, z_max;

  x_min = std::min(std::min(a[0], b[0]), c[0]);
  y_min = std::min(std::min(a[1], b[1]), c[1]);
  z_min = std::min(std::min(a[2], b[2]), c[2]);

  x_max = std::max(std::max(a[0], b[0]), c[0]);
  y_max = std::max(std::max(a[1], b[1]), c[1]);
  z_max = std::max(std::max(a[2], b[2]), c[2]);

  if(x_min<B.min_corner[0]) {
    B.min_corner[0]=x_min;
  }

  if(y_min<B.min_corner[1]) {
    B.min_corner[1]=y_min;
  }

  if(z_min<B.min_corner[2]) {
    B.min_corner[2]=z_min;
  }

  if(x_max>B.max_corner[0]) {
    B.max_corner[0]=x_max;
  }

  if(y_max>B.max_corner[1]) {
    B.max_corner[1]=y_max;
  }

  if(z_max>B.max_corner[2]) {
    B.max_corner[2]=z_max;
  }

}