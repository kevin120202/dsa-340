#include <iostream>
#include <set>

class TreeNode {
public:
    TreeNode *left, *right;
    int value;

    TreeNode(int val) : left(nullptr), right(nullptr), value(val) {}
};

void inOrder(TreeNode* node, std::set<int>& uniqueValues) {
    if (!node) return;
    inOrder(node->left, uniqueValues);
    uniqueValues.insert(node->value);
    inOrder(node->right, uniqueValues);
}

bool secondsmallest(TreeNode *root, int &val) {
    std::set<int> uniqueValues;
    inOrder(root, uniqueValues);

    if (uniqueValues.size() < 2) {
        return false; // Not enough unique values
    }

    auto it = uniqueValues.begin();
    ++it; // Move to the second smallest value
    val = *it;
    return true; // Found second smallest
}







