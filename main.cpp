#include <iostream>
#include <fstream>
#include "CommandDispatcher.h"
#include "Figures/Figure.h"
#include "Figures/Line.h"
#include "Figures/Circle.h"
#include "Figures/Rectangle.h"
#include "string"

using namespace std;

int main()
{
    CommandDispatcher commandDispatcher;
    while(true){
        std::string command = "";
        getline(cin, command);
        commandDispatcher.takeCommand(command);
        if(command == "exit"){
            break;
        }
    }
    return 0;
}
