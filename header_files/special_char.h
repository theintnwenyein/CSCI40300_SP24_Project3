// WildcardCharacters.h
#ifndef WILDCARDCHARACTERS_H
#define WILDCARDCHARACTERS_H

#include <string>
#include <vector>

// Checks if the given filename matches the provided pattern
bool matches(const char* pattern, const char* filename);

// Finds and returns a list of filenames in the current directory that match the given pattern
std::vector<std::string> findMatches(const std::string& pattern);

#endif // WILDCARDCHARACTERS_H
