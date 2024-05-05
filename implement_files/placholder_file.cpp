#include "../header_files/internal_commands.h" //String, Vector
#include "../data/text.h"

messages::messages() { }
std::string messages::getMessage(int which) {
    switch(which) {
        case 1: // alias
            return aliasHelpMessage;
        case 2: // bg
            return "";
        case 3: // cd
            return cdHelpMessage;
        case 4: // eval
            return "";
        case 5: // exec
            return "";
        case 6: // _export
            return "";
        case 7: // fc
            return "";
        case 8: // fg
            return "";
        case 9: // help
            return helpMessage;
        case 10: // history
            return historyHelpMessage;
        case 11: // jobs
            return "";
        case 12: // let
            return "";
        case 13: // local
            return "";
        case 14: // set
            return setHelpMessage;
        case 15: // shift
            return "";
        case 16: // shopt
            return "";
        case 17: // source
            return "";
        case 18: // unalias
            return unaliasHelpMessage;
        default:
            return "Error, could not get Help Message.";
    }
}

bool internal_bg(std::string) { return false; }
bool internal_eval(std::string) { return false; }
bool internal_exec(std::string) { return false; }
bool internal_export(std::string) { return false; }
bool internal_fc(std::string) { return false; }
bool internal_fg (std::string) { return false; }
bool internal_jobs(std::string) { return false; }
bool internal_let(std::string) { return false; }
bool internal_local(std::string) { return false; }
bool internal_read(std::string) { return false; }
bool internal_shift(std::string) { return false; }
bool internal_shopt(std::string) { return false; }
bool internal_source(std::string) { return false; }
bool internal_exit(std::string) { return false; }
bool internal_logout(std::string) { return false; }