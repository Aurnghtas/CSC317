#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");

  std::ofstream file (filename);

  /*****************************************************************************************
   * Format of obj file is obtained from https://en.wikipedia.org/wiki/Wavefront_.obj_file *
   *****************************************************************************************/

  if(!file.is_open()) {
    std::cout << "Can NOT open the file" << std::endl;
    return false;
  } else {
    // geometric vertices
    for(int i=0; i<V.rows(); i++) {
      file << "v " << V(i, 0) << " " << V(i, 1) << " " << V(i, 2) << std::endl;
    }

    // texture coordinates
    for(int i=0; i<UV.rows(); i++) {
      file << "vt " << UV(i, 0) << " " << UV(i, 1) << std::endl;
    }

    // vertex normals
    for(int i=0; i<NV.rows(); i++) {  
      file << "vn " << NV(i, 0) << " " << NV(i, 1) << " " << NV(i, 2) << std::endl;
    }

    // vertex normal indices
    for(int i=0; i<F.rows(); i++) {  
      file << "f ";
      for (int j=0; j<F.cols(); j++) {
        file << F(i, j) << "/" << UF(i, j) << "/" << NF(i, j) << " ";
      }
      file << std::endl;
    }

    file.close();
    return true;
  }

}