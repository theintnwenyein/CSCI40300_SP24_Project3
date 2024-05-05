// Header for handling the HistoryManager class
#ifndef H_HISTORYMANAHER
#define H_HISTORYMANAHER

#include <string>
#include <list>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <sstream>

class HistoryManager {
    private:
        std::vector<std::string> directory;
        std::string baseDir;
    public:
        HistoryManager();
        ~HistoryManager();
        std::list<std::string> getHistory();
        std::list<std::string> getHistory(int);
        std::string getCurrentDirectory();
        void setDirectory(int);
        void clear();
        void removeDuplicates();
        void addDirectory(std::string);
        void save();
};

#endif