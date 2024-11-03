#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include "nodes.h"
#include "bintree.h" 
#include "xml.h" 

// xml_handle_tag
int xml_handle_tag(std::string &tagstring, xml_tree_state &state, bool verbose) {
    if (tagstring.empty() || tagstring.size() < 3 || tagstring.front() != '<' || tagstring.back() != '>') {
        if (verbose) std::cerr << "Error: Invalid tag format: " << tagstring << std::endl;
        return 1;
    }

    int errors = 0;
    bool is_closing_tag = (tagstring[1] == '/');
    std::string content = tagstring.substr(1, tagstring.size() - 2);

    if (is_closing_tag) {
        std::string tag_name = content.substr(1);  // Skip '/'
        errors += xml_close_tag(tag_name, state, verbose);
    } else {
        std::string::size_type space_pos = content.find(' ');
        std::string tag_name = (space_pos == std::string::npos) ? content : content.substr(0, space_pos);
        
        xml_element element;
        element.type = tag;
        element.name = tag_name;

        if (space_pos != std::string::npos) {
            std::string attr_str = content.substr(space_pos + 1);
            errors += xml_handle_attributes(attr_str, element.attrs, verbose);
        }
        
        errors += xml_add_node(element, state, verbose);
    }

    return errors;
}

// xml_handle_attributes
int xml_handle_attributes(const std::string &input, std::map<std::string, std::string> &attrs, bool verbose) {
    int errors = 0;
    std::string::size_type pos = 0;

    while (pos < input.size()) {
        std::string::size_type equals_pos = input.find('=', pos);
        if (equals_pos == std::string::npos || equals_pos == pos || input[equals_pos + 1] != '"') {
            if (verbose) std::cerr << "Error: Invalid attribute format in \"" << input << "\"" << std::endl;
            return ++errors;
        }

        std::string key = input.substr(pos, equals_pos - pos);
        std::string::size_type quote_end = input.find('"', equals_pos + 2);
        if (quote_end == std::string::npos) {
            if (verbose) std::cerr << "Error: Missing closing quote for attribute value." << std::endl;
            return ++errors;
        }

        std::string value = input.substr(equals_pos + 2, quote_end - (equals_pos + 2));
        attrs[key] = value;
        pos = quote_end + 1;
    }

    return errors;
}

// xml_handle_plaintext
int xml_handle_plaintext(std::string &plaintext, xml_tree_state &state, bool verbose) {
    xml_element element;
    element.type = plain;
    element.fulltext = plaintext;
    return xml_add_node(element, state, verbose);
}

// xml_add_node
int xml_add_node(const xml_element &element, xml_tree_state &state, bool verbose) {
    if (!state.cur) {
        state.root = new NodeLRP<xml_element>(element);
        state.cur = state.root;
        return 0;
    }

    if (state.cur->data.type == plain || state.cur->data.closed) {
        state.cur->right = new NodeLRP<xml_element>(element);
        state.cur->right->parent = state.cur->parent;
        state.cur = state.cur->right;
    } else {
        state.cur->left = new NodeLRP<xml_element>(element);
        state.cur->left->parent = state.cur;
        state.cur = state.cur->left;
    }

    return 0;
}

// xml_close_tag
int xml_close_tag(const std::string name, xml_tree_state &state, bool verbose) {
    if (!state.cur || state.cur->data.name != name) {
        if (verbose) std::cerr << "Error: Closing tag does not match the current open tag: " << name << std::endl;
        return 1;
    }

    state.cur->data.closed = true;
    state.cur = state.cur->parent;
    return 0;
}

// xml_find_by_name
std::vector<NodeLRP<xml_element>*> xml_find_by_name(NodeLRP<xml_element>* root, const std::string &name) {
    std::vector<NodeLRP<xml_element>*> matching_nodes;

    if (!root) return matching_nodes;
    if (root->data.name == name) matching_nodes.push_back(root);

    auto left_matches = xml_find_by_name(root->left, name);
    auto right_matches = xml_find_by_name(root->right, name);

    matching_nodes.insert(matching_nodes.end(), left_matches.begin(), left_matches.end());
    matching_nodes.insert(matching_nodes.end(), right_matches.begin(), right_matches.end());

    return matching_nodes;
}

// xml_find_with_attr
std::vector<NodeLRP<xml_element>*> xml_find_with_attr(NodeLRP<xml_element>* root, const std::string &attrname) {
    std::vector<NodeLRP<xml_element>*> matching_nodes;

    if (!root) return matching_nodes;
    if (root->data.attrs.find(attrname) != root->data.attrs.end()) {
        matching_nodes.push_back(root);
    }

    auto left_matches = xml_find_with_attr(root->left, attrname);
    auto right_matches = xml_find_with_attr(root->right, attrname);

    matching_nodes.insert(matching_nodes.end(), left_matches.begin(), left_matches.end());
    matching_nodes.insert(matching_nodes.end(), right_matches.begin(), right_matches.end());

    return matching_nodes;
}

// to_string
std::string to_string(const xml_element &element, bool opening) {
    std::ostringstream output;

    if (element.type == tag) {
        if (opening) {
            output << "<" << element.name;
            for (const auto& [key, value] : element.attrs) {
                output << " " << key << "=\"" << value << "\"";
            }
            output << ">";
        } else {
            output << "</" << element.name << ">";
        }
    } else {
        output << element.fulltext;
    }

    return output.str();
}

// xml_print_subtree
void xml_print_subtree(NodeLRP<xml_element>* root, std::ostream &ost) {
    if (!root) return;
    
    ost << to_string(root->data, true);
    if (root->left) xml_print_subtree(root->left, ost);
    ost << to_string(root->data, false);
    
    if (root->right) xml_print_subtree(root->right, ost);
}

