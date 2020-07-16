
#ifndef SVG_COMMANDDISPATCHER_H
#define SVG_COMMANDDISPATCHER_H
#include "Figure.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "string"
#include <vector>

class CommandDispatcher{
private:
    std::string command;
    std::vector<Figure*> figures;
    int numberOfFigures = 0; 
    std::string userFileName = "";
    void setUserFileName(std::string command);
    void addFigure(std::vector<std::string>& figureData);
    void convertLineFromFile(std::string& line);
    void setFigureDataFromLineOrCommand(std::vector<std::string>&figureData, std::string line);
    std::vector<std::string> splitLineBySpace(std::string line);

public:
    CommandDispatcher();
    void takeCommand(std::string command);
    void print() const;
    void open(std::string command);
    void create(std::string command);
    void translate(std::string command);
    void within(std::string command);
    void erase(std::string command);
    void save();
    void exit() const;
};

#endif //SVG_COMMANDDISPATCHER_H
