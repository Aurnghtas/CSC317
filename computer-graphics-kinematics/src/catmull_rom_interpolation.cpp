#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  Eigen::Vector3d result = Eigen::Vector3d(0, 0, 0);

  /* nothing in the keyframes */
  if(keyframes.empty()) {
    return result;
  }

  /* only one keyframe */
  if(keyframes.size() == 1) {
    return keyframes[0].second;
  }

  /* if the query time is less/greater than and equal to the first/last keyframe */
  if(t<=keyframes[0].first) {
    return keyframes[0].second;
  } else if (t>=keyframes.back().first){
    return keyframes.back().second;
  }

  int index = 0;
  while(index<keyframes.size()) {

    // is the key frame
    if(t == keyframes[index].first) {
      return keyframes[index].second;
    }

    // find the interval
    if(t < keyframes[index].first) {
      break;
    }
    
    index++;
  }

  double t0, t1, t2, t3; // t1 and t2 is from the actual left and right bound point
  Eigen::Vector3d theta0, theta1, theta2, theta3, m0, m1; // theta1 and theta2 is from the actual left and right bound point

  /* following algorithm is obtained from the lecture */ 
  t0 = (index==1)?keyframes[index-1].first:keyframes[index-2].first;
  t1 = keyframes[index-1].first;
  t2 = keyframes[index].first;
  t3 = (index==keyframes.size()-1)?keyframes[index].first:keyframes[index+1].first;

  theta0 = (index==1)?keyframes[index-1].second:keyframes[index-2].second;
  theta1 = keyframes[index-1].second;
  theta2 = keyframes[index].second;
  theta3 = (index==keyframes.size()-1)?keyframes[index].second:keyframes[index+1].second;

  m0 = (theta2-theta0)/(t2-t0);
  m1 = (theta3-theta1)/(t3-t1);

  t = (t-t1)/(t2-t1);

  result = (2 * pow(t, 3) - 3 * pow(t, 2) + 1) * theta1 +
           (pow(t, 3) - 2 * pow(t, 2) + t) * m0 + 
           (- 2 * pow(t, 3) + 3 * pow(t, 2)) * theta2 +
           (pow(t, 3) - pow(t, 2)) * m1;

  return result;
  
}