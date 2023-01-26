#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F, 
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  hit_t = std::numeric_limits<double>::infinity();
  double temp_t;

  for(int i=0; i<F.rows(); i++) {
    /* 
     * F(i, 0 to 2): one row contains 3 vertexs to make a triangle 
     * V(#row): the position of a vertex 
     */
    if(ray_intersect_triangle(ray, V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)), min_t, max_t, temp_t)) {
      if(hit_t>temp_t) {
        hit_t = temp_t;
        hit_f = i;
      }
    }
  }

  // if ray never hits
  if(hit_t==std::numeric_limits<double>::infinity()) {
    return false;
  } else {
    return true;
  }

}