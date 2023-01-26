#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);

  /* 767 times 772 rgb image, how to access the green value at the pixel on the 36th row and 89th column? *
   * data[1 + 3*(88+767*35) *
   * same idea applies for reflected, the last column becomes the first column*/
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++) {
      for(int channel=0; channel<num_channels; channel++){
        reflected[channel+num_channels*(j+width*i)] = input[channel+num_channels*(width-j-1+width*i)];
        reflected[channel+num_channels*(j+width*i)] = input[channel+num_channels*(width-j-1+width*i)];
        reflected[channel+num_channels*(j+width*i)] = input[channel+num_channels*(width-j-1+width*i)];
      }
    }
  }

}
