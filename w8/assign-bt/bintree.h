/************************************************************************************
 ** NIU CSCI 340 Section 2 * Assignment #7 Kevin Dela Paz - z2017241 *
 **
 * I certify that everything I am submitting is either provided by the professor
 *for use in * the assignment, or work done by me personally. I understand that
 *if I am caught submitting * the work of others (including StackOverflow or
 *ChatGPT) as my own is an act of Academic * Misconduct and will be punished as
 *such. *
 ************************************************************************************/

#ifndef NIU_CSCI330_BINTREE_IMPL_H
#define NIU_CSCI330_BINTREE_IMPL_H

#include "bintree.decl.h"
#include <vector>
#include <queue>

/**
 * @brief Performs a preorder traversal of the binary tree.
 * 
 * @tparam BINTREENODE The type of the binary tree node.
 * @tparam FN The type of the function to execute on each node.
 * @param root Pointer to the root of the binary tree.
 * @param fn Function to execute on each node.
 */
template <typename BINTREENODE, typename FN>
void preorder(BINTREENODE *root, FN fn) {
    if (root) {
        fn(root);
        preorder(root->left, fn);
        preorder(root->right, fn);
    }
}

/**
 * @brief Performs an inorder traversal of the binary tree.
 * 
 * @tparam BINTREENODE The type of the binary tree node.
 * @tparam FN The type of the function to execute on each node.
 * @param root Pointer to the root of the binary tree.
 * @param fn Function to execute on each node.
 */
template <typename BINTREENODE, typename FN>
void inorder(BINTREENODE *root, FN fn) {
    if (root) {
        inorder(root->left, fn);
        fn(root);
        inorder(root->right, fn);
    }
}

/**
 * @brief Performs a postorder traversal of the binary tree.
 * 
 * @tparam BINTREENODE The type of the binary tree node.
 * @tparam FN The type of the function to execute on each node.
 * @param root Pointer to the root of the binary tree.
 * @param fn Function to execute on each node.
 */
template <typename BINTREENODE, typename FN>
void postorder(BINTREENODE *root, FN fn) {
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

/**
 * @brief Retrieves all direct children of a node in a tilted binary tree structure.
 * 
 * @tparam BINTREENODE The type of the binary tree node.
 * @param node Pointer to the node whose children are to be retrieved.
 * @return A vector containing pointers to the direct children of the node.
 */
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

/**
 * @brief Finds the parent of a given node in a tilted binary tree.
 * 
 * @tparam BINTREENODE The type of the binary tree node.
 * @param node Pointer to the node whose parent is to be found.
 * @return A pointer to the parent node, or nullptr if no parent is found.
 */
template <typename BINTREENODE>
BINTREENODE* tilted_find_parent(BINTREENODE *node) {
    if (!node || !node->parent) return nullptr;

    BINTREENODE* ancestor = node->parent;

    // Traverse upward in the tree hierarchy
    while (ancestor) {
        BINTREENODE* child = ancestor->left;

        while (child) {
            if (child == node) {
                return ancestor;
            }
            child = child->right;
        }

        ancestor = ancestor->parent;
    }

    return nullptr;
}

/**
 * @brief Performs a tilted level order traversal of the binary tree.
 * 
 * @tparam BINTREENODE The type of the binary tree node.
 * @tparam FN The type of the function to execute on each node.
 * @param root Pointer to the root of the binary tree.
 * @param fn Function to execute on each node.
 */
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
