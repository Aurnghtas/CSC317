// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  vec3 x_axis = vec3(1, 0, 0);
  vec3 y_axis = vec3(0, 1, 0);
  vec3 zero = vec3(0, 0, 0);

  if(cross(N, x_axis) == zero) {
    T = cross(N, y_axis);
  } else {
    T = cross(N, x_axis);
  }
  
  B = cross(N, T);
}