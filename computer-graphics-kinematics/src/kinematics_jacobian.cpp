#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  J = Eigen::MatrixXd::Zero(b.size()*3,skeleton.size()*3);

  /**********************************************************************************
   * Following algorithm is obtained from the assignment page - Finite Differencing *
   **********************************************************************************/

  double h=1e-7;
  Eigen::VectorXd tips = transformed_tips(skeleton, b);

  // for each bone
  for(int i=0; i<skeleton.size(); i++) {

    // for each Euler angle
    for(int j=0; j<3; j++) {
      Skeleton temp_skeleton = skeleton;
      temp_skeleton[i].xzx[j] += h;
      Eigen::VectorXd temp_tips = transformed_tips(temp_skeleton, b);
      J.col(i*3+j) = (temp_tips-tips)/h;
    }
  }

}