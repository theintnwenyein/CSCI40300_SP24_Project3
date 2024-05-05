/**
* Eagle: 10
* Members: Maria Colon, Theint Nwe Nyein, Leo Goldstein, Josh Moore
* 
* This file is the main file of the program. All other files are found
* within their respective file locations within the given directories
* 
* LOG:
* 1 March 2024
* - Added Header information
*/

//--- Imports ---//
#include <iostream>
#include <cctype>
#include <algorithm>
#include <sys/wait.h>

#include "header_files/util.h" // String, Vector
#include "header_files/internal_commands.h"
#include "header_files/keywords.h"
#include "header_files/special_char.h"
#include "header_files/runnable.h"
#include "header_files/history_manager.h"

//--- Pre-cached methods ---//
std::string convert_to_string(int, char**);
cmd_type isInternalCommand(std::string);
bool isKeyword(std::string);
void runKeyWord(std::string);

/**
* Name: main
* Type: Method
* Description: Main function of the program. This intakes the arguments of the program and
*              organizes the information into the correct command to be ran.
* Parameters:
*   argc INT - Number of arguments for the program. The program will always have at least one (1)
*   args char** - Double pointer containing all arguments given for the 
* Return:
*   INT - 0 if program runs correctly
*/
int main(int argc, char** args) {
    bool mode = true;
    bool hasExternal = false;
    cmd_type cmd;
    HistoryManager hm;

    std::string value(argc >= 2 ? args[1] : "");
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c){return std::tolower(c); });

    if(argc < 2)
        std::cout << "Entering interactive mode..." << std::endl;
    else {
        if(split_string(value, " ")[1] == "if") {
            mode = false;
            hasExternal = true;
        } else {
            cmd = isInternalCommand(args[1]);
            mode = (cmd != 0);
        }

    }

    std::string uInput = convert_to_string(argc, args);

    if(mode) {
        while(true) {
            if(uInput == "") {
                std::cout << getCurrentDirectory() << " $ ";
                std::getline(std::cin, uInput);
                continue;
            }
            
            cmd = isInternalCommand(split_string(uInput, " ")[0]);

            if(uInput == "exit" || uInput == "logout")
                break;
            else if(isKeyword(split_string(uInput, " ")[0]))
                runCommand(uInput);
            else if(cmd != none) {
                if(cmd == cd) {
                    run_command_cd(hm, uInput);
                } else
                    run_command(cmd, uInput);
            } else
                runExternalCommand((char*)split_string(uInput, " ")[0].c_str(), uInput);

            std::cout << getCurrentDirectory() << " $ ";
            std::getline(std::cin, uInput);
        }
    } else { // Used for running batch mode
        if(isKeyword(split_string(uInput, " ")[0])) {
            runCommand(uInput);
        } else {
            runExternalCommand(split_string(uInput, " ")[0].c_str(), uInput);
        }
    }

    return 0;
}

/**
 * Name: convert_to_string
 * Type: Function
 * Parameters:
 *   argc INT - Number of arguments of the double char pointer
 *   args CHAR** - arguments given that will converge into a single string.
 *
 * Return:
 *   String
 */
std::string convert_to_string(int argc, char** args) {
    std::string ret;

    for(int i = 1; i < argc; i++)
        ret += (i + 1 < argc ? std::string(args[i]) + " " : std::string(args[i]));

    return ret;
}

/**
 * Name: isInternalCommand
 * Type: Function
 * Parameter:
 *   command STRING - first argument of user input to check.
 */
cmd_type isInternalCommand(std::string command) {
    if(command == "alias") return alias;
    else if(command == "bg") return bg;
    else if(command == "cd") return cd;
    else if(command == "eval") return eval;
    else if(command == "exec") return exec;
    else if(command == "export") return _export;
    else if(command == "fc") return fc;
    else if(command == "fg") return fg;
    else if(command == "help") return help;
    else if(command == "history") return history;
    else if(command == "jobs") return jobs;
    else if(command == "let") return let;
    else if(command == "local") return local;
    else if(command == "set") return set;
    else if(command == "shift") return shift;
    else if(command == "shopt") return shopt;
    else if(command == "source") return source;
    else if(command == "unalias") return unalias;
    else return none;
}

bool isKeyword(std::string arg) { return arg == "if"; }

/**
* Name: runKeyword
* Type: Function
* Parameter:
*   args STRING - input of the program.
*/
void runKeyword(std::string args) { runCommand(args); }