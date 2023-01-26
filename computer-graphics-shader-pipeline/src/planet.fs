// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
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
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
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

  float epsilon = 0.0001;
  vec3 T = vec3(0, 0, 0);
  vec3 B = vec3(0, 0, 0);
  tangent(normalize(sphere_fs_in), T, B);

  n = normalize(cross((bump_position(is_moon, sphere_fs_in+epsilon*T)-bump_position(is_moon, sphere_fs_in))/epsilon, 
                      (bump_position(is_moon, sphere_fs_in+epsilon*B)-bump_position(is_moon, sphere_fs_in))/epsilon));
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

  float sea_level = 0.0001;

  if(is_moon) {
    ka = vec3(0.01,0.01,0.01), 
    kd = vec3(0.5, 0.5, 0.5), 
    ks = vec3(0.7, 0.7, 0.7);
  } else {
    float height = bump_height(is_moon, sphere_fs_in);
    ka = vec3(0.01,0.01,0.01),
    ks = vec3(0.7, 0.7, 0.7);
    if(height < sea_level){
      kd = vec3(0, 0, 1);
    } else {
      float green_factor = 1 - abs(sphere_fs_in.y);
      kd = vec3(0.65*(green_factor), 0.65, 0.01);
    }
  }

  color = blinn_phong(ka, kd, ks, p, n, v, l);

  float cloud = improved_perlin_noise((rotate_about_y(animation_seconds/2*M_PI)*vec4(sphere_fs_in, 1)).xzy);
  ka = vec3(1)*cloud;
  kd = vec3(1)*cloud;
  ks = vec3(1)*cloud;
  
  color = color + blinn_phong(ka, kd, ks, p, n, v, l);
}