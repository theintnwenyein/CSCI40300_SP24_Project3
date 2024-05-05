#include "../header_files/history_manager.h"

HistoryManager::HistoryManager() {
    std::string log;
    baseDir = getCurrentDirectory() + "/";
    std::ifstream logFile(baseDir + "data/Directories.log"); 
    while (std::getline(logFile, log)) {
        directory.push_back(log);
    }
    logFile.close();
}

HistoryManager::~HistoryManager() { }

std::list<std::string> HistoryManager::getHistory() {
    return getHistory(1);
}

std::list<std::string> HistoryManager::getHistory(int startPoint) {
    std::list<std::string> history;
    if(startPoint > 0){
        for (int i = startPoint - 1; i < directory.size(); i++) {
            history.push_back(directory.at(i));
        }

    }
    return history;
    
}

std::string HistoryManager::getCurrentDirectory() {
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != NULL) {
        return std::string(cwd);
    } else {
        return "Error: Unable to get current directory";
    }
}

void HistoryManager::setDirectory(int lineNumber) {
    if (lineNumber <= directory.size() && lineNumber > 0) {
        const char* temp = directory.at(lineNumber - 1).c_str();
        chdir(temp);
        addDirectory(directory.at(lineNumber - 1));
        save();
    }
}

void HistoryManager::clear() {
    directory.clear();
    save();
}

void HistoryManager::removeDuplicates() {
    std::vector<std::string> temp;
    for (int i = 0; i < directory.size(); i++) {
        temp.push_back(directory.at(i));
    }
    std::sort(temp.begin(), temp.end());
    auto it = std::unique(temp.begin(), temp.end());
    temp.erase(it, temp.end());
    directory.clear();

    for (int i = 0; i < temp.size(); i++)
        directory.push_back(temp.at(i));

    save();
}

void HistoryManager::addDirectory(std::string dir) {
    directory.push_back(dir);
    save();
}

void HistoryManager::save() {
    std::ofstream logFile(baseDir + "data/Directories.log");
    logFile.open(baseDir + "data/Directories.log");

    std::string log = "";
    for (int i = 0; i < directory.size(); i++) {
        log += directory.at(i) + "\n";
    }
    logFile << log;
    logFile.close();
}