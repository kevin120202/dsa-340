#include "settings.h"
#include "iniparse.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// Function to read INI configuration from an input stream
INI_CONFIG read_ini(std::istream &input, int verbosity) 
{
    INI_CONFIG config;
    std::string line, current_section;
    int line_number = 0;

    while (std::getline(input, line)) 
	{
        line_number++;
        // Remove leading and trailing whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty() || line[0] == ';')
		 {
            // Ignore empty lines and comments
            continue;
        }

        if (line[0] == '[') 
		{
            // New section
            size_t end = line.find(']');
            if (end != std::string::npos) 
			{
                current_section = line.substr(1, end - 1);
                if (verbosity >= 1) 
				{
                    std::cout << "Section: " << current_section << std::endl;
                }
            }
        } 
		else 
		{
            // Key-value pair
            size_t eq_pos = line.find('=');
            if (eq_pos != std::string::npos) 
			{
                std::string key = line.substr(0, eq_pos);
                std::string value = line.substr(eq_pos + 1);
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));

                if (!current_section.empty()) 
				{
                    config[current_section][key] = value;
                    if (verbosity >= 1) 
					{
                        std::cout << "Key: " << key << ", Value: " << value << std::endl;
                    }
                }
            }
        }

        if (verbosity >= 2) 
		{
            std::cout << "Line " << line_number << ": " << line << std::endl;
        }
    }

    return config;
}

// Function to write INI configuration to an output stream
bool write_ini(std::ostream & ost, const INI_CONFIG & config) 
{
    for (const auto& section : config) 
	{
        ost << "[" << section.first << "]\n";
        for (const auto& key_value : section.second) 
		{
            ost << key_value.first << "=" << key_value.second << "\n";
        }
        ost << "\n";
    }
    return true;
}

// Function to print INI configuration in a formatted way
void print_ini(std::ostream & ost, const INI_CONFIG & config) 
{
    if (config.empty()) 
	{
        ost << "Configuration is empty. Nothing to print\n";
        return;
    }

    for (const auto& section : config) 
	{
        if (section.second.empty()) 
		{
            ost << "Section \"" << section.first << "\" is empty\n";
        } 
		else 
		{
            for (const auto& key_value : section.second) 
			{
                ost << section.first << "." << key_value.first << "\t= \"" << key_value.second << "\"\n";
            }
        }
    }
    ost << "\n";
}

// Function to add a new section to the INI configuration
void add_ini_section(INI_CONFIG & config, const std::string &section) 
{
    if (config.find(section) == config.end()) 
	{
        config[section] = std::map<std::string, std::string>();
    }
}

// Function to remove a section from the INI configuration
// Returns the number of sections removed (0 or 1)
int remove_ini_section(INI_CONFIG & config, const std::string &section) 
{
    return config.erase(section);
}

// Function to get the value of a key in a specific section
// Returns an empty string if the key or section is not found
std::string get_ini_key(const INI_CONFIG &config, const std::string &section, const std::string &key) 
{
    auto section_it = config.find(section);
    if (section_it != config.end()) 
	{
        auto key_it = section_it->second.find(key);
        if (key_it != section_it->second.end()) 
		{
            return key_it->second;
        }
    }
    return "";
}

// Function to set the value of a key in a specific section
// If the section or key doesn't exist, it will be created
void set_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key, const std::string & value) 
{
    config[section][key] = value;
}

// Function to remove a key from a specific section
// Returns the number of keys removed (0 or 1)
int remove_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key) 
{
    auto section_it = config.find(section);
    if (section_it != config.end()) 
	{
        return section_it->second.erase(key);
    }
    return 0;
}

