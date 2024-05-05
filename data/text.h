/**
* This file contains const string objects that are used for other classes
* and information for the project.
*/

#ifndef H_TEXTHEADER
#define H_TEXTHEADER

#include <string>
#include "../header_files/internal_commands.h"



class messages {
  private:
const std::string aliasHelpMessage = R"(Usage: alias [-h] [-p] [-a] [alias_name='command']

Define or display aliases for commands.

Options:

-h: Display simple help message.
-p: Display existing aliases.
-a: Remove all aliases.
alias_name='command': Define an alias where alias_name is the name of the alias, and command is the associated command.)";


const std::string unaliasHelpMessage = R"(Usage: unalias [-h] [alias_name]

Remove aliases for commands.

Options:

-h: Display simple help message.
alias_name: The name of the alias to remove.)";

const std::string historyHelpMessage = R"(Usage: history [-h] [-c] [-n NUM] [-d offset] [!n] [!!]

Display command history.

Options:

-h:       Display simple help message.
-c:       Clear the command history by deleting all entries.
-n NUM:   Display the last NUM commands in the history.
-d offset Delete the history entry at position OFFSET. Negative offsets count back from the end of the history list.
!n        Retrieve the nth command from the history list.
!!        Retrieve the most recent command from the history list.)";

const std::string setHelpMessage = R"(Usage: set [OPTION] [VAR=VALUE]

Set or display shell attributes and positional parameters.

Options:
  -o OPTION      Set the option named OPTION.
  +o OPTION      Unset the option named OPTION.
  -a             Mark variables which are modified or created for export to the environment of subsequent commands.
  ...            ...
  -h             Display a simple help message.)";
  
const std::string cdHelpMessage = R"(Usage: cd [-h] [-H] [-l [{n}]] [-{n}] [-c] [-s] (DIR)
Change the current directory to DIR.
                  
Options:
-h          Display simple help message.
-H          Display full help message.
-l [{n}]    Display the history list of the current directories with serial numbers. With the optional N, it displays only the last N entries.
-{n}        Change the current directory to the n-th entry in the history list.
-c          Clean the directory history.
-s          Suppress the directory history by eliminating duplicated directories.  The order of the history must be maintained. The latest entry must be kept for same directories.)";

const std::string helpMessage = R"(Welcome to Gamma Command Interface

Overview:
Gamma provides a user-friendly interface to execute commands in various scenarios. It supports features like pipe and redirection, wildcard characters, multiple commands in a line, conditional execution, and additional internal commands.

A. Pipe and Redirection:

Use | as a pipe between two programs to pass the output of the first program as input to the second program.
Use > to store the output of a program to a file, and >> to append the output to the end of a file.
Use < to redirect the standard input of a program from a file.


B. Wildcard Characters:

Use ?, *, and [...] for pattertn matching in filenames.


C. Multiple Commands in a Line:

Use ; to terminate commands in a line.
Example: Gamma$ cd /etc ; grep nologin passwd > sysaccnt.txt ; grep nologin group >> sysaccnt.txt

D. Conditional Execution:

Use if, elseif, else, and endif for conditional execution of commands.


E. Additional Internal Commands:

help: Display help for commands.
history: Display command history.
alias: Define or display aliases.
unalias: Remove aliases.
set: Set shell options.

F. Help Command to get started:
Usage: help [command_name]

Display help information for commands.

Options:

command_name: The name of the command to display help for. If not specified, general help information is provided.)";
  public:
    messages();
    std::string getMessage(int);
};

#endif