#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  double sigma = max_step;

  /* algorithm obtained from the assignment page - Line Search */
  Eigen::VectorXd curr_z = z - sigma*dz;
  proj_z(curr_z);

  while(f(curr_z)>f(z)) {
    sigma = sigma / 2.0;
    curr_z = z - sigma*dz;
    proj_z(curr_z);
  }

  return sigma;
}