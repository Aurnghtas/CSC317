#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  U.resize(V.rows(), 3);

  /* following algorithm is obtained from the assignment page - Linear Blend Skinning */
  for(int i=0; i<V.rows(); i++) {
    Eigen::Vector4d sum = Eigen::Vector4d(0, 0, 0, 0);

    for(int j=0; j<skeleton.size(); j++) {
      if(skeleton[j].weight_index != -1) {
        Eigen::Vector4d temp = Eigen::Vector4d(V(i, 0), V(i, 1), V(i, 2), 1.0);
        sum += W(i, skeleton[j].weight_index) * (T[j] * temp);
      }
    }

    U(i,0) = sum[0];
    U(i,1) = sum[1];
    U(i,2) = sum[2];
  }
}