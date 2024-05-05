/*
* Implementation of external comands. 
*/

#include "../header_files/keywords.h"
#include "../header_files/internal_commands.h"
#include "../header_files/runnable.h"
#include "../header_files/util.h"
#include <iostream>

cmd_type InternalCommand(std::string command) {
    if(command == "alias") return alias;
    else if(command == "bg") return bg;
    else if(command == "cd") return cd;
    else if(command == "eval") return eval;
    else if(command == "exec") return exec;
    else if(command == "export") return _export;
    else if(command == "fc") return fc;
    else if(command == "fg") return fg;
    else if(command == "help") return help;
    else if(command == "history") return history;
    else if(command == "jobs") return jobs;
    else if(command == "let") return let;
    else if(command == "local") return local;
    else if(command == "set") return set;
    else if(command == "shift") return shift;
    else if(command == "shopt") return shopt;
    else if(command == "source") return source;
    else if(command == "unalias") return unalias;
    else return none;
}

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void runCommand(std::string input) {
    //split the input into  a vector
   std::vector<std::string> statement = split_string(input,";");
   std::string temp = statement[statement.size() - 1];

   ltrim(temp);
   rtrim(temp);

    if(temp != "endif"){
        std::cout << statement[statement.size() - 1] << std::endl;
        std::cout<< "incorrect format"<<std::endl;
        return;
    }

   for( int i=0; i< statement.size(); /** increase i inside loop*/){
        std::string sub = statement.at(i).substr((i==0 ? 3 :(i+1)==statement.size()? 5 :(i%2)==1 ? 5 : 7),statement[i].length()); // this gets the sub string argumnets 
        // now i need to run the statmnets
        cmd_type cmd = InternalCommand(split_string(sub," ")[0]);

        if(i + 2 >= statement.size() && statement.size() % 2 == 0) {
            if(cmd == none) {
                const char* CMD = split_string(sub, " ")[0].c_str();

                //std::string ARGS = sub.substr(split_string(sub, " ")[0].length(), sub.length());

                runExternalCommand(CMD, sub);
                break;
            }

            run_command(cmd, sub);
            break;
        } else if(i + 2 >= statement.size() && statement.size() % 2 == 1 && split_string(statement[i], " ")[0] == "endif") {
            break;
        }

        if(cmd == none) {
            const char* CMD = split_string(sub, " ")[0].c_str();
            //std::string ARGS = sub.substr(split_string(sub, " ")[0].length(), sub.length());

            bool check = runExternalCommand(CMD, sub);

            if(check) {
                //sub = statement.at(i+1).substr((i+1==0 ? 5 :(i+1)==statement.size()? 5 :(i%2)==1 ? 5 : 7),statement[i + 1].length());
                sub = statement[i+1].substr(5, statement[i + 1].length());
                cmd = InternalCommand(split_string(sub," ")[0]);

                ltrim(sub);
                rtrim(sub);

                if(cmd == none) {
                    const char* CMD_2 = split_string(sub, " ")[0].c_str();
                    //ARGS = sub.substr(split_string(sub, " ")[0].length(), sub.length());

                    runExternalCommand(CMD_2, sub);
                    break;
                } else {
                    run_command(cmd,sub);
                    break;
                }
            }
        }

        if(run_command(cmd,sub)){
            //sub = statement.at(i+1).substr((i==0 ? 5 :(i+1)==statement.size()? 5 :(i%2)==1 ? 7 : 5),(statement[i].length()));
            sub = statement[i+1].substr(5, statement[i + 1].length());
            cmd = InternalCommand(split_string(sub," ")[0]);

            ltrim(sub);
            rtrim(sub);

            if(cmd == none) {
                const char* CMD = split_string(sub, " ")[0].c_str();
                //std::string ARGS = sub.substr(split_string(sub, " ")[0].length(), sub.length());

                runExternalCommand(CMD, sub);
                break;
            } else {
                run_command(cmd,sub);
                break;
            }
        } else {
            i += 2;
        }
   }
}
// 0 1 2
//   1 2 3


/*
0If cmd;            0if                  0if              0if
1then cmd;          1then                1then            1then
2endif              2elseif              2else            2elseif
                    3then                3endif           3then
                    4endif                                 4else
                                                        5endif


*/