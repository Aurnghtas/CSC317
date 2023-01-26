#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());

  double r=0, g=0, b=0, h=0, s=0, v=0;

  for(int i=0; i<height; i++) {
    for(int j=0; j<width; j++) {
      r = rgb[0+3*(i*width+j)] / 255.0; // rgb values are 0-255, but in rgb_to_hsv, rgv values are 0.0 - 1.0
      g = rgb[1+3*(i*width+j)] / 255.0;
      b = rgb[2+3*(i*width+j)] / 255.0;

      rgb_to_hsv(r,g,b,h,s,v);

      s = (1-factor) * s;

      hsv_to_rgb(h,s,v,r,g,b);

      desaturated[0+3*(i*width+j)] = r*255;
      desaturated[1+3*(i*width+j)] = g*255;
      desaturated[2+3*(i*width+j)] = b*255;
    }
  }

}
