#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /* algorithm is obtained from the assignment page - Inverse Kinematics */
  f = [&](const Eigen::VectorXd & A)->double {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd tips = transformed_tips(copy, b);
    double cost = (tips - xb0).squaredNorm();
    return cost;
  };

  /* algorithm is obtained from the assignment page - Projected Gradient Descent */
  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd tips = transformed_tips(copy, b);
    Eigen::VectorXd dE_dx = 2*(tips - xb0);
    Eigen::MatrixXd J;
    kinematics_jacobian(copy, b, J);
    return J.transpose() * dE_dx;
  };

  /* algorithm is obtained from the assignment page - Projected Gradient Descent */
  proj_z = [&](Eigen::VectorXd & A) {
    assert(skeleton.size()*3 == A.size());
    for(int i=0; i<skeleton.size(); i++) {
      A[i * 3 + 0] = std::max(skeleton[i].xzx_min[0], std::min(skeleton[i].xzx_max[0], A[i * 3 + 0]));
      A[i * 3 + 1] = std::max(skeleton[i].xzx_min[1], std::min(skeleton[i].xzx_max[1], A[i * 3 + 1]));
      A[i * 3 + 2] = std::max(skeleton[i].xzx_min[2], std::min(skeleton[i].xzx_max[2], A[i * 3 + 2]));
    }
  };

}