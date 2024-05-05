/**
 * Utility class that contains methods that can be used
 * to simplify redundant code.
 */

#ifndef H_UTIL_HEADER
#define H_UTIL_HEADER

#include <string>
#include <vector>
#include <unistd.h>

std::vector<std::string> split_string(std::string, std::string);
std::string combine_string(std::vector<std::string>, std::string);
std::string getCurrentDirectory();

#endif
