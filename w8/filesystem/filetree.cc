#include <algorithm>
#include <climits>
#include <iostream>
#include <sstream>
#include <vector>

// Node class to represent a file or directory
class Node {
public:
  std::string name;
  int size;   // Size of the node (0 for directories)
  bool isDir; // To check if it's a directory
  std::vector<Node *> children;

  Node(std::string name, int size, bool isDir)
      : name(name), size(size), isDir(isDir) {}
};

// Function to recursively build the tree structure from the transcript
Node *readInput(std::istream &is) {
  std::string line;
  Node *root = new Node("/", 0, true);
  Node *current = root;
  std::vector<Node *> dirStack; // Stack to track current directory

  while (std::getline(is, line)) {
    if (line.empty())
      continue;

    // Parse the command and arguments
    std::istringstream iss(line);
    std::string command, arg;
    iss >> command;

    if (command == "cd") {
      iss >> arg;
      if (arg == "/") {
        current = root;
        dirStack.clear();
      } else if (arg == "..") {
        if (!dirStack.empty()) {
          current = dirStack.back();
          dirStack.pop_back();
        }
      } else {
        Node *child = nullptr;
        for (Node *node : current->children) {
          if (node->name == arg && node->isDir) {
            child = node;
            break;
          }
        }
        if (child != nullptr) {
          dirStack.push_back(current); // Push current to stack
          current = child;             // Change current to child
        }
      }
    } else if (command == "ls") {
      int size;
      std::string name;
      while (iss >> size >> name) {
        Node *newNode =
            new Node(name, size, false); // Files are not directories
        current->children.push_back(newNode);
      }
    }
  }

  return root;
}

// Function to print the tree structure
void printNode(Node *node, int lvl = 0) {
  for (int i = 0; i < lvl; ++i)
    std::cout << "| ";
  if (lvl > 0)
    std::cout << "+-";
  std::cout << "(" << node->name << ", size: " << node->size << ")"
            << std::endl;
  for (auto child : node->children)
    printNode(child, lvl + 1);
}

void printTree(std::istream &is) {
  Node *root = readInput(is);
  printNode(root);
}

// Function to compute the total size of all files and directories recursively
int computeSize(Node *node) {
  if (node->isDir) {
    int totalSize = 0;
    for (auto child : node->children) {
      totalSize += computeSize(child);
    }
    node->size = totalSize; // Update directory size
    return totalSize;
  }
  return node->size; // Return file size
}

// Function to return the smallest directory whose size is at least a target
// amount
std::string smallestDir(Node *node, int targetSize, std::string ext = "") {
  std::string smallest;
  int smallestSize = INT_MAX;

  if (node->isDir) {
    for (auto child : node->children) {
      if (child->isDir) {
        if (child->size >= targetSize &&
            (ext.empty() ||
             child->name.substr(child->name.find_last_of('.') + 1) == ext)) {
          if (child->size < smallestSize) {
            smallest = child->name;
            smallestSize = child->size;
          }
        }
        // Recursive call for children directories
        std::string result = smallestDir(child, targetSize, ext);
        if (!result.empty()) {
          // If result is found, you can check size if needed here
        }
      }
    }
  }

  return smallest;
}

// Function to list the files and directories that will be deleted to free up
// space
void listDeleted(Node *node, int targetSize, std::string ext = "") {
  for (auto child : node->children) {
    if (!child->isDir && child->size < targetSize &&
        (ext.empty() ||
         child->name.substr(child->name.find_last_of('.') + 1) == ext)) {
      std::cout << "/" << child->name << std::endl;
    } else if (child->isDir) {
      listDeleted(child, targetSize, ext); // Recursive call for directories
    }
  }
}
