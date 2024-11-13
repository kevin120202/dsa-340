/************************************************************************************
 ** NIU CSCI 340 Section 2 * Assignment #8 Kevin Dela Paz - z2017241 *
 **
 * I certify that everything I am submitting is either provided by the professor
 *for use in * the assignment, or work done by me personally. I understand that
 *if I am caught submitting * the work of others (including StackOverflow or
 *ChatGPT) as my own is an act of Academic * Misconduct and will be punished as
 *such. *
 ************************************************************************************/

#ifndef NIU_CSCI340_BST_H_IMPL
#define NIU_CSCI340_BST_H_IMPL

#include "bst.decl.h"
#include "bintree.h"
#include <iostream>
#include <algorithm>

/**
 * @brief Finds a node with the specified value in a binary search tree.
 * 
 * @tparam NODE The node type.
 * @tparam T The type of the value being searched.
 * @param root Pointer to the root node of the tree.
 * @param value The value to search for.
 * @return Pointer to the node with the specified value, or nullptr if not found.
 */
template <typename NODE, typename T>
NODE* bst_find(NODE* root, const T& value) {
    if (!root) return nullptr; // (base case)
    if (root->data == value) return root; // Return node if value matches
    // Recur down the left or right subtree based on value comparison
    return (value < root->data) ? bst_find(root->left, value) : bst_find(root->right, value);
}

/**
 * @brief Inserts a node with a specific value into the binary search tree.
 * 
 * @tparam NODEP The node type.
 * @tparam T The type of the value to insert.
 * @param root Reference to the pointer of the root node of the tree.
 * @param value The value to insert.
 * @return Pointer to the newly inserted node, or nullptr if the value already exists.
 */
template <typename NODEP, typename T>
NODEP* bst_insert(NODEP*& root, const T& value) {
    if (!root) { // If the tree is empty, insert at root
        root = new NODEP(value);
        return root;
    }
    NODEP* parent = nullptr; // Pointer to keep track of the parent node
    NODEP* current = root; // Start from the root node
    while (current) { // Traverse the tree to find insertion point
        parent = current;
        if (value < current->data)
            current = current->left;
        else if (value > current->data)
            current = current->right;
        else
            return nullptr;
    }

    // Create new node and set parent link
    NODEP* newNode = new NODEP(value);
    newNode->parent = parent;
    // Attach the new node as a left or right child
    if (value < parent->data) parent->left = newNode;
    else parent->right = newNode;
    return newNode;
}

/**
 * @brief Removes a node with a specific value from the binary search tree.
 * 
 * @tparam NODEP The node type.
 * @tparam T The type of the value to remove.
 * @param root Reference to the pointer of the root node of the tree.
 * @param value The value to remove.
 * @return Pointer to the removed node, or nullptr if the node was not found.
 */
template <typename NODEP, typename T>
NODEP* bst_remove_value(NODEP*& root, const T& value) {
    NODEP* node = bst_find(root, value); // Step 1: Find the node to remove
    if (!node) return nullptr; 

    NODEP* parent = node->parent; // Get the parent node
    NODEP* replacement = nullptr; // Initialize replacement node

    if (!node->left || !node->right) { // Case 1: Node has at most one child
        replacement = node->left ? node->left : node->right;
        if (replacement) replacement->parent = parent; // Set replacement's parent

        if (!parent) root = replacement; // Node to delete is root
        else if (parent->left == node) parent->left = replacement;
        else parent->right = replacement; 
        
        delete node; // Remove node
    } else { // Case 2: Node has two children
        NODEP* successor = bst_minimum(node->right); // Find in-order successor
        node->data = successor->data;

        // Remove the successor node
        if (successor->parent->left == successor) successor->parent->left = successor->right;
        else successor->parent->right = successor->right;

        if (successor->right) successor->right->parent = successor->parent; // Update child's parent

        delete successor; // Delete the successor
    }
    return node;
}

/**
 * @brief Helper function to check if a tree is a binary search tree.
 * 
 * @tparam NODE The node type.
 * @param root Pointer to the root node of the tree.
 * @param minNode Pointer to the minimum  node.
 * @param maxNode Pointer to the maximum  node.
 * @return True if the tree is a binary search tree, false otherwise.
 */
template <typename NODE>
bool is_bst_helper(NODE* root, NODE* minNode, NODE* maxNode) {
    if (!root) return true; // Base case
    // Check for violations of BST properties
    if ((minNode && root->data <= minNode->data) || (maxNode && root->data >= maxNode->data)) return false;
    // Recursively check left and right subtrees
    return is_bst_helper(root->left, minNode, root) && is_bst_helper(root->right, root, maxNode);
}

/**
 * @brief Checks if a binary tree is a binary search tree.
 * 
 * @tparam NODE The node type.
 * @param root Pointer to the root node of the tree.
 * @return True if the tree is a binary search tree, false otherwise.
 */
template <typename NODE>
bool is_bst(NODE* root) {
    return is_bst_helper(root, static_cast<NODE*>(nullptr), static_cast<NODE*>(nullptr)); 
}

/**
 * @brief Finds the node with the minimum value in a binary search tree.
 * 
 * @tparam NODE The node type.
 * @param root Pointer to the root node of the tree.
 * @return Pointer to the node with the minimum value.
 */
template <typename NODE>
NODE* bst_minimum(NODE* root) {
    while (root && root->left) root = root->left;
    return root;
}

/**
 * @brief Finds the node with the maximum value in a binary search tree.
 * 
 * @tparam NODE The node type.
 * @param root Pointer to the root node of the tree.
 * @return Pointer to the node with the maximum value.
 */
template <typename NODE>
NODE* bst_maximum(NODE* root) {
    while (root && root->right) root = root->right; // Traverse right to find maximum
    return root; 
}

/**
 * @brief Finds the successor of a given node in a binary search tree.
 * 
 * @tparam NODEP The node type.
 * @param node Pointer to the node for which to find the successor.
 * @return Pointer to the successor node, or nullptr if there is no successor.
 */
template <typename NODEP>
NODEP* successor(NODEP* node) {
    if (node->right) return bst_minimum(node->right); // Successor is the minimum in the right subtree
    NODEP* parent = node->parent; // Start from the parent of the node
    while (parent && node == parent->right) { 
        node = parent;
        parent = parent->parent;
    }
    return parent; 
}

#endif
