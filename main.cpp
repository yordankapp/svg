#include <iostream>
#include <fstream>
#include "CommandDispatcher.h"
#include "Figure.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
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
