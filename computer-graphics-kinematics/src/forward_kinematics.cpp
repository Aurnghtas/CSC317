#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

Eigen::Affine3d forward_recursive(int index, const Skeleton & skeleton) {
  
  /* base case - root */
  if(skeleton[index].parent_index == -1) {
    return Eigen::Affine3d::Identity();
  }

  /* get its parent */
  int parent_index = skeleton[index].parent_index;
  Eigen::Affine3d T_p = forward_recursive(parent_index, skeleton);

  /* can do the transformation */
  Bone curr_bone = skeleton[index];
  Eigen::Affine3d R = euler_angles_to_transform(curr_bone.xzx);

  /* formula taken from the lecture */
  return T_p * curr_bone.rest_T * R * curr_bone.rest_T.inverse();
}

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());

  // for each bone
  for(int i=0; i<skeleton.size(); i++) {
    T[i] = forward_recursive(i, skeleton);
  }

}