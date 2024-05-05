#include "../header_files/internal_commands.h" // String
#include "../data/text.h" // aliasHelpMessage
#include <iostream>
#include <string>
#include <unordered_map> // For storing aliases 

/*
@author Theint Nwe Nyein
@date 3/9/2024
@log: Deleted command_unalias.cpp and moved the unalias method to this file to make it easier to store all aliases.
*/
std::unordered_map<std::string, std::string> aliasMap;

bool internal_alias(std::string aliasCommand) {
    messages m;
    std::string args = aliasCommand.substr(6); // Remove "alias " from the command 
    size_t equalSignPos = args.find('=');
     

    // Check if the user wants to display existing aliases
    if (args == "-p") {
        std::cout << "Existing aliases:" <<std::endl;
        for (const auto& pair : aliasMap) {
            std::cout << pair.first << "=" << pair.second <<std::endl;
        }
        std::cout << std::endl;
        return true;
    }

    // Check if the user wants to remove all aliases
    else if (args == "-a") {
        aliasMap.clear();
        std::cout << "All aliases removed." << "\n" <<std::endl;
        return true;
    }
    
    else if(args == "-h"){
        std::cout<<m.getMessage(1)<<std::endl;
    }
    
    // Check if '=' exists and it's not the first or last character
    else if (equalSignPos == std::string::npos || equalSignPos == 0 || equalSignPos == args.length() - 1) {
        std::cerr << "Invalid alias format. Usage: alias <alias_name>=<command>" << std::endl;
        return false;
    }

    else{
        std::string alias = args.substr(0, equalSignPos);
        std::string command = args.substr(equalSignPos + 1);

        // Store the alias and command in the aliasMap
        aliasMap[alias] = command;

        std::cout << "Alias '" << alias << "' set to '" << command << "'" << "\n" <<std::endl;
        return true;
    }

    return false;
}

bool internal_unalias(std::string unaliasCommand){
    messages m;
    std::string args = unaliasCommand.substr(8); // Remove "unalias " from the command
    auto it = aliasMap.find(args);

    if (args == "-a") {
        aliasMap.clear();
        std::cout << "All aliases removed." << "\n" << std::endl;
        return true;
    }
    else if(args == "-h"){
        std::cout<<m.getMessage(18)<< "\n" <<std::endl; 
    }
    
    else if (it != aliasMap.end()) {
        aliasMap.erase(it);
        std::cout << "Alias '" << args << "' removed." << "\n" << std::endl;
        return true;
    } else {
        std::cerr << "Alias '" << args << "' not found." << std::endl;
    }
    return false;
    

}
