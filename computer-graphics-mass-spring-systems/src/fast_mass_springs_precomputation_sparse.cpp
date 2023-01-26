#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  /*****************************************************************
   * Formulas and algorithms are obtained from the assignment page *
   *****************************************************************/

  r.resize(E.rows());
  /* get the edge length */
  for(int i=0; i<E.rows(); i++) {
    r[i] = (V.row(E(i,0)) - V.row(E(i, 1))).norm();
  }

  std::vector<Eigen::Triplet<double> > m_ijv;
  for(int i=0; i<V.rows(); i++) {
    m_ijv.emplace_back(i, i, m[i]);
  }
  M.resize(V.rows(), V.rows());
  M.setFromTriplets(m_ijv.begin(),m_ijv.end());

  signed_incidence_matrix_sparse(V.rows(), E, A);

  std::vector<Eigen::Triplet<double> > c_ijv;
  for(int i=0; i<b.rows(); i++) {
    c_ijv.emplace_back(i, b(i), 1);
  }
  C.resize(b.rows(), V.rows());
  C.setFromTriplets(c_ijv.begin(),c_ijv.end());

  double w = 1e10;
  Eigen::SparseMatrix<double> Q(V.rows(), V.rows());
  Q = k*A.transpose()*A + 1.0/(pow(delta_t, 2))*M + w*C.transpose()*C; // need to add the additional energy term

  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
