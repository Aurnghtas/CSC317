#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  std::vector<std::vector<int>>VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  // taken from TA on discord
  double cos_threshold = cos(corner_threshold * M_PI / 180.0);

  for(int i=0; i<F.rows(); i++) {
    Eigen::RowVector3d face_normal = triangle_area_normal(V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)));
    face_normal = face_normal.normalized();

    // for each corner
    for(int j=0; j<3; j++) {
      // get the other faces
      std::vector<int> other_faces = VF[F(i, j)];
      Eigen::RowVector3d corner_face_normal = Eigen::RowVector3d(0, 0, 0);

      // for other faces
      for(int k=0; k<other_faces.size(); k++) {
        Eigen::RowVector3d other_face_normal = triangle_area_normal(V.row(F(other_faces[k], 0)), V.row(F(other_faces[k], 1)), V.row(F(other_faces[k], 2)));
        other_face_normal = other_face_normal.normalized();
        
        // accept it
        if(face_normal.dot(other_face_normal) > cos_threshold) {
          corner_face_normal +=other_face_normal;
        }

      }

      corner_face_normal = corner_face_normal.normalized();
      N.row(i*3+j) = corner_face_normal;
    }
  }

}