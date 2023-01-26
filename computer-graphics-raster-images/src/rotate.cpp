#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);

  /* from right to the left in a row, the rightmost pixel needs to be in the upmost pixel in the rotated image */
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++) {
      for(int channel=0; channel<num_channels; channel++){
        rotated[channel+num_channels*(i+height*j)] = input[channel+num_channels*(width-j-1+width*i)];
        rotated[channel+num_channels*(i+height*j)] = input[channel+num_channels*(width-j-1+width*i)];
        rotated[channel+num_channels*(i+height*j)] = input[channel+num_channels*(width-j-1+width*i)];
      }
    }
  }

}
