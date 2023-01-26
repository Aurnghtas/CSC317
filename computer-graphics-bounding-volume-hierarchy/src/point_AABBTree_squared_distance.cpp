#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  /* Knowledge of priority_queue is obtained from 
   * https://en.cppreference.com/w/cpp/container/priority_queue */
  std::priority_queue<std::pair<double, std::shared_ptr<Object>>, std::vector<std::pair<double, std::shared_ptr<Object>>>, 
                    std::greater<std::pair<double, std::shared_ptr<Object>>>> priority_queue;

  sqrd = std::numeric_limits<double>::infinity();
  double box_d, object_d;
  std::pair<double, std::shared_ptr<Object>> curr_pair;
  std::shared_ptr<AABBTree> aabb;
  std::shared_ptr<Object> temp_desc;

  // deal with the given root first
  box_d = point_box_squared_distance(query, root->box);
  priority_queue.push(std::make_pair(box_d, root));

  /* deal with general cases:
   * when the queue is not empty
   * take the first element and compare */
  while(!priority_queue.empty()) {
    curr_pair = priority_queue.top();
    box_d = curr_pair.first;
    priority_queue.pop();

    /* knowledge of std::dynamic_pointer_cast is from assignment page - shared pointers */
    aabb = std::dynamic_pointer_cast<AABBTree>(curr_pair.second);

    // is an AABB-tree
    if(aabb) {
      // check if left/right node exists
      if(aabb->left){
        box_d = point_box_squared_distance(query, aabb->left->box);
        priority_queue.push(std::make_pair(box_d, aabb->left));
      }
      if(aabb->right){
        box_d = point_box_squared_distance(query, aabb->right->box);
        priority_queue.push(std::make_pair(box_d, aabb->right));
      }
    }

    // is the leaf(object)
    else {
      // cannot use point_box_squared_distance, since it is the object now
      if(curr_pair.second->point_squared_distance(query, min_sqrd, max_sqrd, object_d, temp_desc)){
        sqrd=object_d;
        descendant=curr_pair.second;
        break;
      }
    }
    
  }

  if(sqrd>=min_sqrd && sqrd<max_sqrd) {
    return true;
  } else {
    return false;
  }

}