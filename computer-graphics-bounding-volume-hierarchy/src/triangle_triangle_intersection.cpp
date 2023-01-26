#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"
#include <Eigen/Geometry>

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  /*************************************************************************
   *       Some parts of the following algorithm is obtained from          *
   * https://web.stanford.edu/class/cs277/resources/papers/Moller1997b.pdf *
   *       in this assignment, assume triangles are not co-planar          *
   *************************************************************************/

  /* compute plane equation of triangle 2 */
  Eigen::RowVector3d n2 = (B1-B0).cross(B2-B0);
  double d2=-n2.dot(B0);

  /* signed distances from the vertics of triangle A to B's plane equation*/
  double d_A0 = n2.dot(A0)+d2; 
  double d_A1 = n2.dot(A1)+d2; 
  double d_A2 = n2.dot(A2)+d2; 

  bool rejectA = false;

  /* check if all three values are > 0 and have the same sign */
  if(d_A0*d_A1>0 && d_A0*d_A2>0) {
    rejectA = true;
  }

  if(rejectA) {
    return false;
  }
  
  /* compute plane equation of triangle 1 */
  Eigen::RowVector3d n1 = (A1-A0).cross(A2-A0);
  double d1=-n1.dot(A0);

  /* signed distances from the vertics of triangle A to B's plane equation*/
  double d_B0 = n1.dot(B0)+d1; 
  double d_B1 = n1.dot(B1)+d1; 
  double d_B2 = n1.dot(B2)+d1; 

  bool rejectB = false;

  /* check if all three values are > 0 and have the same sign */
  if(d_B0*d_B1>0 && d_B1*d_B2>0) {
    rejectB = true;
  }

  if(rejectB) {
    return false;
  }

  /* above algorithm should examine most of the no intersection case
   * now the following algorithm should determine some intersection case */
  bool intersect = false;
  double t;
  if (ray_intersect_triangle(Ray(B0, B1-B0), A0, A1, A2, 0, 1, t) ||
      ray_intersect_triangle(Ray(B1, B2-B1), A0, A1, A2, 0, 1, t) ||
      ray_intersect_triangle(Ray(B2, B0-B2), A0, A1, A2, 0, 1, t) ||
      ray_intersect_triangle(Ray(A0, A1-A0), B0, B1, B2, 0, 1, t) ||
      ray_intersect_triangle(Ray(A1, A2-A1), B0, B1, B2, 0, 1, t) ||
      ray_intersect_triangle(Ray(A2, A0-A2), B0, B1, B2, 0, 1, t) ) {
        intersect = true;
      }
  
  if(intersect) {
    return true;
  } else {
    return false;
  }
  
}