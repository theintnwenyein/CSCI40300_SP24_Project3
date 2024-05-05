#ifndef H_RUNNABLECOMMANDS
#define H_RUNNABLECOMMANDS

#include "internal_commands.h"

bool run_command(cmd_type, std::string);
bool run_command_cd(HistoryManager, std::string);
bool runExternalCommand(const char*, std::string);

#endif