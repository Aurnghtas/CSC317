#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  /**************************************************************************
   * The following algorithm is obtained from the course lecture + textbook *
   **************************************************************************/
  double x_min, x_max, y_min, y_max, z_min, z_max, x_d, y_d, z_d, x_e, y_e, z_e;
  double t_xmin, t_xmax, t_ymin, t_ymax, t_zmin, t_zmax;

  x_min=box.min_corner[0];
  x_max=box.max_corner[0];
  y_min=box.min_corner[1];
  y_max=box.max_corner[1];
  z_min=box.min_corner[2];
  z_max=box.max_corner[2];

  x_d=ray.direction[0];
  y_d=ray.direction[1];
  z_d=ray.direction[2];
  x_e=ray.origin[0];
  y_e=ray.origin[1];
  z_e=ray.origin[2];


  double a = 1/x_d;
  double b = 1/y_d;
  double c = 1/z_d;

  if(a>=0) {
    t_xmin = a*(x_min-x_e);
    t_xmax = a*(x_max-x_e);
  } else {
    t_xmin = a*(x_max-x_e);
    t_xmax = a*(x_min-x_e);
  }

  if(b>=0) {
    t_ymin = b*(y_min-y_e);
    t_ymax = b*(y_max-y_e);
  } else {
    t_ymin = b*(y_max-y_e);
    t_ymax = b*(y_min-y_e);
  }

  if(c>=0) {
    t_zmin = c*(z_min-z_e);
    t_zmax = c*(z_max-z_e);
  } else {
    t_zmin = c*(z_max-z_e);
    t_zmax = c*(z_min-z_e);
  }

  double t_min = std::max(std::max(t_xmin, t_ymin), t_zmin);
  double t_max = std::min(std::min(t_xmax, t_ymax), t_zmax);

  // incorrect interval
  if(t_min>t_max) {
    return false;
  }

  /* careful: if the ray or `min_t` lands _inside_ the box 
   * this could still hit something stored inside the box,
   * so this counts as a hit */
  if(t_min<=t_max && t_max<=max_t) {
    return true;
  } else {
    return false;
  }
  
}