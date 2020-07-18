#ifndef SVG_RECTANGLE_H
#define SVG_RECTANGLE_H
#include "Figure.h"
#include "string"
#include <vector>

class Rectangle : public Figure{
private:
    int width;
    int height;
public:
    Rectangle();
    Rectangle(int _x, int _y, int _width, int _height, std::string _color);
    Rectangle(std::vector<std::string> figureData);
    void print() const;
    void translate(int _x, int _y);
    void within(std::vector<std::string> figureData);
    void save(std::ostream& os);
    bool operator==(const Rectangle& otherRectangle) const;
    Rectangle& operator=(const Rectangle& otherRectangle);
};

#endif //SVG_RECTANGLE_H
