#ifndef SVG_FIGURE_H
#define SVG_FIGURE_H
#include "string"
#include <vector>

class Figure{
protected:
    int x;
    int y;
    std::string color;
public:
    Figure();
    Figure(int _x, int _y, std::string _color);
    virtual void print() const;
    virtual void translate(int _x, int _y);
    virtual void within(std::vector<std::string> figureData);
    virtual void save(std::ostream& os);
};

#endif //SVG_FIGURE_H
