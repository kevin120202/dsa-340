/************************************************************************************
 ** NIU CSCI 340 Section 2 * Assignment #7 Kevin Dela Paz - z2017241 *
 **
 * I certify that everything I am submitting is either provided by the professor
 *for use in * the assignment, or work done by me personally. I understand that
 *if I am caught submitting * the work of others (including StackOverflow or
 *ChatGPT) as my own is an act of Academic * Misconduct and will be punished as
 *such. *
 ************************************************************************************/

// Implement a simple parser for XML that uses a tilted binary tree for storage
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <regex>

#include "nodes.h" // supplied node declarations
#include "bintree.h"
#include "xml.h"

// Convert XML element to a string
std::string to_string(const xml_element &element, bool opening) {
    std::ostringstream oss;
    if (element.type == xml_type::tag) {
        if (opening) {
            oss << "<" << element.name;
            for (const auto& [key, value] : element.attrs) {
                oss << " " << key << "=\"" << value << "\"";
            }
            oss << ">";
        } else {
            oss << "</" << element.name << ">";
        }
    } else { // plain text
        oss << element.fulltext;
    }
    return oss.str();
}

// Find all nodes with a specific tag name
std::vector<XMLNODE *> xml_find_by_name(XMLNODE *root, const std::string &name) {
    std::vector<XMLNODE *> matches;
    preorder(root, [&matches, &name](XMLNODE *node) {
        if (node->data.name == name) {
            matches.push_back(node);
        }
    });
    return matches;
}

// Find all nodes with a specific attribute
std::vector<XMLNODE *> xml_find_with_attr(XMLNODE *root, const std::string &attrname) {
    std::vector<XMLNODE *> matches;
    preorder(root, [&matches, &attrname](XMLNODE *node) {
        if (node->data.attrs.find(attrname) != node->data.attrs.end()) {
            matches.push_back(node);
        }
    });
    return matches;
}

// Add node to XML tree based on the current state
int xml_add_node(const xml_element &element, xml_tree_state &state, bool verbose) {
    XMLNODE *newNode = new XMLNODE(element);
    if (!state.root) {
        state.root = newNode;
        state.cur = newNode;
        return 0;
    }
    if (!state.cur) {
        if (verbose) std::cerr << "Error: Current node is nullptr." << std::endl;
        delete newNode;
        return 1;
    }
    if (state.cur->data.type == xml_type::plain || state.cur->data.closed) {
        state.cur->right = newNode;
    } else {
        state.cur->left = newNode;
    }
    state.cur = newNode;
    return 0;
}

// Close a tag in the XML tree
int xml_close_tag(const std::string name, xml_tree_state &state, bool verbose) {
    if (!state.cur || state.cur->data.name != name) {
        XMLNODE* parent = tilted_find_parent(state.cur);
        if (parent && parent->data.name == name) {
            state.cur = parent;
        } else {
            if (verbose) std::cerr << "Error: Mismatched closing tag for " << name << "." << std::endl;
            return 1;
        }
    }
    state.cur->data.closed = true;
    state.cur = tilted_find_parent(state.cur);
    return 0;
}

// Handle plain text and add it to the XML tree
int xml_handle_plaintext(std::string &plaintext, xml_tree_state &state, bool verbose) {
    xml_element textElement;
    textElement.type = xml_type::plain;
    textElement.fulltext = plaintext;
    return xml_add_node(textElement, state, verbose);
}


int xml_handle_attributes(const std::string &input, std::map<std::string, std::string> &attrs, bool verbose) {
    std::regex attr_regex(R"(\s*(\w+)\s*=\s*\"([^\"]*)\")");
    std::sregex_iterator begin(input.begin(), input.end(), attr_regex);
    std::sregex_iterator end;

    int validAttrs = 0;
    std::string parsed_portion;

    for (auto it = begin; it != end; ++it) {
        std::smatch match = *it;
        std::string key = match[1].str();
        std::string value = match[2].str();

        // Add key-value pair to the attributes map
        attrs[key] = value;
        validAttrs++;

        // Append matched part to track processed parts of the input
        parsed_portion += match.str();
    }

    // Check for any remaining unprocessed text in input
    if (parsed_portion.size() < input.size()) {
        std::string remaining = input.substr(parsed_portion.size());
        if (verbose) {
            std::cerr << "ERROR: xml_handle_attributes done. Invalid string remaining \""
                      << remaining << "\"" << std::endl;
        }
    }

    // Check if no valid attributes were found and quotes or equals are present in input
    if (validAttrs == 0 && (input.find('=') != std::string::npos || input.find('"') != std::string::npos)) {
        if (verbose) {
            std::cerr << "ERROR: xml_handle_attributes tag ended before value's quotation ended." << std::endl;
        }
    }

    return validAttrs;
}


// Handle XML tag (opening or closing)
int xml_handle_tag(std::string &tagstring, xml_tree_state &state, bool verbose) {
    if (tagstring.empty() || tagstring[0] != '<' || tagstring.back() != '>') {
        if (verbose) std::cerr << "Error: Invalid tag format." << std::endl;
        return 1;
    }

    bool isClosing = tagstring[1] == '/';
    size_t nameStart = isClosing ? 2 : 1;
    size_t nameEnd = tagstring.find(' ', nameStart);
    std::string name = tagstring.substr(nameStart, nameEnd - nameStart);

    if (isClosing) {
        return xml_close_tag(name, state, verbose);
    }

    xml_element element;
    element.type = xml_type::tag;
    element.name = name;

    size_t attrStart = tagstring.find(' ', nameEnd) + 1;
    if (attrStart < tagstring.size() - 1) {
        std::string attrs = tagstring.substr(attrStart, tagstring.size() - attrStart - 1);
        xml_handle_attributes(attrs, element.attrs, verbose);
    }

    return xml_add_node(element, state, verbose);
}

// Print the XML subtree rooted at `root`
void xml_print_subtree(XMLNODE *root, std::ostream &ost) {
    if (!root) return;

    ost << to_string(root->data, true);
    if (root->left) xml_print_subtree(root->left, ost);
    ost << to_string(root->data, false);
    if (root->right) xml_print_subtree(root->right, ost);
}
