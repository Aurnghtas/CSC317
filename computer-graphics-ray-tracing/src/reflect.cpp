#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  Eigen::Vector3d out = Eigen::Vector3d(0,0,0);

  /* reflection ray formula is obtained from tutorial notes */
  out = in - 2 * (in.dot(n)) * n;
  out = out.normalized();   // unit reflection vector
  return out;
  
}