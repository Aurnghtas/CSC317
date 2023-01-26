#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  Eigen::VectorXd result;
  result.resize(b.size() * 3);

  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > T;
  forward_kinematics(skeleton, T);

  for(int i=0; i<b.size(); i++) {
    int index = b[i];
    Eigen::Vector4d tip = T[index] * skeleton[index].rest_T * Eigen::Vector4d(skeleton[index].length, 0, 0, 1);

    result[3 * i + 0] = tip[0];
    result[3 * i + 1] = tip[1];
    result[3 * i + 2] = tip[2];
  }

  return result;

}