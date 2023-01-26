#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");

  std::ofstream file (filename);

  /* the format of ppm file is obtained from https://en.wikipedia.org/wiki/Netpbm#File_format_description */
  if(num_channels == 3) {
    file << "P3" << std::endl << width << " " << height << std::endl << 255 << std::endl;
    for (int i=0; i<data.size(); i++) {
      file << int(data[i]) << " ";
    }
    file.close();
    return true;
  } 
  
  else if (num_channels == 1) {
    file << "P2" << std::endl << width << " " << height << std::endl << 255 << std::endl;
    for (int i=0; i<data.size(); i++) {
      file << int(data[i]) << " ";
    }
    file.close();
    return true;
  }

  return false;

}