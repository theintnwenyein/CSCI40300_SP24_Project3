#include "../header_files/internal_commands.h" // String
#include "../header_files/util.h" // String, Vector, unistd.h
#include "../header_files/history_manager.h" // String, List, fstream, algorithm, sstream
#include "../data/text.h" // String
#include <iostream>

/*
@author Theint Nwe Nyein
@date 3/9/2024
*/

//TODO: Need to fix paths not saving to directories.log file

enum CDArgType {
    h, // Simple Help
    H, // Full Help
    l, // List directory history {included COULD be a numerical value}
    lN, // List the N last directories
    c, // clear directory history
    s, // remove duplicate paths in history
    i, // change to directory from history from line number {i}
    dir, // Change to directory
    NONE // NONE of the above, argument is a directory input
};

class CommandCD {
private:
    std::vector<std::string> args;
    std::string rawInput;
    CDArgType argType;
    const std::string shortHelp = R"(Usage: cd [-h] [-H] [-l [{n}]] [-{n}] [-c] [-s] (DIR)
Change the current directory to DIR.
                  
Options:
-h          Display simple help message.
-H          Display full help message.
-l [{n}]    Display the history list of the current directories with serial numbers. With the optional N, it displays only the last N entries.
-{n}        Change the current directory to the n-th entry in the history list.
-c          Clean the directory history.
-s          Suppress the directory history by eliminating duplicated directories.  The order of the history must be maintained. The latest entry must be kept for same directories.)";


const std::string fullHelp = R"(Description: The cd command is used to change the current working directory in a shell environment. It allows for flexible navigation within the file system and includes additional features 
 beyond the typical cd commands found in Windows Command Prompt or Linux shells.
                    
Usage: cd [-h] [-H] [-l [{n}]] [-{n}] [-c] [-s] (DIR)
Change the current directory to DIR. The default DIR is the current directory so that it is identical to the pwd command in typical Linux shells.
                   
 Options:
-h, --help:
Display a simple help message describing the basic usage of the cd command.
-H, --full-help
Display a detailed help message explaining all available options and usage scenarios for the cd command.              
                            
-l [{n}], --list [{n}]
Display the history list of the current directories with serial numbers. 
If the optional N is provided, it displays only the last N entries from the history list.
For example: Display the last 5 entries from the directory history: cd -l 5
            
- {n} -- Go to nth directory
Change the current directory to the n-th entry in the history list.
For example: Change to the directory listed as the 3rd entry in the history: cd -3                            
                      
                      
-c, --clean-history
Clean the directory history, removing all entries from the history list.
                      
-s, --suppress-duplicates
Suppress the directory history by eliminating duplicated directories. 
The order of the history must be maintained, and only the latest entry must be kept for the same directories.)";

    void clearData() {
        rawInput.clear();
        args.clear();
        argType = NONE;
    }

public:
    CommandCD() {
        argType = NONE;
        rawInput = "";
    }

    ~CommandCD() {}

    std::string getRawInput() {
        return rawInput;
    }

    CDArgType getArgType() {
        return argType;
    }

    std::string getArg(size_t index) {
        if (index < args.size()) {
            return args[index];
        } else {
            return "";
        }
    }

    bool isChangeDirectory() {
        return argType == i;
    }

    void parseCommand(HistoryManager hm, std::string userInput) {
        clearData();
        CommandCD::rawInput = userInput; 

        

        std::string modifiedInput = rawInput.substr(rawInput.find(' ') + 1);

        std::istringstream iss(modifiedInput);
        std::string arg;
        while (iss >> arg) {

            if (arg == "-h") {
                argType = h;
                args.push_back(arg);
            } else if (arg == "-H") {
                argType = H;
                args.push_back(arg);
            } else if (arg == "-l") {
                argType = l;
                args.push_back(arg);
                // Check if there's an optional number after -l
                if (iss >> arg) {
                    try {
                        int n = std::stoi(arg);
                        argType = lN;
                        args.push_back(std::to_string(n));
                    } catch (const std::invalid_argument&) {
                        // Invalid argument after "-l"
                        argType = NONE;
                    }
                }
            } else if (arg == "-c") {
                argType = c;
                args.push_back(arg);
            } else if (arg == "-s") {
                argType = s;
                args.push_back(arg);
            } else if (arg.substr(0, 1) == "-") {
                // Handle -{n} where n is a positive integer
                try {
                    int n = std::stoi(arg.substr(1));
                    if (n >= 0) {
                        argType = i; // Change to directory from history at line number n
                        args.push_back(std::to_string(n));
                    } else {
                        argType = NONE; // Invalid negative integer
                    }
                } catch (const std::invalid_argument&) {
                    // Invalid argument after "-"
                    argType = NONE;
                }
            } else if (arg.substr(0, 1) != "-") {
                argType = dir;
                args.push_back(arg);
            } else {
                argType = NONE;
            }
        }
    }

    

    void implementCDCommand(HistoryManager hm){
        if(getArgType() == h){
            std::cout<<shortHelp<<std::endl;
        } 
        else if(getArgType() == H){
            std::cout<<fullHelp<<std::endl;
        }
        else if(getArgType() == l){
            std::cout << "List of Directories: " << std::endl;
            for (auto dir : hm.getHistory()) {
                std::cout << dir << " " << std::endl;
            }
            std::cout << std::endl;
        }
        else if(getArgType() == lN){
            std::cout << "List of Directories: " << std::endl;
            for (auto dir : hm.getHistory(std::stoul(args[1]))) {
                std::cout << dir << " " << std::endl;
            }
            std::cout << std::endl;
        }
        else if(getArgType() == c){
            hm.clear(); 
            std::cout << "Directory History Cleared" << std::endl;
        }
         else if(getArgType() == s){
            hm.removeDuplicates();  
            std::cout << "Directory History Suppressed" << std::endl;
        }
        else if(getArgType() == i){
            hm.setDirectory(std::stoul(args[0]));
            std::cout << "Change to directory from history at line number: " << args[0]<< std::endl;
        }
        else if(getArgType() == dir){
            std::cout<<"DIR command"<<std::endl;
            const char* directoryPath = args[0].c_str();

            if (chdir(directoryPath) == 0) {
                //std::cout << "Directory changed successfully to: " << directoryPath << std::endl;
            } else {
                std::cerr << "Error: Unable to change directory to: " << directoryPath << std::endl;
            }

            hm.addDirectory(hm.getCurrentDirectory());
            hm.save();
        }
        else{
            std::cout << "Invalid Argument" << std::endl;
        
        }
    }
    
};
    
bool internal_cd(HistoryManager m, std::string args) {
    CommandCD cdCommand; 
    cdCommand.parseCommand(m, args); 
    cdCommand.implementCDCommand(m); 
    return true; 
}


