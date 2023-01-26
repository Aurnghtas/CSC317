#include "projected_gradient_descent.h"
#include "line_search.h"

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
  /* TA suggests start from this number, up to 100000 */
  int sigma = 20000;

  for(int i=0; i<max_iters; i++) {
    Eigen::VectorXd grad = grad_f(z);
    z = z - line_search(f, proj_z, z, grad, sigma) * grad;
    proj_z(z);
  }
}