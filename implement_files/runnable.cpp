#include "../header_files/runnable.h"
#include "../header_files/internal_commands.h"
#include "../header_files/util.h"

#include <iostream>
#include <sys/wait.h>

bool run_command(cmd_type cmd, std::string args) {

    pid_t pid = fork();

    if(pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        switch(cmd) {
            case 1: // alias
                return internal_alias(args);
            case 2: // bg
                return internal_bg(args);
            // case 3: // cd
            //     return internal_cd(args);
            case 4: // eval
                return internal_eval(args);
            case 5: // exec
                return internal_exec(args);
            case 6: // _export
                return internal_export(args);
            case 7: // fc
                return internal_fc(args);
            case 8: // fg
                return internal_fg(args);
            case 9: // help
                return internal_help(args);
            case 10: // history
                return internal_history(args);
            case 11: // jobs
                return internal_jobs(args);
            case 12: // let
                return internal_let(args);
            case 13: // local
                return internal_local(args);
            case 14: // set
                return internal_set(args);
            case 15: // shift
                return internal_shift(args);
            case 16: // shopt
                return internal_shopt(args);
            case 17: // source
                return internal_source(args);
            case 18: // unalias
                return internal_unalias(args);
            case 0: // NONE
                // Not an internal command, should be something like a file input:  gamma < fileName.txt == OR === fileName.txt
                                                                                //NOTE: 'gamma'is NOT included in the input/args
                return true;
            default:
                std::cout << "Error, could not run inputted commands... exiting program" << std::endl;
                // Kill Program
                return false;
        }

        // Catch if split does not execute properly
        return false;
    }

    return true;
}

bool run_command_cd(HistoryManager m, std::string args) {
    
    pid_t pid = fork();

    if(pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        return internal_cd(m, args);
        // Catch if split does not execute properly
        return false;
    }

    return true;
}

/**
 * Name: runExternalCommand
 * Type: Function
 * Parameter:
 *   cmd CHAR* - External command to run
 *   cmd_args STRING - arguments of the command
 * Return:
 *   Boolean
 */
bool runExternalCommand(const char* cmd, std::string cmd_strargs) {
    pid_t pid = fork();
    bool ret = true;

    std::vector<char*> cmd_args;

    for(auto& s : split_string(cmd_strargs, " "))
        cmd_args.push_back(const_cast<char*>(s.c_str()));
    cmd_args.push_back(nullptr);

    if (pid == -1) {
        std::cerr << "Failed to fork" << std::endl;
        return !ret;
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    } else {
        // Child process
        execvp(cmd, cmd_args.data());
        std::cerr << "Failed to execute command: " << cmd_strargs << std::endl;
        ret = false;
        _exit(1); // Exit child process
    }

    return ret;
}