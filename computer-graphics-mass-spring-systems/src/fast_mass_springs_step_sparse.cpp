#include "fast_mass_springs_step_sparse.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::SparseMatrix<double>  & M,
  const Eigen::SparseMatrix<double>  & A,
  const Eigen::SparseMatrix<double>  & C,
  const Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  /*****************************************************************
   * Formulas and algorithms are obtained from the assignment page *
   *****************************************************************/

  double w = 1e10;
  Unext = Ucur; // initially, use the current information
  Eigen::MatrixXd y = 1.0/(pow(delta_t,2))*M*(2*Ucur-Uprev) + fext;

  for(int iter=0; iter<50; iter++) {
    Eigen::MatrixXd d = Eigen::MatrixXd::Zero(E.rows(), 3); // each row is a 3D vector

    /* local optimization */
    for(int i=0; i<E.rows(); i++) {
      d.row(i) = (Unext.row(E(i,0)) - Unext.row(E(i,1))).normalized(); // this is the direction
      d.row(i) = d.row(i) * r[i];
    }

    /* global optimization */
    Eigen::MatrixXd b = k*A.transpose()*d + y + w*C.transpose()*C*V;
    Unext = prefactorization.solve(b);
  }

}