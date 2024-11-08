#include "treenode.h"
#include <queue>
#include <algorithm>

// Check if two binary trees are the same
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;             // Both trees are empty
    if (!p || !q) return false;            // One tree is empty, the other isn't
    if (p->value != q->value) return false;    // Values are different
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right); // Check subtrees
}

// Check if two binary trees are symmetric
bool isSymmetric(TreeNode* left, TreeNode* right) {
    if (!left && !right) return true;      // Both subtrees are empty
    if (!left || !right) return false;     // One subtree is empty, the other isn't
    if (left->value != right->value) return false;  // Values are different
    return isSymmetric(left->left, right->right) && isSymmetric(left->right, right->left);
}

bool isSymmetricTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;             
    if (!p || !q) return false;            
    return isSymmetric(p, q);              
}

// Check if one binary tree is a subtree of another tree
bool isSubtree(TreeNode* s, TreeNode* t) {
    if (!s) return false;
    if (isSameTree(s, t)) return true;     
    return isSubtree(s->left, t) || isSubtree(s->right, t);
}

bool isOneTreePartOfAnother(TreeNode* p, TreeNode* q) {
    if (!p || !q) return false;            // If both trees are empty, return false
    return isSubtree(p, q) || isSubtree(q, p);
}

// Check if two binary trees are the same heap
bool isMaxHeap(TreeNode* root) {
    if (!root) return true;                
    if (root->left && root->left->value > root->value) return false;
    if (root->right && root->right->value > root->value) return false;
    return isMaxHeap(root->left) && isMaxHeap(root->right);
}

bool isSameHeap(TreeNode* p, TreeNode* q) {
    if (!isSameTree(p, q)) return false; 
    return isMaxHeap(p) && isMaxHeap(q);   
}

// Check if two binary trees have the same width
int getWidth(TreeNode* root) {
    if (!root) return 0;
    int maxWidth = 0;
    std::queue<std::pair<TreeNode*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        int levelSize = q.size();
        int leftmost = q.front().second;
        int rightmost = q.back().second;
        maxWidth = std::max(maxWidth, rightmost - leftmost + 1);

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front().first;
            int index = q.front().second;
            q.pop();

            if (node->left) q.push({node->left, 2 * index});
            if (node->right) q.push({node->right, 2 * index + 1});
        }
    }
    return maxWidth;
}

bool ofSameWidth(TreeNode* p, TreeNode* q) {
    return getWidth(p) == getWidth(q);
}
