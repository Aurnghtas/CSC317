#include "Triangle.h"
#include "Ray.h"
#include <tuple>
#include <iostream>
#include <Eigen/Geometry>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  /* the formula is obtained from the course textbook */
  double a, b, c, d, e, f, g, h, i, j, k, l;
  double xa, xb, xc, xd, xe, ya, yb, yc, yd, ye, za, zb, zc, zd, ze;
  double beta, gamma, M;

  Eigen::Vector3d A = std::get<0>(corners);
  Eigen::Vector3d B = std::get<1>(corners);
  Eigen::Vector3d C = std::get<2>(corners);

  xa=A[0];
  xb=B[0];
  xc=C[0];
  xd=ray.direction[0];
  xe=ray.origin[0];

  ya=A[1];
  yb=B[1];
  yc=C[1];
  yd=ray.direction[1];
  ye=ray.origin[1];

  za=A[2];
  zb=B[2];
  zc=C[2];
  zd=ray.direction[2];
  ze=ray.origin[2];

  a=xa-xb;
  d=xa-xc;
  g=xd;
  j=xa-xe;
  b=ya-yb;
  e=ya-yc;
  h=yd;
  k=ya-ye;
  c=za-zb;
  f=za-zc;
  i=zd;
  l=za-ze;

  M = a*(e*i-h*f) + b*(g*f-d*i) + c*(d*h-e*g);
  beta = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h-e*g))/M;
  gamma = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/M;
  t = - (f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c))/M;

  if(t<min_t) {
    return false;
  } else if(gamma<0 || gamma >1 || beta<0 || (beta+gamma)>1) {
    return false;
  } else {
    Eigen::Vector3d normal = (A-B).cross(A-C);
    n = normal / normal.norm();
    return true;
  }

}