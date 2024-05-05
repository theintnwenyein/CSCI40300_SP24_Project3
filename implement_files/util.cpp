/**
 * Util CPP file for implementing the Util methods
 */

// Imports

/**
* Included Imports:
* String
* Vector
*/
#include "../header_files/util.h"
#include <iostream>



std::vector<std::string> split_string(std::string str, std::string delimiter) {
	std::vector<std::string> ret;

	size_t pos = 0;
	std::string token;

	while((pos = str.find(delimiter)) != std::string::npos) {
		token = str.substr(0, pos);
		ret.push_back(token);
		str.erase(0, pos + delimiter.length());
	}

	ret.push_back(str);

	return ret;
}

std::string combine_string(std::vector<std::string> vec, std::string pattern) {
	std::string ret;

	for(size_t i = 0; i < vec.size(); i++)
		ret += (i + 1 == vec.size() ? vec[i] : (vec[i] + pattern));

	return ret;
}


std::string getCurrentDirectory() {
	char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != NULL) {
        return std::string(cwd);
    } else {
        return "Error: Unable to get current directory";
    }
}



