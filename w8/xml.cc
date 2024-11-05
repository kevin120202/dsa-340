// Implement a simple parser for XML that uses a tilted binary tree for storage
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

std::string to_string(const xml_element &element, bool opening) {
    std::ostringstream oss;
    if (element.type == xml_type::plain) {
        oss << element.fulltext;
    } else {
        if (opening) {
            oss << "<" << element.name;
            for (const auto &[key, value] : element.attrs) {
                oss << " " << key << "=\"" << value << "\"";
            }
            oss << ">";
        } else {
            oss << "</" << element.name << ">";
        }
    }
    return oss.str();
  //return "";
}

std::vector <XMLNODE *> xml_find_by_name(XMLNODE * root, const std::string &name) {
    std::vector<XMLNODE *> result;
    preorder(root, [&result, &name](XMLNODE *node) {
        if (node->data.type == xml_type::tag && node->data.name == name) {
            result.push_back(node);
        }
    });
    return result;
  //return {};
}

std::vector <XMLNODE *> xml_find_with_attr(XMLNODE * root, const std::string &attrname) {
	std::vector<XMLNODE *> result;
    preorder(root, [&result, &attrname](XMLNODE *node) {
        if (node->data.attrs.find(attrname) != node->data.attrs.end()) {
            result.push_back(node);
        }
    });
    return result;
    
  //return {};
}

int xml_add_node(const xml_element &element, xml_tree_state & state, bool verbose) {
 auto *new_node = new XMLNODE(element);
    if (!state.root) {
        state.root = state.cur = new_node;
    } else if (!state.cur->data.closed) {
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
        new_node->parent = state.cur->parent;
        state.cur->right = new_node;
    }
    state.cur = new_node;
    return 0;
   //return 1000;
}

int xml_close_tag(const std::string name, xml_tree_state &state, bool verbose) {
    if (state.cur) {   
        if (state.cur->data.name == name) {
            state.cur->data.closed = true;  
            return 0;                      
        }
    } 

    XMLNODE* currentParent = (state.cur== nullptr) ? nullptr: state.cur->parent; 
	

    while (currentParent) {
        if (currentParent->data.name == name) {
            currentParent->data.closed = true; 
            state.cur = currentParent;           
            return 0; 
        } 
        currentParent = tilted_find_parent(currentParent);  
    } 

    if (verbose) {
        std::cout << "Error: No tag matched for " << name; 
    }
    
    return 1;       
}

int xml_handle_tag(std::string &tagstring, xml_tree_state &state, bool verbose) {
    
    if (tagstring.empty() || tagstring.front() != '<' || tagstring.back() != '>') {
        if (verbose) {
            std::cerr << "ERROR: Invalid tag format: " << tagstring << std::endl;
        }
        return 1;
    }

    
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

    
    if (isClosingTag) {
        return xml_close_tag(tagName, state, verbose);
    }

    
    std::map<std::string, std::string> attributeMap;  
    std::string remainingContent;  
    getline(tagStream, remainingContent); 

  
    int attributeErrors = xml_handle_attributes(remainingContent, attributeMap);  
    if (attributeErrors > 0) {
        if (verbose) {
            std::cerr << "ERROR: Invalid attributes in tag: " << tagstring << std::endl;
        }
    }

   
    xml_element xmlElem(xml_type::tag, tagName, tagstring, attributeMap);  

    
    return xml_add_node(xmlElem, state, verbose);
}


int xml_handle_plaintext(std::string &plaintext, xml_tree_state &state, bool verbose) {
    xml_element element(xml_type::plain, "", plaintext, {});
    return xml_add_node(element, state, verbose);
}


int xml_handle_attributes(const std::string &input, std::map<std::string, std::string> &attrs, bool verbose) {
   int validCount = 0;

    size_t currentIndex = 0; 
    while(currentIndex < input.size() && isspace(input[currentIndex])) { // Skip whitespace 
        ++currentIndex;
    }
    
    while (currentIndex < input.size()) { // While there's input 
        std::string attributeKey; 
        
        // Get the left of the = sign 
        while ((currentIndex < input.size()) && isalnum(input[currentIndex])) {
            attributeKey += input[currentIndex]; // Store as key 
            ++currentIndex; 
        }
        if ((currentIndex < input.size()) && (input[currentIndex] == '=')) {
            ++currentIndex;                       

            if (currentIndex < input.size() && input[currentIndex] == '"') {
                ++currentIndex; // Move past the opening quote 
            
                std::string attributeValue; 
                // While it is still within quotes 
                while (currentIndex < input.size() && input[currentIndex] != '"') {
                    attributeValue += input[currentIndex];
                    ++currentIndex; 
                }
                
                if (currentIndex < input.size() && input[currentIndex] == '"') { 
                    ++currentIndex; 
                    attrs[attributeKey] = attributeValue; // Store value in map 
                    validCount += 1; // Increase count 
                } else {
                    std::cout << "  ERROR: xml_handle_attributes tag ended before value's quotation ended.\n"; 
                    if (verbose) {
                        std::cout << "End Quote missing" << std::endl; 
                    }
                    return 0; // No valid attributes found 
                }
            } else {
                std::cout << "Error: Missing opening quote\n";
                if (verbose) {
                    std::cout << "Beginning quote missing " << std::endl; 
                }
                return 0; 
            }
        } else {
            std::cout << "  ERROR: xml_handle_attributes done. Invalid string remaining \"" << input << "\"" << std::endl;
            return 0; 
        }
        
        // Skip whitespace between attributes
        while (currentIndex < input.size() && isspace(input[currentIndex])) {
            ++currentIndex; 
        }
    }
    return validCount; // Return count of valid attributes 
}


void xml_print_subtree(XMLNODE *root, std::ostream &ost) {
    if (!root) return;

    if (root->data.type == xml_type::tag) {
        ost << to_string(root->data, true); // Opening tag
    } else {
        ost << root->data.fulltext; // Plain text, no recursion needed
        return; // End here since plain text nodes don’t have children
    }

    // Iterate through the left child and its siblings
    for (XMLNODE *childNode = root->left; childNode; childNode = childNode->right) {
        xml_print_subtree(childNode, ost); // Recursively print each child
    }

    if (root->data.type == xml_type::tag) {
        ost << to_string(root->data, false); // Closing tag
    }
}

