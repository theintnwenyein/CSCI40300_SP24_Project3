#include "../header_files/internal_commands.h" // String
#include "../data/text.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <sys/wait.h>

/*
@author Theint Nwe Nyein
@date 3/13/2024
- I tried to call the "set" command from bash directly, and the commented main() is used to test the program. 
I only tested these three commands: "set -o", "set -e", and "set -u". 

@date 3/19/23
- Checked if there is an argument provided, if not, directly execute the set command without invoking bash
*/

bool internal_set(const std::string args) { //TODO: Need to fix if no ARGS are provided (ie. 'set' is the only given args, no 'set -o' or 'set -...')
    // Tokenize the input arguments
    std::istringstream iss(args);
    std::vector<std::string> tokens;
    std::string arg;
    while (std::getline(iss, arg, ' ')) {
        tokens.push_back(arg);
    }

    if (!tokens.empty() && tokens[0] == "set") {
         if (tokens.size() == 1) {
        // Handle 'set' command without arguments
        // Print current environment variables
        extern char** environ;
        for (char** env = environ; *env != nullptr; ++env) {
            std::cout << *env << std::endl;
            }
        return true;
        }
        
        else if (tokens.size() == 2 && tokens[1] == "-h") {
            messages m;
            std::cout << m.getMessage(14)<< std::endl;
            return true;
        }
        
    }

    // Convert vector of strings to array of C-style strings
    std::vector<const char*> argv;
    for (const std::string& token : tokens) {
        argv.push_back(token.c_str());
    }
    argv.push_back(nullptr); // Null-terminate the array

    // Using execlp instead of execvp to search for the command in the PATH environment variable
    if (execlp("bash", "bash", "-c", args.c_str(), nullptr) == -1) {
        std::cerr << "Execution failed." << std::endl;
        return false;
    }

    // This part will only be reached if execlp fails
    std::cerr << "Child process terminated abnormally." << std::endl;
    return false;
}

/*
int main(){
    std::string input = "set";

    if (internal_set(input)) {
        std::cout << "Set command executed successfully." << std::endl;
    } else {
        std::cerr << "Error executing the set command." << std::endl;
    }
    return 0;
}
*/

