#include <iostream>
#include "Figure.h"
#include "string"

Figure::Figure(){

}

Figure::Figure(int _x, int _y, std::string _color){
    x = _x;
    y = _y;
    color = _color;
}
void Figure::print() const {

}

void Figure::translate(int _x, int _y) {

}

void Figure::within(std::vector<std::string> figureData) {

}

void Figure::save(std::ostream& os){

}

bool Figure::operator==(const Figure& otherFigure) const{
  return (this->x == otherFigure.x) && 
         (this->y == otherFigure.y) && 
         (this->color == otherFigure.color); 
}

Figure& Figure::operator=(const Figure& otherFigure){
  if(this != &otherFigure){
    this->x = otherFigure.x;
    this->y = otherFigure.y;
    this->color = otherFigure.color;
  }
  return *this;
}
