#include "first_hit.h"
#include <float.h>

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  int index = -1;
  t = FLT_MAX;
  double temp_t = -1;
  Eigen::Vector3d temp_n;

  for(int i=0; i<objects.size(); i++) {
    if(objects[i]->intersect(ray, min_t, temp_t, temp_n)) {
      if(t>temp_t) {
        index = i;
        t = temp_t;
        n = temp_n;
      }
    }
  }

  if(index == -1) {
    return false;
  } else {
    hit_id = index;
    return true;
  }

}