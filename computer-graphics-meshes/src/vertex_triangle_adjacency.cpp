#include "vertex_triangle_adjacency.h"

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);

  // for each vertex
  for(int i=0; i<num_vertices; i++) {

    // loop all faces
    for(int j=0; j<F.rows(); j++) {

      // if current face has the current index
      if(F(j, 0)==i || F(j, 1)==i || F(j, 2)==i) {
        VF[i].push_back(j);
      }
    }
  }

}