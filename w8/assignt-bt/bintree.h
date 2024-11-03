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
 * @brief Performs a preorder traversal on a binary tree.
 * 
 * This function visits the current node first, then the left subtree, 
 * and finally the right subtree, applying the given function to each node.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @tparam FN Type of the function to apply to each node.
 * @param root Pointer to the root node of the binary tree.
 * @param fn Function to apply to each node during traversal.
 */
template <typename BINTREENODE, typename FN>
void preorder(BINTREENODE* root, FN fn) {
    if (root) {
        fn(root);                    // Process the current node
        preorder(root->left, fn);    // Visit left subtree
        preorder(root->right, fn);   // Visit right subtree
    }
}

/**
 * @brief Performs an inorder traversal on a binary tree.
 * 
 * This function visits the left subtree first, then the current node, 
 * and finally the right subtree, applying the given function to each node.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @tparam FN Type of the function to apply to each node.
 * @param root Pointer to the root node of the binary tree.
 * @param fn Function to apply to each node during traversal.
 */
template <typename BINTREENODE, typename FN>
void inorder(BINTREENODE* root, FN fn) {
    if (root) {
        inorder(root->left, fn);     // Visit left subtree
        fn(root);                    // Process the current node
        inorder(root->right, fn);    // Visit right subtree
    }
}

/**
 * @brief Performs a postorder traversal on a binary tree.
 * 
 * This function visits the left subtree first, then the right subtree, 
 * and finally the current node, applying the given function to each node.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @tparam FN Type of the function to apply to each node.
 * @param root Pointer to the root node of the binary tree.
 * @param fn Function to apply to each node during traversal.
 */
template <typename BINTREENODE, typename FN>
void postorder(BINTREENODE* root, FN fn) {
    if (root) {
        postorder(root->left, fn);   // Visit left subtree
        postorder(root->right, fn);  // Visit right subtree
        fn(root);                    // Process the current node
    }
}

/**
 * @brief Performs a level-order traversal on a binary tree.
 * 
 * This function visits nodes level by level from top to bottom, applying 
 * the given function to each node. It uses a queue to manage the traversal.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @tparam FN Type of the function to apply to each node.
 * @param root Pointer to the root node of the binary tree.
 * @param fn Function to apply to each node during traversal.
 */
template <typename BINTREENODE, typename FN>
void levelorder(BINTREENODE* root, FN fn) {
    if (!root) return;
    std::queue<BINTREENODE*> q;
    q.push(root);

    while (!q.empty()) {
        BINTREENODE* current = q.front();
        q.pop();
        fn(current);  // Process the current node

        if (current->left) q.push(current->left);   // Add left child to queue
        if (current->right) q.push(current->right); // Add right child to queue
    }
}

// /**
//  * @brief Deletes all nodes in a binary tree.
//  * 
//  * This function recursively deletes each node in the binary tree, starting 
//  * from the leaves and moving up to the root, freeing all allocated memory.
//  * 
//  * @tparam BINTREENODE Type of the binary tree node.
//  * @param root Pointer to the root node of the binary tree.
//  */
// template <typename BINTREENODE>
// void delete_tree(BINTREENODE* root) {
//     if (root) {
//         delete_tree(root->left);   // Delete left subtree
//         delete_tree(root->right);  // Delete right subtree
//         delete root;               // Delete the current node
//     }
// }


/**
 * @brief Returns all direct children of the given node in a tilted binary tree.
 * 
 * This function gathers and returns a vector of pointers to all direct children of 
 * the specified node in a tilted binary tree. In this tree structure, the left 
 * pointer represents the first child, and the right pointer represents the next sibling.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @param node Pointer to the node whose children we want to gather.
 * @return std::vector<BINTREENODE*> A vector containing pointers to all direct children.
 * If the node is nullptr or a leaf node (no children), returns an empty vector.
 */
template <typename BINTREENODE>
std::vector<BINTREENODE*> tilted_get_children(BINTREENODE* node) {
    std::vector<BINTREENODE*> children;
    
    // If the node is nullptr or has no children, return an empty vector.
    if (!node || !node->left) return children;

    // Start with the left child (first child)
    BINTREENODE* child = node->left;
    
    // Traverse through the siblings, adding each one to the children vector.
    while (child) {
        children.push_back(child);
        child = child->right; // Move to the next sibling
    }

    return children;
}

// template <typename BINTREENODE>
// BINTREENODE* tilted_find_parent(BINTREENODE *node) {
//     if (!node || !node->parent) return nullptr;

//     BINTREENODE* ancestor = node->parent;

//     // Traverse upward in the tree hierarchy
//     while (ancestor) {
//         // Check if the current ancestor has this node in its "tilted children" (right siblings of the left child)
//         BINTREENODE* child = ancestor->left;

//         while (child) {
//             if (child == node) {
//                 return ancestor;
//             }
//             child = child->right;  // Move to the next sibling
//         }

//         ancestor = ancestor->parent;  // Move up to the next ancestor
//     }

//     return nullptr;  // If no parent found
// }

/**
 * @brief Finds the tilted parent of a node in a tilted binary tree.
 * 
 * This function searches for the real parent of a given node in the tilted binary
 * tree structure, where the left pointer represents the first child and the right
 * pointer represents the next sibling.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @param node Pointer to the node whose tilted parent we want to find.
 * @return BINTREENODE* Pointer to the tilted parent node, or nullptr if no parent is found.
 */
template <typename BINTREENODE>
BINTREENODE* tilted_find_parent(BINTREENODE* node) {
    if (!node || !node->parent) return nullptr;

    BINTREENODE* parent = node->parent;

    // If this node is the left (first) child of its parent, then parent is the tilted parent
    if (parent->left == node) {
        return parent;
    }

    // Otherwise, move up through the siblings to find the tilted parent
    BINTREENODE* sibling = parent->left;
    while (sibling && sibling->right != node) {
        sibling = sibling->right;
    }

    return (sibling && sibling->right == node) ? parent : nullptr;
}


/**
 * @brief Performs a level-order traversal on a tilted binary tree.
 * 
 * This function visits nodes level by level in a tilted binary tree, where each 
 * node can have multiple children. The left pointer represents the first child, 
 * and the right pointer represents the next sibling. The provided function `fn` 
 * is applied to each visited node.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @tparam FN Type of the function to apply to each node.
 * @param root Pointer to the root node of the tilted binary tree.
 * @param fn Function to apply to each node during traversal.
 */
template <typename BINTREENODE, typename FN>
void tilted_levelorder(BINTREENODE* root, FN fn) {
    if (!root) return; // If root is nullptr, there’s nothing to traverse.

    std::queue<BINTREENODE*> q;
    q.push(root);

    while (!q.empty()) {
        BINTREENODE* current = q.front();
        q.pop();

        // Apply the provided function to the current node.
        fn(current);

        // Traverse all children of the current node.
        BINTREENODE* child = current->left;
        while (child) {
            q.push(child);      // Enqueue each child node
            child = child->right; // Move to the next sibling
        }
    }
}

// Delete Tree
template <typename BINTREENODE>
void delete_tree(BINTREENODE *&node) {
    if (node) {
        delete_tree(node->left); // Recursively delete left subtree
        delete_tree(node->right); // Recursively delete right subtree
        delete node; // Delete the current node
        node = nullptr;
    }
}

#endif

