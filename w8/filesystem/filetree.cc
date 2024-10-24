#include "filetree.h"
#include <algorithm>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using std::istream;
using std::string;
using std::vector;

// Only showing the modified Node class for brevity - rest remains the same

class Node {
public:
  string name;
  bool isDirectory;
  int size;
  vector<Node *> children;
  Node *parent;

  Node(string n, bool isDir = false, int s = 0)
      : name(n), isDirectory(isDir), size(s), parent(nullptr) {}

  ~Node() {
    for (Node *child : children) {
      delete child;
    }
  }

  void addChild(Node *child) {
    children.push_back(child);
    child->parent = this;
  }

  // Fixed path construction to avoid double slashes
  string getFullPath() const {
    if (parent == nullptr)
      return "/";

    string path;
    // Build path from child to root
    vector<string> parts;
    const Node *current = this;

    while (current->parent != nullptr) {
      parts.push_back(current->name);
      current = current->parent;
    }

    // Construct path starting with root
    path = "/";
    // Add path components in reverse order
    for (auto it = parts.rbegin(); it != parts.rend(); ++it) {
      path += *it;
      if (it != parts.rend() - 1 || (isDirectory && path != "/")) {
        path += "/";
      }
    }

    return path;
  }
};

// Helper function to get file extension
string getExtension(const string &filename) {
  size_t pos = filename.find_last_of('.');
  if (pos != string::npos) {
    return filename.substr(pos);
  }
  return "";
}

// Parse the command output and build the file tree
Node *readInput(istream &is) {
  Node *root = new Node("/", true);
  Node *currentNode = root;
  string line;

  while (getline(is, line)) {
    if (line.empty())
      continue;

    if (line[0] == '$') {
      std::istringstream iss(line.substr(2));
      string command;
      iss >> command;

      if (command == "cd") {
        string dir;
        iss >> dir;

        if (dir == "/") {
          currentNode = root;
        } else if (dir == "..") {
          if (currentNode->parent) {
            currentNode = currentNode->parent;
          }
        } else {
          for (Node *child : currentNode->children) {
            if (child->name == dir) {
              currentNode = child;
              break;
            }
          }
        }
      }
    } else {
      // Parse ls output
      std::istringstream iss(line);
      int size;
      string name;
      iss >> size >> name;

      // Remove trailing '/' if present
      bool isDir = false;
      if (name.back() == '/') {
        isDir = true;
        name.pop_back();
      }

      Node *newNode = new Node(name, isDir, size);
      currentNode->addChild(newNode);
    }
  }

  return root;
}

void printNodeHelper(Node *node, int lvl = 0) {
  for (int i = 0; i < lvl; i++) {
    std::cout << "| ";
  }
  std::cout << std::endl;

  for (int i = 0; i < lvl - 1; i++) {
    std::cout << "| ";
  }
  if (lvl > 0) {
    std::cout << "+-";
  }
  // Special case for root node - print empty parentheses
  if (node->parent == nullptr) {
    std::cout << "()" << std::endl;
  } else {
    std::cout << "(" << node->name << ")" << std::endl;
  }

  for (Node *child : node->children) {
    printNodeHelper(child, lvl + 1);
  }
}

void printTree(istream &is) {
  Node *root = readInput(is);
  printNodeHelper(root);
  delete root;
}

int computeSizeHelper(Node *node, const string &ext = "") {
  int totalSize = 0;

  // If this is a file, check if it matches the extension filter
  if (!node->isDirectory) {
    if (ext.empty() || getExtension(node->name) == ext) {
      return node->size;
    }
    return 0;
  }

  // For directories, recursively sum up matching files
  for (Node *child : node->children) {
    totalSize += computeSizeHelper(child, ext);
  }
  return totalSize;
}

// Find node by path
Node *findNodeByPath(Node *root, const string &path) {
  if (path == "/" || path.empty())
    return root;

  size_t start = 1;
  Node *current = root;

  while (start < path.length()) {
    size_t end = path.find('/', start);
    if (end == string::npos)
      end = path.length();

    string dirName = path.substr(start, end - start);
    bool found = false;

    for (Node *child : current->children) {
      if (child->name == dirName) {
        current = child;
        found = true;
        break;
      }
    }

    if (!found)
      return nullptr;
    start = end + 1;
  }

  return current;
}

int computeSize(istream &is, string path) {
  Node *root = readInput(is);
  Node *targetNode = findNodeByPath(root, path);
  int result = targetNode ? computeSizeHelper(targetNode) : -1;
  delete root;
  return result;
}

void findSmallestDirHelper(Node *node, int targetSize, const string &ext,
                           string &result, int &smallestValidSize) {
  if (!node->isDirectory)
    return;

  // Calculate size considering only files with matching extension
  int currentSize = computeSizeHelper(node, ext);

  // Skip directories that have zero size for the matching extension
  if (currentSize == 0) {
    return;
  }

  // Update result if this directory is the smallest one meeting the target size
  // so far
  if (currentSize >= targetSize && currentSize < smallestValidSize) {
    smallestValidSize = currentSize;
    result = node->getFullPath();
  }

  // Recursively check all subdirectories
  for (Node *child : node->children) {
    if (child->isDirectory) {
      findSmallestDirHelper(child, targetSize, ext, result, smallestValidSize);
    }
  }
}

string smallestDir(istream &is, int targetSize, string ext) {
  Node *root = readInput(is);
  string result = "";
  int smallestValidSize = std::numeric_limits<int>::max();

  findSmallestDirHelper(root, targetSize, ext, result, smallestValidSize);

  delete root;
  return result;
}

void listDeletedHelper(Node *node, const string &ext,
                       vector<string> &toDelete) {
  if (!node->isDirectory) {
    if (ext.empty() || getExtension(node->name) == ext) {
      toDelete.push_back(node->getFullPath());
    }
    return;
  }

  bool allFilesDeleted = true;
  vector<string> dirContents;

  for (Node *child : node->children) {
    listDeletedHelper(child, ext, dirContents);
    if (!child->isDirectory &&
        (ext.empty() || getExtension(child->name) != ext)) {
      allFilesDeleted = false;
    }
  }

  if (allFilesDeleted || node->children.empty()) {
    // Avoid adding an extra slash for root "/"
    if (node->name == "/") {
      toDelete.push_back(node->getFullPath());
    } else {
      toDelete.push_back(node->getFullPath() + "/");
    }
  }

  toDelete.insert(toDelete.end(), dirContents.begin(), dirContents.end());
}

void listDeleted(istream &is, int targetSize, string ext) {
  Node *root = readInput(is);
  string dirToDelete =
      smallestDir(is, targetSize, ext); // Find the directory to delete
  Node *targetNode = findNodeByPath(
      root, dirToDelete); // Get the node corresponding to that directory

  if (targetNode) {
    vector<string> deletedItems;
    listDeletedHelper(targetNode, ext, deletedItems);

    // Sort and remove duplicates
    std::sort(deletedItems.begin(), deletedItems.end());
    deletedItems.erase(std::unique(deletedItems.begin(), deletedItems.end()),
                       deletedItems.end());

    for (const string &item : deletedItems) {
      std::cout << item << std::endl;
    }
  }

  delete root; // Clean up the tree
}
