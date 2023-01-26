// Construct the model transformation matrix. The moon should orbit around the
// origin. The other object should stay still.
//
// Inputs:
//   is_moon  whether we're considering the moon
//   time  seconds on animation clock
// Returns affine model transformation as 4x4 matrix
//
// expects: identity, rotate_about_y, translate, PI
mat4 model(bool is_moon, float time)
{
  if(is_moon){
    float period = 4.0; // one period
    float omega = 2*M_PI/period;  // angular velocity = 2*pi*frequency
    float theta = omega*time;
    vec3 shift_away = vec3(2, 0, 0);

    mat4 rotation = rotate_about_y(theta);
    mat4 translate = translate(shift_away); // shift away from the origin by 2 units
    mat4 scale = uniform_scale(0.3);  // shrink by 70%
    
    return rotation*translate*scale;

  } else{
    return identity();
  }
}