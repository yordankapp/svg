#include <iostream>
#include <cmath>
#include "Circle.h"
#include "string"

Circle::Circle() {

}

Circle::Circle(int _x, int _y, int _radius, std::string _color) : Figure(_x, _y, _color){
  radius = _radius;
}

Circle::Circle(std::vector<std::string> figureData) : Circle(atoi(figureData[1].c_str()), atoi(figureData[2].c_str()), atoi(figureData[3].c_str()), figureData[4]){
  
}

void Circle::print() const{
    std::cout<<"circle "<<x<<" "<<y<<" "<<radius<<" "<<color<<std::endl;
}

void Circle::translate(int _x, int _y){
    x += _x;
    y += _y;
}

void Circle::within( std::vector<std::string> figureData){
    char figureNameFirstLetter = figureData[0][0];

    if(figureNameFirstLetter == 'r'){
        if( abs(atoi(figureData[1].c_str()) - this->x) >= this->radius && 
            abs(atoi(figureData[2].c_str()) - this->y) >= this->radius &&
            abs(atoi(figureData[3].c_str()) + atoi(figureData[1].c_str()) - this->x) >= this->radius &&
            abs(atoi(figureData[4].c_str()) + atoi(figureData[2].c_str()) - this->y) >= this->radius){
            this->print();
        }
    }
    else if(figureNameFirstLetter == 'c'){
        if(sqrt(pow(atoi(figureData[1].c_str()) - this->x,2) + pow(atoi(figureData[2].c_str()) - this->y,2)) + 
            this->radius <= atoi(figureData[3].c_str())){
            this->print();
        }
    }
}
void Circle::save(std::ostream& os){
    std::string circle = "  <circle cx=\"" + std::to_string(this->x) + "\" cy=\"" + std::to_string(this->y) + 
                         "\" r=\"" + std::to_string(this->radius) + "\" fill=\"" + this->color + "\" />\n";
    os<<circle;
}

bool Circle::operator==(const Circle& otherCircle) const{
  return (Figure::operator==(otherCircle)) && (this->radius == otherCircle.radius);
}

Circle& Circle::operator=(const Circle& otherCircle){
  if(this != &otherCircle){
    this->x = otherCircle.x;
    this->y = otherCircle.y;
    this->radius = otherCircle.radius;
    this->color = otherCircle.color; 
  }
  return *this;
}
