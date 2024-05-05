#include "../header_files/internal_commands.h" // String
#include "../data/text.h" // historyHelpMessage
#include "../header_files/util.h"
#include <iostream>
#include <cstdlib> // For std::atoi

/*
@author Theint Nwe Nyein
@date 3/10/2024
*/

std::vector<std::string> commandHistory;


void addToHistory(const std::string &command)
{
    commandHistory.push_back(command);
}


// Function to display the command history - If num is negative, display the full history
void displayHistory(int num)
{
    std::cout << "Command History:" << std::endl;
    int start = (num > 0) ? std::max(0, static_cast<int>(commandHistory.size()) - num) : 0;
    for (int i = start; i < commandHistory.size(); ++i)
    {
        std::cout << i + 1 << ". " << commandHistory[i] << std::endl;
    }
}

void clearHistory()
{
    commandHistory.clear();
    std::cout << "Command History cleared." << std::endl;
}


// Function to delete history entry at position OFFSET
void deleteHistoryEntry(int offset)
{
    if (offset >= 0 && offset < commandHistory.size())
    {
        commandHistory.erase(commandHistory.begin() + offset);
        std::cout << "Deleted history entry at position " << offset << "." << std::endl;
    }
    else
    {
        std::cerr << "Invalid offset." << std::endl;
    }
}

// Function to get the nth command from history
std::string getNthCommand(size_t n)
{
    if (n > 0 && n <= commandHistory.size())
    {
        return commandHistory[n - 1];
    }
    else
    {
        std::cerr << "Invalid history reference." << std::endl;
        return "";
    }
}

// Function to get the most recent command from history
std::string getMostRecentCommand()
{
    if (!commandHistory.empty())
    {
        return commandHistory.back();
    }
    else
    {
        std::cerr << "History is empty." << std::endl;
        return "";
    }
}


// std::vector<std::string> split_string(std::string str, std::string delimiter) {
// 	std::vector<std::string> ret;

// 	size_t pos = 0;
// 	std::string token;

// 	while((pos = str.find(delimiter)) != std::string::npos) {
// 		token = str.substr(0, pos);
// 		ret.push_back(token);
// 		str.erase(0, pos + delimiter.length());
// 	}

// 	ret.push_back(str);

// 	return ret;
// }

bool internal_history(std::string args){
    args = args.substr(7);

    // Display the entire history is no arguments are provided
    if(args == ""){
        displayHistory(-1);
        return true;
    }

    args = args.substr(1);
    std::vector<std::string> tokens = split_string(args, " ");

    // If the user wants to display the history
    if(tokens[0] == "-h"){
        messages m;
        std::cout<<m.getMessage(10)<<std::endl;
        return true;
    }

    // If the user wants to display the last N commands
    else if (tokens[0] == "-n") {
        if (tokens.size() > 1) {
            int num = std::stoi(tokens[1]);
            displayHistory(num); // Display last N commands
            return true;
        } else {
            std::cerr << "Invalid usage of -n. Usage: history -n NUM" << std::endl;
            return false;
        }
    }

    // If the user wants to clear the history
    else if (tokens[0] == "-c")
    {
        clearHistory();
        return true;
    }
    // If the user wants to delete a specific history entry
    else if (tokens[0] == "-d")
    {
        if (tokens.size() > 1)
        {
            int offset = std::stoi(tokens[1]);
            deleteHistoryEntry(offset);
            return true;
        }
        else
        {
            std::cerr << "Offset not provided for deletion." << std::endl;
            return false;
        }
    }
    else if (tokens[0][0] == '!'){
    // If the user wants to refer to the most recent command
        if (tokens[0] == "!!")
        {
            std::string recentCommand = getMostRecentCommand();
            std::cout << "Most recent command: " << recentCommand << std::endl;
            return true;
        }
        else // If the user wants to refer to a command by its index
        {
            int n = std::stoi(tokens[0].substr(1));
            std::string nthCommand = getNthCommand(n);
            std::cout << "Command #" << n << ": " << nthCommand << std::endl;
            return true;
        }
    }
    
    else{
        std::cerr << "Invalid history command." << std::endl;
        return false;
    }

    return false;
}

