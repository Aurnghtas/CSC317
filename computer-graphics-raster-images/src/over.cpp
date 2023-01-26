#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());

  /* formula for Over operator is obtained from https://en.wikipedia.org/wiki/Alpha_compositing */

  int number_channels = A.size() / (width*height);
  double alpha_a, alpha_b, alpha_0;

  for(int i=0; i<height; i++) {
    for(int j=0; j<width; j++) {
      alpha_a = A[3+number_channels*(i*width+j)]/255.0;   // divide by 255 since the range of alpha is between 0 - 1
      alpha_b = B[3+number_channels*(i*width+j)]/255.0;
      alpha_0 = alpha_a + alpha_b*(1-alpha_a);

      C[0+number_channels*(i*width+j)] = (A[0+number_channels*(i*width+j)]*alpha_a + B[0+number_channels*(i*width+j)]*alpha_b*(1-alpha_a)) / alpha_0;
      C[1+number_channels*(i*width+j)] = (A[1+number_channels*(i*width+j)]*alpha_a + B[1+number_channels*(i*width+j)]*alpha_b*(1-alpha_a)) / alpha_0;
      C[2+number_channels*(i*width+j)] = (A[2+number_channels*(i*width+j)]*alpha_a + B[2+number_channels*(i*width+j)]*alpha_b*(1-alpha_a)) / alpha_0;
      C[3+number_channels*(i*width+j)] = alpha_0*255;
    }
  }

}
