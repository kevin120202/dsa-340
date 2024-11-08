#ifndef LEHUTA_BINTREE_H_IMPL
#define LEHUTA_BINTREE_H_IMPL

#include "bintree.decl.h"
#include <queue>

// height of tree, defined as the number of edges in the longest path
// from the root to a leaf. If you're off the tree, this should return -1.
template <typename NODE>
int height(NODE * node) {
  // XXX You need to implement this
  return 9999999;
}
template <typename NODE>
int count(NODE * root) {
  // XXX You need to implement this
  return 9999999;
}

/**
 * @brief Performs a preorder traversal of the binary tree.
 * 
 * @tparam NODE The type of the binary tree node.
 * @tparam FN The type of the function to execute on each node.
 * @param root Pointer to the root of the binary tree.
 * @param fn Function to execute on each node.
 */
template <typename NODE, typename FN>
void preorder(NODE *root, FN fn) {
    if (root) {
        fn(root);
        preorder(root->left, fn);
        preorder(root->right, fn);
    }
}

/**
 * @brief Performs an inorder traversal of the binary tree.
 * 
 * @tparam NODE The type of the binary tree node.
 * @tparam FN The type of the function to execute on each node.
 * @param root Pointer to the root of the binary tree.
 * @param fn Function to execute on each node.
 */
template <typename NODE, typename FN>
void inorder(NODE *root, FN fn) {
    if (root) {
        inorder(root->left, fn);
        fn(root);
        inorder(root->right, fn);
    }
}

/**
 * @brief Performs a postorder traversal of the binary tree.
 * 
 * @tparam NODE The type of the binary tree node.
 * @tparam FN The type of the function to execute on each node.
 * @param root Pointer to the root of the binary tree.
 * @param fn Function to execute on each node.
 */
template <typename NODE, typename FN>
void postorder(NODE *root, FN fn) {
    if (root) {
        postorder(root->left, fn);
        postorder(root->right, fn);
        fn(root);
    }
}

/**
 * @brief Performs a level order traversal of the binary tree.
 * 
 * @tparam BINTREENODE The type of the binary tree node.
 * @tparam FN The type of the function to execute on each node.
 * @param root Pointer to the root of the binary tree.
 * @param fn Function to execute on each node.
 */
template <typename NODE, typename FN>
void levelorder(NODE *root, FN fn) {
    if (!root) return;
    std::queue<NODE*> q;
    q.push(root);
    while (!q.empty()) {
        NODE *node = q.front();
        q.pop();
        fn(node);
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

/**
 * @brief Deletes all nodes in the binary tree, deallocating the entire tree.
 * 
 * @tparam BINTREENODE The type of the binary tree node.
 * @param node Reference to the pointer to the root node of the tree.
 */
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