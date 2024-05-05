#include <dirent.h>
#include "../header_files/special_char.h"
#include <iostream>
#include <cstring>

bool isMatchInBracket(const char* pattern, char c) {
    bool negate = false;
    bool match = false;
    
    if (*pattern == '^') {
        negate = true;
        ++pattern;
    }
    
    while (*pattern != ']' && *pattern != '\0') {
        if (*(pattern + 1) == '-' && *(pattern + 2) != ']') {
            if (c >= *pattern && c <= *(pattern + 2)) {
                match = true;
            }
            pattern += 3;
        } else {
            if (c == *pattern) {
                match = true;
            }
            ++pattern;
        }
    }
    
    return negate ? !match : match;
}

bool matches(const char* pattern, const char* filename) {
    if (*pattern == '\0' && *filename == '\0') return true;
    if (*pattern == '*' && *(pattern+1) != '\0' && *filename == '\0') return false;
    if (*pattern == '?' || *pattern == *filename) return matches(pattern + 1, filename + 1);
    if (*pattern == '*') return matches(pattern + 1, filename) || matches(pattern, filename + 1);
    if (*pattern == '[') {
        const char* closeBracket = strchr(pattern, ']');
        if (!closeBracket) {
            std::cerr << "Unmatched [ in pattern." << std::endl;
            return false; // Pattern is invalid (unmatched '[')
        }
        if (isMatchInBracket(pattern + 1, *filename)) {
            return matches(closeBracket + 1, filename + 1);
        }
    }
    return false;
}

std::vector<std::string> findMatches(const std::string& pattern) {
    DIR* dir;
    struct dirent* ent;
    std::vector<std::string> matchingFiles;

    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (matches(pattern.c_str(), ent->d_name)) {
                matchingFiles.push_back(ent->d_name);
            }
        }
        closedir(dir);
    } else {
        // Could not open directory
        perror("opendir");
        return matchingFiles;
    }

    return matchingFiles;
}
