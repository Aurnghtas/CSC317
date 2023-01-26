#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  /***********************************************************
   * Following algorithm is obtained from the course lecture *
   ***********************************************************/

  // does not hit the bounding box
  if(!ray_intersect_box(ray, this->box, min_t, max_t)) {
    return false;
  } 
  else {
    bool hit_left, hit_right;
    double left_t, right_t;
    std::shared_ptr<Object> left_desc, right_desc;
    
    // the left/right node needs to exist first, then check
    if(this->left != NULL) {
      hit_left = this->left->ray_intersect(ray, min_t, max_t, left_t, left_desc);
    }
    if(this->right != NULL) {
      hit_right = this->right->ray_intersect(ray, min_t, max_t, right_t, right_desc);
    }

    // hit the leaf
    if(!std::dynamic_pointer_cast<AABBTree>(this->left)){
      left_desc=this->left;
    }
    if(!std::dynamic_pointer_cast<AABBTree>(this->right)){
      right_desc=this->right;
    }
    
    if(hit_left && hit_right) {
      t=std::min(left_t, right_t);
      if(t==left_t) {
        descendant = left_desc;
      } else {
        descendant = right_desc;
      }
      return true;
    } else if(hit_left) {
      t = left_t;
      descendant = left_desc;
      return true;
    } else if(hit_right) {
      t = right_t;
      descendant = right_desc;
      return true;
    } else {
      return false;
    }
  }

}