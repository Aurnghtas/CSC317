#include "per_vertex_normals.h"
#include "triangle_area_normal.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);

  // for each vertex
  for(int i=0; i<V.rows(); i++) {
    Eigen::RowVector3d normal = Eigen::RowVector3d(0, 0, 0);

    /* use the area-weighted per-vertex normals from assignment page */
    for(int j=0; j<F.rows(); j++) {

      // faces neighboring the current vertex
      if(F(j, 0)==i || F(j, 1)==i || F(j, 2)==i) {
        Eigen::RowVector3d A = V.row(F(j, 0));
        Eigen::RowVector3d B = V.row(F(j, 1));
        Eigen::RowVector3d C = V.row(F(j, 2));
        
        normal += triangle_area_normal(A, B, C);
      }
    }

    normal = normal.normalized();
    N.row(i) = normal;
  }

}