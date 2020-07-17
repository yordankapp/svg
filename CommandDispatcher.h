
#ifndef SVG_COMMANDDISPATCHER_H
#define SVG_COMMANDDISPATCHER_H
#include "Figure.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "string"
#include <vector>
#include <utility>

class CommandDispatcher{
private:
    std::string command;
    std::vector<Figure*> figures;
    std::string userFileName = "";
    void setUserFileName(std::string command);
    Figure* createFigure(std::vector<std::string> figureData);
    void addFigure(std::vector<std::string>& figureData);
    void simplifyLineFromFile(std::string& line);
    void setFigureDataFromLineOrCommand(std::vector<std::string>&figureData, std::string line);
    std::vector<std::string> splitLineBySpace(std::string line);
    bool lineContainsFigure(std::vector<std::string> line);
    std::pair<int,int> getParametersForTranslation(std::vector<std::string> line); 
    int findFigurePositionInAllFigures(std::vector<std::string> figureData);
    void translateOneFigure(std::vector<std::string> figureData, std::pair<int,int> parameters);
    void translateAllFigures(std::pair<int,int> parameters);

public:
    CommandDispatcher();
    void execute(std::string command);
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
