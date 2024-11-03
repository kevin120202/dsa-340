#ifndef NIU_CSCI330_BINTREE_IMPL_H
#define NIU_CSCI330_BINTREE_IMPL_H

#include "bintree.decl.h"
#include <vector>
#include <queue>

// Preorder traversal
template <typename BINTREENODE, typename FN>
void preorder(BINTREENODE *root, FN fn) {
  if (root) {
    fn(root);
    preorder(root->left, fn);
    preorder(root->right, fn);
  }
}

// Inorder traversal
template <typename BINTREENODE, typename FN>
void inorder(BINTREENODE *root, FN fn) {
  if (root) {
    inorder(root->left, fn);
    fn(root);
    inorder(root->right, fn);
  }
}

// Postorder traversal
template <typename BINTREENODE, typename FN>
void postorder(BINTREENODE *root, FN fn) {
  if (root) {
    postorder(root->left, fn);
    postorder(root->right, fn);
    fn(root);
  }
}

// Level order traversal
template <typename BINTREENODE, typename FN>
void levelorder(BINTREENODE *root, FN fn) {
  if (!root) return;
  std::queue<BINTREENODE*> q;
  q.push(root);
  while (!q.empty()) {
    BINTREENODE *node = q.front();
    q.pop();
    fn(node);
    if (node->left) q.push(node->left);
    if (node->right) q.push(node->right);
  }
}

// Get all direct children in a tilted tree
template <typename BINTREENODE>
std::vector<BINTREENODE *> tilted_get_children(BINTREENODE *node) {
  std::vector<BINTREENODE*> children;
  if (node) {
    BINTREENODE *child = node->left;
    while (child) {
      children.push_back(child);
      child = child->right;
    }
  }
  return children;
}

template <typename BINTREENODE>
BINTREENODE* tilted_find_parent(BINTREENODE *node) {
    if (!node || !node->parent) return nullptr;

    BINTREENODE* ancestor = node->parent;

    // Traverse upward in the tree hierarchy
    while (ancestor) {
        // Check if the current ancestor has this node in its "tilted children" (right siblings of the left child)
        BINTREENODE* child = ancestor->left;

        while (child) {
            if (child == node) {
                return ancestor;
            }
            child = child->right;  // Move to the next sibling
        }

        ancestor = ancestor->parent;  // Move up to the next ancestor
    }

    return nullptr;  // If no parent found
}

// Tilted level order traversal
template <typename BINTREENODE, typename FN>
void tilted_levelorder(BINTREENODE *root, FN fn) {
  if (!root) return;
  std::queue<BINTREENODE*> q;
  q.push(root);
  
  while (!q.empty()) {
    BINTREENODE *node = q.front();
    q.pop();
    fn(node);
    
    for (BINTREENODE *child : tilted_get_children(node)) {
      q.push(child);
    }
  }
}

// Delete all nodes in the tree
template <typename BINTREENODE>
void delete_tree(BINTREENODE *&node) {
  if (node) {
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
    node = nullptr;
  }
}

#endif

