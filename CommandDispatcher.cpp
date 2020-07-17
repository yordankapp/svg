#include <iostream>
#include <fstream>
#include <sstream>
#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(){
    
}

std::vector<std::string> CommandDispatcher::splitLineBySpace(std::string line){
  std::istringstream iss(line);
  std::vector<std::string> splitLine;
  std::string word;
  while(getline( iss, word, ' ')) {
    splitLine.push_back(word.c_str());
  }
  return splitLine;
}

void CommandDispatcher::execute(std::string _command){
  std::vector<std::string> splitCommand = splitLineBySpace(_command);
  std::string commandName = splitCommand[0];

  if(commandName == "open"){
    open(_command); 
  }
  else if(commandName == "print"){
    print(); 
  }
  else if(commandName == "create"){
    create(_command); 
  }
  else if(commandName == "translate"){
    translate(_command); 
  }
  else if(commandName == "within"){
    within(_command); 
  }
  else if(commandName == "erase"){
    erase(_command); 
  }
  else if(commandName == "save"){
    save(); 
  }
  else if(commandName == "exit"){
    exit(); 
  }
}

void CommandDispatcher:: print() const{
  for (int i = 0; i < figures.size(); i++){
    figures[i]->print();
  }
}

void CommandDispatcher::setUserFileName(std::string command){
  std::vector<std::string> splitCommand = splitLineBySpace(command);
  userFileName = splitCommand[1];
}

Figure* CommandDispatcher::createFigure(std::vector<std::string> figureData){
  std::string figureName = figureData[0];
  Figure* newFigure;
  if(figureName == "rectangle"){
    newFigure = new Rectangle(figureData);
  }  
  else if(figureName == "circle"){
    newFigure = new Circle(figureData);
  }
  else if(figureName == "line"){
    newFigure = new Line(figureData);
  }
  return newFigure;
}

void CommandDispatcher::addFigure(std::vector<std::string>& figureData){
  Figure* figure = createFigure(figureData);
  figures.push_back(figure);
}

void CommandDispatcher::simplifyLineFromFile(std::string& line){
  std::string simplifiedLine = "";

  std::string substring(line);
  unsigned findNameFirstDelimiter = substring.find("<");
  unsigned findNameLastDelimiter = substring.find(" ", findNameFirstDelimiter);
  std::string figureName = substring.substr(findNameFirstDelimiter + 1,findNameLastDelimiter - findNameFirstDelimiter - 1);
  simplifiedLine += figureName;
  simplifiedLine += " ";
  
  int position = 0;
  while(line[position] != '>'){
    if(line[position] == '\"'){
      std::string characteristic = "";
      position++;
      while(line[position] != '\"'){
        char character = line[position];
        characteristic += character;
        position++;
      }
      position++;
      simplifiedLine += characteristic;
      simplifiedLine += " "; 
    }
    else{
      position++;
    }
  }
  line = simplifiedLine;
}

void CommandDispatcher::setFigureDataFromLineOrCommand(std::vector<std::string>& figureData, std::string line){
  std::vector<std::string> dataFromLine = splitLineBySpace(line);
  std::string command = dataFromLine[0];
  if(command == "within"){
    // erase the command name
    dataFromLine.erase(dataFromLine.begin());
    figureData = dataFromLine;
  }
  else if(command == "translate"){
    // erase the command name
    dataFromLine.erase(dataFromLine.begin());

    // erase the parameters
    dataFromLine.erase(dataFromLine.end() - 1);
    dataFromLine.erase(dataFromLine.end() - 1);
    figureData = dataFromLine;
  }
  else{
    figureData = dataFromLine;
  }
}

void CommandDispatcher::open(std::string _command){
  setUserFileName(_command);
  std::fstream file(userFileName);
  std::string line;
  int numberOFLines = 0;

  while(getline(file, line)){
  std::vector<std::string> figureData; 
        
  //skip the first 3 lines in the file
  if (numberOFLines > 3 && line != "</svg>"){
    simplifyLineFromFile(line); 
    setFigureDataFromLineOrCommand(figureData, line);
    addFigure(figureData);
  }
  else{
    numberOFLines++;
    }
  }
  std::cout << "Successfully opened " << userFileName << std::endl;
}

void CommandDispatcher::create(std::string _command){
  std::vector<std::string> figureData; 
    
  setFigureDataFromLineOrCommand(figureData, _command);
  addFigure(figureData);

  std::string figureName = figureData[0];
  std::cout << "Successfully created " << figureName << " (" << figures.size() << ")" << std::endl;
}

bool CommandDispatcher::lineContainsFigure(std::vector<std::string> line){
  for(int i = 0; i < line.size(); i++){
    if(line.at(i) == "rectangle" || 
       line.at(i) == "circle" || 
       line.at(i) == "line"){
         return true;
    }
  }
  return false;
}

std::pair<int,int> CommandDispatcher::getParametersForTranslation(std::vector<std::string> line){
  // erase the command name
  line.erase(line.begin());

  std::pair<int,int> parameters;
  if(line.size() > 3){
    int sizeOfLine = line.size();
    parameters.first = atoi(line.at(sizeOfLine - 1).c_str());
    parameters.second = atoi(line.at(sizeOfLine - 2).c_str());
  }
  else{
    parameters.first = atoi(line.at(0).c_str());
    parameters.second = atoi(line.at(1).c_str());
  }
  return parameters;
}

int CommandDispatcher::findFigurePositionInAllFigures(std::vector<std::string> figureData){
  Figure* figure = createFigure(figureData);
  for(int i = 0; i < figures.size(); i++){
    if(*figures[i] == *figure){
      return i;
    }
  }
  return -1;
}

void CommandDispatcher::translateOneFigure(std::vector<std::string> figureData, std::pair<int,int> parameters){
  int figurePosition = findFigurePositionInAllFigures(figureData);
  if(0 <= figurePosition){
    figures.at(figurePosition)->translate(parameters.first, parameters.second);
    std::cout << "Successfully translated a figure " << std::endl;
  }
  else{
    std::cout << "This figure does't exist " << std::endl;
  }
}

void CommandDispatcher::translateAllFigures(std::pair<int,int> parameters){
  for (int j = 0; j < figures.size(); j++){
    figures.at(j)->translate(parameters.first, parameters.second);
  }
  std::cout << "Successfully translated all figures " << std::endl;
}

void CommandDispatcher::translate(std::string _command){
  std::vector<std::string> line = splitLineBySpace(_command);
  std::pair<int,int> parameters = getParametersForTranslation(line);

  if(lineContainsFigure(line)){
    std::vector<std::string> figureData; 
    setFigureDataFromLineOrCommand(figureData, _command);
    translateOneFigure(figureData, parameters);
  }
  else{
    translateAllFigures(parameters);
  }
}

void CommandDispatcher::within(std::string _command){
  std::vector<std::string> figureData; 
  setFigureDataFromLineOrCommand(figureData, _command);

  int numberOfFiguresWithin = 0;
  for (int i = 0; i < figures.size(); i++){
    figures.at(i)->within(figureData);
    numberOfFiguresWithin++;
  }

  if(numberOfFiguresWithin == 0){
    std::cout<<"No figures are located within this figure."<<std::endl;
  }
}

void CommandDispatcher::erase(std::string command){
  std::vector<std::string> splitCommand = splitLineBySpace(command);
  int indexOfFigureToErase = atoi(splitCommand[1].c_str());
  if(indexOfFigureToErase <= figures.size()){
      figures.erase(figures.begin() + indexOfFigureToErase - 1);
      std::cout << "Erased (" << indexOfFigureToErase << ")" << std::endl;
  }
  else{
    std::cout << "There is no figure number " << indexOfFigureToErase << std::endl;
  }
}

void CommandDispatcher::save(){
  std::ofstream file(userFileName, std::ios::trunc);
  std::string text = "<?xml version=\"1.0\" standalone=\"no\"?>\n"
                  "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n"
                  "  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n"
                  "<svg>\n";
  file << text;
    
  for (int i = 0; i < figures.size(); i++){
    figures.at(i)->save(file);
  }

  file << "</svg>";
  file.close();
  std::cout << "Successfully saved the changes in" << userFileName << std::endl;
}
void CommandDispatcher::exit() const{
  std::cout << "Exit" << std::endl;
}
