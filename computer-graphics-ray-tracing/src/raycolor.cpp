#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  int hit_id;
  double t;
  Eigen::Vector3d n;
  rgb = Eigen::Vector3d(0,0,0);
  Ray reflected_ray;
  Eigen::Vector3d reflected_rgb = Eigen::Vector3d(0,0,0);

  bool isHit = first_hit(ray, min_t, objects, hit_id, t, n);

  /* algorithm is obtained from the tutorial handout */
  if(isHit) {
    rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);

    if(num_recursive_calls==20) {
      return true;
    } else {
      reflected_ray.direction = reflect(ray.direction, n);
      reflected_ray.origin = ray.origin + t*ray.direction;

      /* TA suggests use a slightly larger min_t for reflected rat */
      raycolor(reflected_ray, 1e-5, objects, lights, num_recursive_calls+1, reflected_rgb);

      /* compute the component-wise multiplication 
       * formula is obtained from the assignment - Whitelist section */
      rgb += (objects[hit_id]->material->km.array() * reflected_rgb.array()).matrix();
    }
  }

  return false;

}