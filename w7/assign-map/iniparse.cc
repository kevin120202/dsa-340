/************************************************************************************
 ** NIU CSCI 340 Section 2 * Assignment #6 Kevin Dela Paz - z2017241 *
 **
 * I certify that everything I am submitting is either provided by the professor
 *for use in * the assignment, or work done by me personally. I understand that
 *if I am caught submitting * the work of others (including StackOverflow or
 *ChatGPT) as my own is an act of Academic * Misconduct and will be punished as
 *such. *
 ************************************************************************************/

#include "iniparse.h"
#include "settings.h"
#include <iostream>
#include <map>
#include <sstream>

// Define INI_CONFIG as a map where each section is a string (key),
// and each section contains another map of key-value pairs (strings).
using INI_CONFIG = std::map<std::string, std::map<std::string, std::string>>;

/**
 * @brief Reads an INI configuration from an input stream and parses it into an
 * object.
 *
 * @param input A reference to an input stream
 * @param verbosity The level of verbosity (0: silent, >0: print load status).
 * @return INI_CONFIG The parsed configuration as a map of sections containing
 * pairs.
 *
 * This function reads line by line, ignoring comments and empty lines. For
 * section headers, lines closed in square brackets, it creates a new section.
 * For key-value pairs, it parses the key and value, trimming whitespaces, and
 * adds them to the corresponding section.
 */
INI_CONFIG read_ini(std::istream &input, int verbosity) {
  INI_CONFIG config;                 // Holds the parsed INI file
  std::string line, current_section; // Current line and section

  while (std::getline(input, line)) {
    // Ignore comments and empty lines
    if (line.empty() || line[0] == ';' || line[0] == '#')
      continue;

    // Trim leading and trailing whitespace
    line.erase(0, line.find_first_not_of(" \t"));
    line.erase(line.find_last_not_of(" \t") + 1);

    if (line.front() == '[' && line.back() == ']') {
      // Get the section name by removing the brackets
      current_section = line.substr(1, line.size() - 2);
      config[current_section] = {}; // Create new section in the map
    } else {
      size_t equals_pos = line.find('=');
      if (equals_pos != std::string::npos) {
        std::string key = line.substr(0, equals_pos);
        std::string value = line.substr(equals_pos + 1);

        // Trim key and value of any surrounding whitespace
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        // Store key-value pair in the current section
        config[current_section][key] = value;
      }
    }
  }

  // Print a message if verbosity is enabled
  if (verbosity > 0) {
    std::cout << "INI file loaded with " << config.size() << " sections."
              << std::endl;
  }

  return config;
}

/**
 * @brief Writes an INI configuration to an output stream.
 *
 * @param ost A reference to the output stream where the configuration will be
 * written.
 * @param config The INI configuration to be written, structured as a map of
 * sections and key-value pairs.
 * @return bool True if the configuration was written.
 *
 * This function iterates over each section in the INI_CONFIG map and writes the
 * section header followed by its corresponding key-value
 * pairs.
 */
bool write_ini(std::ostream &ost, const INI_CONFIG &config) {
  for (const auto &section : config) {
    ost << "[" << section.first << "]\n"; // Write the section header
    for (const auto &key_value : section.second) {
      ost << key_value.first << "\t= " << key_value.second
          << "\n"; // Write each key-value pair
    }
    ost << "\n"; // Add a blank line after each section
  }
  return true;
}

/**
 * @brief Prints the INI configuration in a formatted way to an output stream.
 *
 * @param ost A reference to the output stream where the configuration will be
 * printed.
 * @param config The INI configuration to print, structured as a map of sections
 * and pairs.
 *
 */
void print_ini(std::ostream &ost, const INI_CONFIG &config) {
  if (config.empty()) {
    ost << "Configuration is empty. Nothing to print\n";
    return;
  }

  for (const auto &section : config) {
    if (!section.second.empty()) {
      for (const auto &key_value : section.second) {
        ost << section.first << "." << key_value.first << "\t= \""
            << key_value.second << "\"\n";
      }
    } else {
      ost << "Section \"" << section.first
          << "\" is empty\n"; // If section is empty, print empty message
    }
  }
  ost << std::endl; // Ensure proper newline at the end
}

/**
 * @brief Adds a new section to the INI configuration.
 *
 * @param config The INI_CONFIG object where the section will be added.
 * @param section The name of the new section
 *
 * If the section does not already exist in the configuration, this function
 * creates it.
 */
void add_ini_section(INI_CONFIG &config, const std::string &section) {
  if (config.find(section) == config.end()) {
    config[section] = {}; // Create new section if it doesn't exist
  }
}

/**
 * @brief Removes a section from the INI configuration.
 *
 * @param config The INI_CONFIG object from which the section will be removed.
 * @param section The name of the section to remove.
 * @return int 1 if the section was successful, 0 if the section was
 * not found.
 */
int remove_ini_section(INI_CONFIG &config, const std::string &section) {
  if (config.erase(section) > 0) {
    return 1; // Section removed successfully
  }
  return 0; // Section not found
}

/**
 * @brief Retrieves the value of a key from a specific section in the INI
 * configuration.
 *
 * @param config The INI_CONFIG object containing the data.
 * @param section The name of the section where the key is located.
 * @param key The name of the key whose value should be retrieved.
 * @return std::string The value of the key if found, or an empty string
 */
std::string get_ini_key(const INI_CONFIG &config, const std::string &section,
                        const std::string &key) {
  auto section_it = config.find(section);
  if (section_it != config.end()) {
    auto key_it = section_it->second.find(key);
    if (key_it != section_it->second.end()) {
      return key_it->second; // Return the value if the key is found
    }
  }
  return "";
}

/**
 * @brief Sets the value of a key in a specific section of the INI
 * configuration.
 *
 * @param config
 * @param section The name of the section where the key is located.
 * @param key The name of the key to set or update.
 * @param value The new value for the key.
 *
 * If the section or key does not exist, it will be created.
 */
void set_ini_key(INI_CONFIG &config, const std::string &section,
                 const std::string &key, const std::string &value) {
  config[section][key] = value; // Set or update the key-value pair
}

/**
 * @brief Removes a key from a specific section in the INI configuration.
 *
 * @param config The INI_CONFIG object the key will be removed.
 * @param section The name of the section where the key is located.
 * @param key The name of the key to remove.
 * @return int 1 if the key was successfully removed, 0 if the key or section
 * was not found.
 */
int remove_ini_key(INI_CONFIG &config, const std::string &section,
                   const std::string &key) {
  auto section_it = config.find(section);
  if (section_it != config.end()) {
    auto &keys = section_it->second;
    if (keys.erase(key) > 0) {
      return 1; // Key removed successfully
    }
  }
  return 0; // Key not found
}
