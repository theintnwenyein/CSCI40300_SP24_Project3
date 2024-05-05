#include "../header_files/internal_commands.h" // String
#include "../data/text.h"
#include <iostream>

/*
@author Theint Nwe Nyein
@date 3/8/2024
*/

bool internal_help(std::string args) {
    messages m;

    if(args == "help"){
        std::cout<<m.getMessage(9)<<std::endl;
    }    
    if(args == "help cd"){
        std::cout<<m.getMessage(3)<<std::endl;
    }

    if(args == "help alias"){
        std::cout<<m.getMessage(1)<<std::endl;
    }

    if(args == "help unalias"){
        std::cout<<m.getMessage(18)<<std::endl;
    }

    if(args == "help history"){
        std::cout<<m.getMessage(10)<<std::endl;
    }

    if(args == "help set"){
        std::cout<<m.getMessage(14)<<std::endl;
    }

    return false;
}

