#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  Eigen::RowVector3d closest_point = Eigen::RowVector3d{0, 0, 0};
  for(int i=0; i<3; i++) {
    // outside the range of the specified axis
    if(query[i] <= box.min_corner[i]) {
      closest_point[i] = box.min_corner[i];
    } 
    else if(query[i] >= box.max_corner[i]) {
      closest_point[i] = box.max_corner[i];
    }
    // inside the specified axis
    else {
      closest_point[i] = query[i];
    }
  }

  return (closest_point-query).squaredNorm();
}
