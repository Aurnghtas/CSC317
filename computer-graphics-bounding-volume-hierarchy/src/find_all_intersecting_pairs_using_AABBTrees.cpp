#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  /****************************************************************
   * The following algorithm is obtained from the assignment page *
   ****************************************************************/

  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> queue;
  std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> curr_pair;
  std::shared_ptr<AABBTree> aabb_A, aabb_B;

  leaf_pairs={};

  /* if they intersect */
  if(box_box_intersect(rootA->box, rootB->box)) {
    queue.emplace_back(rootA, rootB);
  }

  while(!queue.empty()) {
    curr_pair = queue.front();
    queue.pop_front();

    aabb_A = std::dynamic_pointer_cast<AABBTree>(curr_pair.first);
    aabb_B = std::dynamic_pointer_cast<AABBTree>(curr_pair.second);
    
    /* if current pair is leaf */
    if(!aabb_A && !aabb_B) {
      leaf_pairs.emplace_back(curr_pair);
    }

    /* node A is a leaf*/
    else if(!aabb_A) {
      if(aabb_B->left!=NULL && box_box_intersect(curr_pair.first->box, aabb_B->left->box)) {
        queue.emplace_back(curr_pair.first, aabb_B->left);
      }
      if(aabb_B->right!=NULL && box_box_intersect(curr_pair.first->box, aabb_B->right->box)) {
        queue.emplace_back(curr_pair.first, aabb_B->right);
      }
    }

    /* node B is a leaf*/
    else if(!aabb_B) {
      if(aabb_A->left!=NULL && box_box_intersect(aabb_A->left->box, curr_pair.second->box)) {
        queue.emplace_back(aabb_A->left, curr_pair.second);
      }
      if(aabb_A->right!=NULL && box_box_intersect(aabb_A->right->box, curr_pair.second->box)) {
        queue.emplace_back(aabb_A->right, curr_pair.second);
      }
    }

    else {
      if(aabb_A->left!=NULL && aabb_B->left!=NULL && box_box_intersect(aabb_A->left->box, aabb_B->left->box)) {
        queue.emplace_back(aabb_A->left, aabb_B->left);
      }
      if(aabb_A->left!=NULL && aabb_B->right!=NULL && box_box_intersect(aabb_A->left->box, aabb_B->right->box)) {
        queue.emplace_back(aabb_A->left, aabb_B->right);
      }
      if(aabb_A->right!=NULL && aabb_B->right!=NULL && box_box_intersect(aabb_A->right->box, aabb_B->right->box)) {
        queue.emplace_back(aabb_A->right, aabb_B->right);
      }
      if(aabb_A->right!=NULL && aabb_B->left!=NULL && box_box_intersect(aabb_A->right->box, aabb_B->left->box)) {
        queue.emplace_back(aabb_A->right, aabb_B->left);
      }
    }
    
  }

}