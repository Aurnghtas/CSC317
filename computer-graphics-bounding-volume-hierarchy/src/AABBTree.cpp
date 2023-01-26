#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  /* from side effect, num_leaves = objects.size() */

  // no objects
  if(this->num_leaves == 0) {
    this->left = NULL;
    this->right = NULL;
  } 

  // only one object
  else if(this->num_leaves == 1) {
    this->left = objects[0];
    insert_box_into_box(objects[0]->box, this->box);
    this->right = NULL;
  } 

  // two objects
  else if(this->num_leaves == 2) {
    this->left = objects[0];
    insert_box_into_box(objects[0]->box, this->box);
    this->right = objects[1];
    insert_box_into_box(objects[1]->box, this->box);
  }

  // general cases
  else {
    // get the boundary of all objects
    for(int i=0; i<num_leaves; i++) {
      insert_box_into_box(objects[i]->box, this->box);
    }
    
    /* 
     * find the longest axis
     * 0 represents x-axis
     * 1 represents y-axis
     * 2 represnets z-aixs
     */
    double x_length = this->box.max_corner[0] - this->box.min_corner[0];
    double y_length = this->box.max_corner[1] - this->box.min_corner[1];
    double z_length = this->box.max_corner[2] - this->box.min_corner[2];
    int longest_axis;
    if(x_length == std::max(std::max(x_length, y_length), z_length)) {
      longest_axis = 0;
    } else if(y_length == std::max(std::max(x_length, y_length), z_length)) {
      longest_axis = 1;
    } else {
      longest_axis = 2;
    }

    std::vector<std::shared_ptr<Object>> left_objects;
    std::vector<std::shared_ptr<Object>> right_objects;

    // x-axis is the longest axis
    if(longest_axis == 0) {
      for(int i=0; i<num_leaves; i++) {
        if(objects[i]->box.center()[0] <= this->box.center()[0]){
          left_objects.push_back(objects[i]);
        } else {
          right_objects.push_back(objects[i]);
        }
      }
    } 
    // y-axis is the longest axis
    else if (longest_axis == 1) {
      for(int i=0; i<num_leaves; i++) {
        if(objects[i]->box.center()[1] <= this->box.center()[1]){
          left_objects.push_back(objects[i]);
        } else {
          right_objects.push_back(objects[i]);
        }
      }
    } 
    // z-axis is the longest axis
    else {
      for(int i=0; i<num_leaves; i++) {
        if(objects[i]->box.center()[2] <= this->box.center()[2]){
          left_objects.push_back(objects[i]);
        } else {
          right_objects.push_back(objects[i]);
        }
      }
    }

    // if one side has no objects and the other side gets all the objects
    // need to "balance" them to avoid infinite loop
    if(left_objects.size()==0) {
      for(int i=0; i<right_objects.size()/2; i++) {
        right_objects.pop_back();   // here, right objects' size has been decreased by 1
        left_objects.push_back(objects[right_objects.size()]);  // we want the last element from right objects goes to the left objects
      }
    } else if(right_objects.size()==0) {
      for(int i=0; i<left_objects.size()/2; i++) {
        left_objects.pop_back();
        right_objects.push_back(objects[left_objects.size()]);
      }
    }

    this->left = std::make_shared<AABBTree>(left_objects, this->depth+1);
    this->right = std::make_shared<AABBTree>(right_objects, this->depth+1);

  }

}