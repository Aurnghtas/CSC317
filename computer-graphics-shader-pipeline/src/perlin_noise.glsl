// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
float perlin_noise( vec3 st) 
{
  /**********************************************************************************
  * Following algorithm is obtained from https://en.wikipedia.org/wiki/Perlin_noise *
  *             and https://adrianb.io/2014/08/09/perlinnoise.html                  *      
  ***********************************************************************************/

  int x0 = int(floor(st.x));
  int x1 = x0 + 1;
  int y0 = int(floor(st.y));
  int y1 = y0 + 1;
  int z0 = int(floor(st.z));
  int z1 = z0 + 1;

  float sx = smooth_step(st.x - float(x0));
  float sy = smooth_step(st.y - float(y0));
  float sz = smooth_step(st.z - float(z0));

  vec3 v1 = vec3(x0, y0, z0);
  vec3 g1 = random_direction(v1);
  vec3 d1 = st - v1;
  float n1 = dot(d1, g1);

  vec3 v2 = vec3(x1, y0, z0);
  vec3 g2 = random_direction(v2);
  vec3 d2 = st - v2;
  float n2 = dot(d2, g2);

  vec3 v3 = vec3(x0, y1, z0);
  vec3 g3 = random_direction(v3);
  vec3 d3 = st - v3;
  float n3 = dot(d3, g3);

  vec3 v4 = vec3(x1, y1, z0);
  vec3 g4 = random_direction(v4);
  vec3 d4 = st - v4;
  float n4 = dot(d4, g4);

  vec3 v5 = vec3(x0, y0, z1);
  vec3 g5 = random_direction(v5);
  vec3 d5 = st - v5;
  float n5 = dot(d5, g5);

  vec3 v6 = vec3(x1, y0, z1);
  vec3 g6 = random_direction(v6);
  vec3 d6 = st - v6;
  float n6 = dot(d6, g6);

  vec3 v7 = vec3(x0, y1, z1);
  vec3 g7 = random_direction(v7);
  vec3 d7 = st - v7;
  float n7 = dot(d7, g7);

  vec3 v8 = vec3(x1, y1, z1);
  vec3 g8 = random_direction(v8);
  vec3 d8 = st - v8;
  float n8 = dot(d8, g8);

  float ix1 = (n2-n1)*sx+n1;
  float ix2 = (n4-n3)*sx+n3;
  float ix3 = (n6-n5)*sx+n5;
  float ix4 = (n8-n7)*sx+n7;

  float iy1 = (ix2-ix1)*sy+ix1;
  float iy2 = (ix4-ix3)*sy+ix3;

  float iz1 = (iy2-iy1)*sz+iy1;
  
  return iz1;
}