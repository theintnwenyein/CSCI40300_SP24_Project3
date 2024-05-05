/**
 * This contains the methods used when the program
 * runs an internal command.
 */

#ifndef H_INTERNALCOMMANDS
#define H_INTERNALCOMMANDS

#include <string>

#include <vector>//  form Maria to Theint ; i added the vector beacuse it was creating errors 

#include "history_manager.h"

//--- Enum Command Values ---//
enum cmd_type { none, alias, bg, cd,  eval, exec, _export, fc, fg, help, history, jobs, let, local, set , shift, shopt, source, unalias };

// TODO: Need to add Javadoc information for each Method

bool internal_alias(std::string);
bool internal_bg(std::string);
bool internal_cd(HistoryManager, std::string);
bool internal_eval(std::string);
bool internal_exec(std::string);
bool internal_export(std::string);
bool internal_fc(std::string);
bool internal_fg (std::string);
bool internal_help(std::string);
bool internal_history(std::string);
bool internal_jobs(std::string);
bool internal_let(std::string);
bool internal_local(std::string);
bool internal_read(std::string);
bool internal_set(std::string);
bool internal_shift(std::string);
bool internal_shopt(std::string);
bool internal_source(std::string);
bool internal_unalias(std::string);
bool internal_exit(std::string);
bool internal_logout(std::string);

#endif