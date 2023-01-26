#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  double eplison = 1e-6;  // for fake surface use only
  double ia=0.1;  // hard-coded value of ia=0.1 for ambient light
  Eigen::Vector3d rgb = Eigen::Vector3d(0,0,0);
  
  /* algorithm is obtained from the tutorial handout */
  rgb = ia*objects[hit_id]->material->ka;

  /* for each light in lights */
  for(int i=0; i<lights.size(); i++) {
    
    Eigen::Vector3d d_l = Eigen::Vector3d(0,0,0);   // direction of the light
    double maxt_l = 0;  // max_t of the light
    lights[i]->direction(ray.origin+t*ray.direction, d_l, maxt_l);
    d_l = d_l.normalized();

    Eigen::Vector3d half = (-ray.direction.normalized() + d_l);   // the ray.direction need to be normalized, othtrwise the math is wrong
    half = half.normalized();   // unit half vector

    Ray shadow;
    shadow.direction = d_l;
    shadow.origin = ray.origin+t*ray.direction+n*eplison;
    int shadow_hitid;
    double shadow_t;
    Eigen::Vector3d shadow_n;

    /* if not shadowed by other obects 
     * directional light: only need to check first_hit
     * point light: also need to check if the light is behind the object or not */
    if(!first_hit(shadow, 0, objects, shadow_hitid, shadow_t, shadow_n) || shadow_t>maxt_l) {
      
      /* component-wise multiplication formula
       * is obtained from the assignment - Whitelist section */ 

      /* Diffuse */
      rgb += std::max(0.0, n.dot(d_l)) * (lights[i]->I.array() * objects[hit_id]->material->kd.array()).matrix();

      /* Specular */
      rgb += std::pow(std::max(0.0, n.dot(half)), objects[hit_id]->material->phong_exponent) 
              * (lights[i]->I.array() * objects[hit_id]->material->ks.array()).matrix();
    }
  }

  return rgb;

}