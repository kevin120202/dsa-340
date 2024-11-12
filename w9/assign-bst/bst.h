#ifndef NIU_CSCI340_BST_H_IMPL
#define NIU_CSCI340_BST_H_IMPL

#include "bst.decl.h"
#include "bintree.h"
#include <iostream>
#include <algorithm>

template <typename NODE, typename T>
NODE* bst_find(NODE* root, const T& value) {
    if (!root) return nullptr;
    if (root->data == value) return root;
    return (value < root->data) ? bst_find(root->left, value) : bst_find(root->right, value);
}


// Insert a node with a specific value
template <typename NODEP, typename T>
NODEP* bst_insert(NODEP*& root, const T& value) {
    if (!root) {
        root = new NODEP(value);
        return root;
    }
    NODEP* parent = nullptr;
    NODEP* current = root;
    while (current) {
        parent = current;
        if (value < current->data) current = current->left;
        else if (value > current->data) current = current->right;
        else return nullptr;  // Value already exists
    }

    NODEP* newNode = new NODEP(value);
    newNode->parent = parent;
    if (value < parent->data) parent->left = newNode;
    else parent->right = newNode;
    return newNode;
}

// Remove node and print tree state after each removal
template <typename NODEP, typename T>
NODEP* bst_remove_value(NODEP*& root, const T& value) {
    NODEP* nodeToDelete = bst_find(root, value);
    if (!nodeToDelete) return nullptr;  // Node not found

    // Case 1: Node has no children
    if (!nodeToDelete->left && !nodeToDelete->right) {
        if (nodeToDelete->parent) {
            if (nodeToDelete->parent->left == nodeToDelete) 
                nodeToDelete->parent->left = nullptr;
            else 
                nodeToDelete->parent->right = nullptr;
        } else {
            root = nullptr;
        }
    }
    // Case 2: Node has two children
    else if (nodeToDelete->left && nodeToDelete->right) {
        NODEP* succ = successor(nodeToDelete);
        if (succ) {
            nodeToDelete->data = succ->data;  // Copy successor's data
            if (succ->parent->left == succ) 
                succ->parent->left = succ->right;
            else 
                succ->parent->right = succ->right;
            
            if (succ->right)
                succ->right->parent = succ->parent;

            delete succ;
        }
    }
    // Case 3: Node has one child
    else {
        NODEP* child = nodeToDelete->left ? nodeToDelete->left : nodeToDelete->right;
        child->parent = nodeToDelete->parent;
        if (nodeToDelete->parent) {
            if (nodeToDelete->parent->left == nodeToDelete) 
                nodeToDelete->parent->left = child;
            else 
                nodeToDelete->parent->right = child;
        } else {
            root = child;  // Node to delete is the root node
        }
    }

    delete nodeToDelete;

    // Output tree state after deletion
    std::cout << "  preorder:   "; preorder(root, [](NODEP* node) { std::cout << node->data << " "; }); std::cout << "\n";
    std::cout << "  inorder:    "; inorder(root, [](NODEP* node) { std::cout << node->data << " "; }); std::cout << "\n";
    std::cout << "  postorder:  "; postorder(root, [](NODEP* node) { std::cout << node->data << " "; }); std::cout << "\n";
    std::cout << "  levelorder: "; levelorder(root, [](NODEP* node) { std::cout << node->data << " "; }); std::cout << "\n";
    std::cout << "  count: " << count(root)
              << "; root: " << (root ? std::to_string(root->data) : "none")
              << "; min: " << (root ? std::to_string(bst_minimum(root)->data) : "none")
              << "; max: " << (root ? std::to_string(bst_maximum(root)->data) : "none")
              << "; height: " << height(root)
              << "; is_bst: " << (is_bst(root) ? "true" : "false") << "\n";

    return root;
}

// Check if the tree is a BST
template <typename NODE>
bool is_bst_helper(NODE* root, NODE* minNode, NODE* maxNode) {
    if (!root) return true;
    if ((minNode && root->data <= minNode->data) || (maxNode && root->data >= maxNode->data)) return false;
    return is_bst_helper(root->left, minNode, root) && is_bst_helper(root->right, root, maxNode);
}

template <typename NODE>
bool is_bst(NODE* root) {
    return is_bst_helper(root, static_cast<NODE*>(nullptr), static_cast<NODE*>(nullptr));
}


// Find the minimum value node
template <typename NODE>
NODE* bst_minimum(NODE* root) {
    while (root && root->left) root = root->left;
    return root;
}

// Find the maximum value node
template <typename NODE>
NODE* bst_maximum(NODE* root) {
    while (root && root->right) root = root->right;
    return root;
}

// Find the successor of a node
template <typename NODEP>
NODEP* successor(NODEP* node) {
    if (node->right) return bst_minimum(node->right);
    NODEP* parent = node->parent;
    while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

#endif
