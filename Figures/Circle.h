#ifndef SVG_CIRCLE_H
#define SVG_CIRCLE_H
#include "Figure.h"
#include "string"
#include <vector>

class Circle : public Figure{
private:
    int radius;
public:
    Circle();
    Circle(int _x, int _y, int _radius, std::string _color);
    Circle(std::vector<std::string> figureData);
    void print() const;
    void translate(int _x, int _y);
    void within(std::vector<std::string> figureData);
    void save(std::ostream& os );
    bool operator==(const Circle& otherCircle) const;
    Circle& operator=(const Circle& otherCircle);
};

#endif //SVG_CIRCLE_H
