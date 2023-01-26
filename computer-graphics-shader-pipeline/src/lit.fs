// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  vec3 ka;
  vec3 kd;
  vec3 ks;
  float p = 1000;
  vec3 n;
  vec3 v;
  vec3 l;

  vec3 eye = vec3(0, 0, 0); // assume the origin is the eye
  n = normalize(normal_fs_in);
  v = normalize(eye - view_pos_fs_in.xyz);
  
  float period = 8.0; // one period
  float omega = 2*M_PI/period;  // angular velocity = 2*pi*frequency
  float theta = omega*animation_seconds;
  mat4 rotation = mat4(cos(theta), 0, sin(theta), 0, 
                      0, 1, 0, 0,
                      -sin(theta),0,cos(theta),0,
                      0,0,0,1); // light is cw rotation
  vec4 orbiting_light = view*rotation*vec4(6, 6, 6, 1);

  l = normalize(orbiting_light.xyz - view_pos_fs_in.xyz);

  if(is_moon) {
    ka = vec3(0.01,0.01,0.01), 
    kd = vec3(0.5, 0.5, 0.5), 
    ks = vec3(0.7, 0.7, 0.7);
  } else {
    ka = vec3(0.01,0.01,0.01), 
    kd = vec3(0, 0, 1), 
    ks = vec3(0.7, 0.7, 0.7);
  }

  color = blinn_phong(ka, kd, ks, p, n, v, l);

}