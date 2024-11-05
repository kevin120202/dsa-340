/************************************************************************************
 ** NIU CSCI 340 Section 2 * Assignment #7 Kevin Dela Paz - z2017241 *
 **
 * I certify that everything I am submitting is either provided by the professor
 *for use in * the assignment, or work done by me personally. I understand that
 *if I am caught submitting * the work of others (including StackOverflow or
 *ChatGPT) as my own is an act of Academic * Misconduct and will be punished as
 *such. *
 ************************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <queue>
#include "nodes.h" 
#include "bintree.h"
#include "xml.h"

using namespace std;

/**
 * @brief Converts an XML element to a string representation, either as an opening or closing tag.
 * 
 * @param element The XML element to convert to a string.
 * @param opening Boolean flag indicating whether to generate an opening tag (true) or closing tag (false).
 * @return A string representation of the XML.
 */
std::string to_string(const xml_element &element, bool opening) {
    std::ostringstream output;
    // Check if the element is plain text or a tag
    if (element.type == xml_type::plain) {
        output << element.fulltext;  
    } else {
        if (opening) {
            output << "<" << element.name; 
            // Append each attribute in the format: key="value"
            for (const auto &[key, value] : element.attrs) {
                output << " " << key << "=\"" << value << "\"";
            }
            output << ">";
        } else {
            output << "</" << element.name << ">"; 
        }
    }
    return output.str();
}

/**
 * @brief Finds all nodes with the specified tag name in the XML tree.
 * 
 * @param root The root node of the XML tree.
 * @param name The name of the tag to search for.
 * @return A vector of pointers to XML nodes that match the tag name.
 */
std::vector<XMLNODE *> xml_find_by_name(XMLNODE *root, const std::string &name) {
    std::vector<XMLNODE *> result;
    // Preorder traversal to search for matching nodes by tag name
    preorder(root, [&result, &name](XMLNODE *node) {
        if (node->data.type == xml_type::tag && node->data.name == name) {
            result.push_back(node);
        }
    });
    return result;
}

/**
 * @brief Finds all nodes that contain the specified attribute.
 * 
 * @param root The root node of the XML tree.
 * @param attrname The name of the attribute to search for.
 * @return A vector of pointers to XML nodes that contain the specified attribute.
 */
std::vector<XMLNODE *> xml_find_with_attr(XMLNODE *root, const std::string &attrname) {
    std::vector<XMLNODE *> result;
    // Preorder traversal to search for nodes with the specified attribute
    preorder(root, [&result, &attrname](XMLNODE *node) {
        if (node->data.attrs.find(attrname) != node->data.attrs.end()) {
            result.push_back(node);  // Add node if attribute is found
        }
    });
    return result;
}

/**
 * @brief Adds a new XML element to the XML tree.
 * 
 * @param element The XML element to add to the tree.
 * @param state The current XML tree state.
 * @param verbose Flag for verbose output.
 * @return 0 on successful addition.
 */
int xml_add_node(const xml_element &element, xml_tree_state &state, bool verbose) {
    XMLNODE *new_node = new XMLNODE(element);

    // Check if the tree has a root node
    if (!state.root) {
        state.root = state.cur = new_node;
    } else if (!state.cur->data.closed) {
        // Add new node as a child
        new_node->parent = state.cur;
        if (!state.cur->left) {
            state.cur->left = new_node;
        } else {
            XMLNODE *sibling = state.cur->left;
            while (sibling->right) {
                sibling = sibling->right;
            }
            sibling->right = new_node;
        }
    } else {
        // Add new node as a sibling to the current node
        new_node->parent = state.cur->parent;
        state.cur->right = new_node;
    }
    state.cur = new_node;
    return 0;
}

/**
 * @brief Closes an open XML tag in the XML tree.
 * 
 * @param name The name of the tag to close.
 * @param state The current XML tree state.
 * @param verbose Flag for verbose output.
 * @return 0 if successfully closed, 1 if an error occurs.
 */
int xml_close_tag(const std::string name, xml_tree_state &state, bool verbose) {
    // Check if the current node matches the tag to close
    if (state.cur && state.cur->data.name == name) {
        state.cur->data.closed = true; 
        return 0;
    }

    // Traverse up the tree to find an open tag with the matching name
    XMLNODE *currentParent = (state.cur == nullptr) ? nullptr : state.cur->parent;

    while (currentParent) {
        if (currentParent->data.name == name) {
            currentParent->data.closed = true;
            state.cur = currentParent;
            return 0;
        }
        currentParent = tilted_find_parent(currentParent);
    }

    // No matching open tag found; report error if verbose
    if (verbose) {
        std::cout << "Error: No matching open tag for " << name << std::endl;
    }

    return 1;
}

/**
 * @brief Handles an XML tag, determining if it's an opening or closing tag and processing it accordingly.
 * 
 * @param tagstring The XML tag string to handle.
 * @param state The current XML tree state.
 * @param verbose Flag for verbose output.
 * @return Error count; 0 if no errors.
 */
int xml_handle_tag(std::string &tagstring, xml_tree_state &state, bool verbose) {
    if (tagstring.empty() || tagstring.front() != '<' || tagstring.back() != '>') {
        if (verbose) {
            std::cerr << "ERROR: Invalid tag format: " << tagstring << std::endl;
        }
        return 1;
    }

    // Determine if this is a closing tag
    bool isClosingTag = tagstring[1] == '/';
    std::string tagContent = tagstring.substr(isClosingTag ? 2 : 1, tagstring.size() - (isClosingTag ? 3 : 2));
    std::istringstream tagStream(tagContent);
    std::string tagName;
    tagStream >> tagName;

    if (tagName.empty()) {
        if (verbose) {
            std::cerr << "ERROR: Empty tag name in: " << tagstring << std::endl;
        }
        return 1;
    }

    // If it's a closing tag, attempt to close it
    if (isClosingTag) {
        return xml_close_tag(tagName, state, verbose);
    }

    // Parse attributes if it’s an opening tag
    std::map<std::string, std::string> attributeMap;
    std::string remainingContent;
    getline(tagStream, remainingContent);

    int attributeErrors = xml_handle_attributes(remainingContent, attributeMap);
    if (attributeErrors > 0 && verbose) {
        std::cerr << "ERROR: Invalid attributes in tag: " << tagstring << std::endl;
    }

    // Add new element as a node
    xml_element xmlElem(xml_type::tag, tagName, tagstring, attributeMap);
    return xml_add_node(xmlElem, state, verbose);
}

/**
 * @brief Handles plain text content within XML and adds it to the XML tree.
 * 
 * @param plaintext The plain text string.
 * @param state The current XML tree state.
 * @param verbose Flag for verbose output.
 * @return 0 on success.
 */
int xml_handle_plaintext(std::string &plaintext, xml_tree_state &state, bool verbose) {
    xml_element element(xml_type::plain, "", plaintext, {});
    return xml_add_node(element, state, verbose);
}

/**
 * @brief Parses and handles attributes within an XML tag.
 * 
 * @param input The attribute string to parse.
 * @param attrs Map to store parsed attributes.
 * @param verbose Flag for verbose output.
 * @return Number of valid attributes processed.
 */
int xml_handle_attributes(const std::string &input, std::map<std::string, std::string> &attrs, bool verbose) {
    int validCount = 0;
    size_t currentIndex = 0;

    // Skip leading whitespace
    while (currentIndex < input.size() && isspace(input[currentIndex])) {
        ++currentIndex;
    }

    // Parse each attribute in the input
    while (currentIndex < input.size()) {
        std::string attributeKey;

        // Extract attribute key before the '='
        while (currentIndex < input.size() && isalnum(input[currentIndex])) {
            attributeKey += input[currentIndex];
            ++currentIndex;
        }

        // Look for the '=' and ensure the next character is a quote
        if (currentIndex < input.size() && input[currentIndex] == '=') {
            ++currentIndex;
            if (currentIndex < input.size() && input[currentIndex] == '"') {
                ++currentIndex;
                std::string attributeValue;

                // Extract attribute value within quotes
                while (currentIndex < input.size() && input[currentIndex] != '"') {
                    attributeValue += input[currentIndex];
                    ++currentIndex;
                }

                // Store valid key-value pairs
                if (currentIndex < input.size() && input[currentIndex] == '"') {
                    ++currentIndex;
                    attrs[attributeKey] = attributeValue;
                    validCount++;
                } else {
                    if (verbose) std::cout << "Error: Missing closing quote.\n";
                    return 0;
                }
            } else {
                if (verbose) std::cout << "Error: Missing opening quote.\n";
                return 0;
            }
        } else {
            if (verbose) std::cout << "Error: Invalid attribute format.\n";
            return 0;
        }

        // Skip whitespace between attributes
        while (currentIndex < input.size() && isspace(input[currentIndex])) {
            ++currentIndex;
        }
    }
    return validCount;
}

/**
 * @brief Recursively prints the XML subtree starting from the given node.
 * 
 * @param root The root node of the subtree to print.
 * @param ost The output stream to print to.
 */
void xml_print_subtree(XMLNODE *root, std::ostream &ost) {
    if (!root) return;

    // Print opening tag or plain text content
    if (root->data.type == xml_type::tag) {
        ost << to_string(root->data, true);
    } else {
        ost << root->data.fulltext;
        return;
    }

    // Recursively print children nodes
    for (XMLNODE *childNode = root->left; childNode; childNode = childNode->right) {
        xml_print_subtree(childNode, ost);
    }

    // Print closing tag if applicable
    if (root->data.type == xml_type::tag) {
        ost << to_string(root->data, false);
    }
}
