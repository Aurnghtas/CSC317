#include "hsv_to_rgb.h"
#include <cmath>
#include <math.h>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  /* conversion formula is obtained from https://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB */

  double c = v * s;
  double h_prime = fmod(h/60, 6);   // division only might cause h_prime > 6, use fmod to make sure h_prime is range from 0 to 6
  double x = c * (1 - abs(fmod(h_prime,2)-1));

  if(0<=h_prime && h_prime<1) {
    r=c;
    g=x;
    b=0;
  } else if(1<=h_prime && h_prime<2) {
    r=x;
    g=c;
    b=0;
  } else if(2<=h_prime && h_prime<3) {
    r=0;
    g=c;
    b=x;
  } else if(3<=h_prime && h_prime<4) {
    r=0;
    g=x;
    b=c;
  } else if(4<=h_prime && h_prime<5) {
    r=x;
    g=0;
    b=c;
  } else if(5<=h_prime && h_prime<6) {
    r=c;
    g=0;
    b=x;
  }

  double m = v - c;
  r+=m;
  g+=m;
  b+=m;

}
