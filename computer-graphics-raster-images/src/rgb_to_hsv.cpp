#include "rgb_to_hsv.h"
#include <algorithm>
#include <math.h>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  /* conversion formula is obtained from https://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB */

  double x_max = std::max(std::max(r, g), b);
  double x_min = std::min(std::min(r, g), b);
  double c = x_max - x_min;

  /* value */
  v = x_max;

  /* hue */
  if(c == 0) {
    h = 0;
  } else if (v == r) {
    h = 60 * (g-b)/c;
  } else if (v == g) {
    h = 60 * (2 + (b-r)/c);
  } else if (v == b) {
    h = 60 * (4 + (r-g)/c);
  }

  if(h<360) {
    h = 360 + h;
  }

  /* saturation */
  if(v == 0) {
    s = 0;
  } else {
    s = c/x_max;
  }

}
