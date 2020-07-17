#include <iostream>
#include "Rectangle.h"
#include "string"

Rectangle::Rectangle(){

}
Rectangle::Rectangle(int _x, int _y, int _width, int _height, std::string _color) : Figure(_x, _y, _color){
    width = _width;
    height = _height;
}
Rectangle::Rectangle(std::vector<std::string> figureData) :
   Rectangle(atoi(figureData[1].c_str()), atoi(figureData[2].c_str()), atoi(figureData[3].c_str()), atoi(figureData[4].c_str()), figureData[5]){

   }

void Rectangle::print() const{
    std::cout<<"rectangle "<<x<<" "<<y<<" "<<width<<" "<<height<<" "<<color<<std::endl;
}

void Rectangle::translate(int _x, int _y){
    x += _x;
    y += _y;
}

void Rectangle::within(std::vector<std::string> figureData){
    char figureNameFirstLetter = figureData[0][0];
    
    if(figureNameFirstLetter == 'r'){
        if(atoi(figureData[1].c_str()) + atoi(figureData[3].c_str()) >= this->x + this->width &&
           atoi(figureData[2].c_str()) + atoi(figureData[4].c_str()) >= this->y + this->height){
            this->print();
        }
    }
    else if (figureNameFirstLetter == 'c'){
        int c1 = atoi(figureData[1].c_str()) ;
        int c2 = atoi(figureData[2].c_str()) ;
        int r = atoi(figureData[3].c_str()) ;
        int dx = c1 - x >= x + width + height - c1 ? c1 - x : x + width + height - c1;
        int dy = c2 - y + width >= y + height - c2 ? c2 - y + width : y + height - c2;

        if(r * r >= dx * dx + dy * dy){
            this->print();
        }
    }
}
void Rectangle::save(std::ostream& os){
    std::string rectangle = "  <rect x=\"" + std::to_string(this->x) + 
                        "\" y=\"" + std::to_string(this->y) + 
                        "\" width=\"" + std::to_string(this->width) + 
                        "\" height=\"" + std::to_string(this->height) + 
                        "\" fill=\"" + this->color + "\" />\n";

    os<<rectangle;
}

bool Rectangle::operator==(const Rectangle& otherRectangle) const{
  return (Figure::operator==(otherRectangle)) && 
           (this->width == otherRectangle.width) &&
           (this->height == otherRectangle.height);
}

Rectangle& Rectangle::operator=(const Rectangle& otherRectangle){
  if(this != &otherRectangle){
    this->x = otherRectangle.x; 
    this->y = otherRectangle.y;
    this->width = otherRectangle.width;
    this->height = otherRectangle.height;
    this->color = otherRectangle.color;
  }
  return *this;
}