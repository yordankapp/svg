#ifndef SVG_LINE_H
#define SVG_LINE_H
#include "Figure.h"
#include "string"
#include <vector>

class Line: public Figure{
private:
    int x2;
    int y2;
    int width;
public:
    Line();
    Line(int _x1, int _y1, int _x2, int _y2, int _width, std::string _color);
    Line(std::vector<std::string> figureData);
    void print() const ;
    void translate(int _x, int _y);
    void within(std::vector<std::string> figureData);
    void save(std::ostream& os );
};

#endif //SVG_LINE_H