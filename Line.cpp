#include <iostream>
#include <cmath>
#include "Line.h"
#include "string"

Line::Line(){

}

Line::Line(int _x1, int _y1, int _x2, int _y2, int _width, std::string _color) : Figure(_x1, _y1,  _color){
    x2 = _x2;
    y2 = _y2;
    width = _width;
}

Line::Line(std::vector<std::string> figureData) : Line(atoi(figureData[1].c_str()), atoi(figureData[2].c_str()), atoi(figureData[3].c_str()), atoi(figureData[4].c_str()), atoi(figureData[5].c_str()), figureData[6]){

}

void Line::print() const{
  std::cout<<"line "<<x<<" "<<y<<" "<<x2<<" "<<y2<<" "<<width<<" "<<color<<std::endl;
}

void Line::translate(int _x1, int _y1){
    x += _x1;
    y += _y1;
    x2 += _x1;
    y2 += _y1;
}

void Line::within(std::vector<std::string> figureData){
  char figureNameFirstLetter = figureData[0][0];

  if(figureNameFirstLetter == 'r'){
    if(atoi(figureData[1].c_str()) <= this->x && this->x <= atoi(figureData[1].c_str()) + atoi(figureData[3].c_str()) &&
       atoi(figureData[2].c_str()) <= this->y && this->y <= atoi(figureData[2].c_str()) + atoi(figureData[4].c_str()) && 
       atoi(figureData[1].c_str()) <= this->x2 && this->x2 <= atoi(figureData[1].c_str()) + atoi(figureData[3].c_str()) && 
       atoi(figureData[2].c_str()) <= this->y2 && this->y2 <= atoi(figureData[2].c_str()) + atoi(figureData[4].c_str())){
          this->print();
        }
    }
  else if(figureNameFirstLetter == 'c'){
    if(sqrt(pow(atoi(figureData[1].c_str()) - this->x,2) + pow(atoi(figureData[2].c_str()) - this->y,2)) <= atoi(figureData[3].c_str()) && 
       sqrt(pow(atoi(figureData[1].c_str()) - this->x2,2) + pow(atoi(figureData[2].c_str()) - this->y2,2)) <= atoi(figureData[3].c_str())){
          this->print();
      }
    }
}

void Line::save(std::ostream& os ){
  std::string line = "  <line x1=\"" + std::to_string(this->x) + "\" y1=\"" + std::to_string(this->y) + 
                 "\" x2=\"" + std::to_string(this->x2) + "\" y2=\"" + std::to_string(this->y2) + 
                 "\" width=\"" + std::to_string(this->width) + 
                 "\" fill=\"" + this->color + "\" />\n";
  os<<line;
}
