#include "cube.h"

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  V.resize(8,3);
  F.resize(6,4);
  UV.resize(14,2);
  UF.resize(6,4);
  NV.resize(6,3);
  NF.resize(6,4);

  /* Imagine a cube with length 1 lands in non-negative x, y, z axises */

  // cube's vertices
  V << 0, 0, 1,
       1, 0, 1,
       1, 1, 1,
       0, 1, 1,
       0, 0, 0,
       1, 0, 0,
       1, 1, 0,
       0, 1, 0;

  F << 1, 2, 3, 4,      // front
       6, 5, 8, 7,      // back
       5, 1, 4, 8,      // left
       2, 6, 7, 3,      // right
       4, 3, 7, 8,      // up
       5, 6, 2, 1;      // bottom

  // cube's normal vectors
  NV << 0, 0, 1,        // front
        0, 0, -1,       // back
        -1, 0, 0,       // left
        1, 0, 0,        // right
        1, 0, 0,        // up
        -1, 0, 0;       // bottom

  NF << 1, 1, 1, 1,     // front
        2, 2, 2, 2,     // back
        3, 3, 3, 3,     // left
        4, 4, 4, 4,     // right
        5, 5, 5, 5,     // up
        6, 6, 6, 6;     // bottom

  // 2D parameterized cube (figure is in tutorial)
  UV << 0.25, 0,
        0.5, 0,
        0, 0.25,
        0.25, 0.25,
        0.5, 0.25,
        0.75, 0.25,
        1, 0.25,
        0, 0.5,
        0.25, 0.5,
        0.5, 0.5,
        0.75, 0.5,
        1, 0.5,
        0.25, 0.75,
        0.5, 0.75;

  UF << 4, 5, 10, 9,
        6, 7, 12, 11,
        3, 4, 9, 8,
        5, 6, 11, 10,
        9, 10, 14, 13,
        1, 2, 5, 4;

}