#include "sphere.h"
#include <iostream>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  /* in this implementation top and bottom does not count as 1 vertex, instead, treat it as quad as usual */
  int num_vertices = (num_faces_u+1) * (num_faces_v+1);
  int num_faces = num_faces_u * num_faces_v;

  V.resize(num_vertices, 3);
  F.resize(num_faces,4);
  UV.resize(num_vertices,2);
  UF.resize(num_faces,4);
  NV.resize(num_vertices,3);
  NF.resize(num_faces,4);

  double x, y, z, phi, theta;
  int index = 0;

  /* Assume it's a unit sphere 
   * and in spherical coordinate 0<=theta<=pi, 0<=phi<=2*pi*/
  for(int i=0; i<num_faces_u+1; i++) {
    theta = (double)i / num_faces_u * M_PI;

    for(int j=0; j<num_faces_v+1; j++) {
      phi = (double)j / num_faces_v * 2 * M_PI;
      x = cos(phi) * sin(theta);
      y = sin(phi) * sin(theta);
      z = -cos(theta);  // to flip the sphere
      double u = (double)i/num_faces_u; // stay in range 0 - 1
      double v = (double)j/num_faces_v; // stay in range 0 - 1

      V.row(index) = Eigen::RowVector3d(y, z, x); // makes it look like a real globe
      NV.row(index) = Eigen::RowVector3d(y, z, x);  // should be the same as V if the center is at the origin
      UV.row(index) = Eigen::RowVector2d(v, u);
      index++;
    }
  }

  index = 0;
  int v1, v2, v3, v4;

  for(int i=0; i<num_faces_u; i++) {
    for(int j=0; j<num_faces_v; j++) {

    v1 = i*(num_faces_v+1)+j+1; // top left
    v2 = v1+1;  // bottom left
    v3 = (i+1)*(num_faces_v+1)+j+1+1; // bottom right
    v4 = v3-1;  // top right

    F.row(index) = Eigen::RowVector4i(v1, v2, v3, v4);
    NF.row(index) = Eigen::RowVector4i(v1, v2, v3, v4);
    UF.row(index) = Eigen::RowVector4i(v1, v2, v3, v4); 
    index++; 
    }
  }

}