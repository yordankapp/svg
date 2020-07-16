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

void CommandDispatcher::takeCommand(std::string _command){
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
    for (int i = 0; i < numberOfFigures; i++){
        figures[i]->print();
    }
}

void CommandDispatcher::setUserFileName(std::string command){
  std::vector<std::string> splitCommand = splitLineBySpace(command);
  userFileName = splitCommand[1];
}

void CommandDispatcher::addFigure(std::vector<std::string>& figureData){
 char  figureNameFirstLetter = figureData[0][0];
 switch(figureNameFirstLetter){  
    case 'r': {
      Rectangle* newFigure = new Rectangle(figureData);
      figures.push_back(newFigure);
      numberOfFigures++;
      break;
    }
    case 'c': {
      Circle* newFigure = new Circle(figureData);
      figures.push_back(newFigure);
      numberOfFigures++;
      break;
    }
    case 'l': {
      Line* newFigure = new Line(figureData);
      figures.push_back(newFigure);
      numberOfFigures++;
      break;
    }
    default: {
      break;
    }
  }
}

void CommandDispatcher::convertLineFromFile(std::string& line){
  std::string convertedLine = "";

  std::string substring(line);
  unsigned findNameFirstDelimiter = substring.find("<");
  unsigned findNameLastDelimiter = substring.find(" ", findNameFirstDelimiter);
  std::string figureName = substring.substr(findNameFirstDelimiter + 1,findNameLastDelimiter - findNameFirstDelimiter - 1);
  convertedLine += figureName;
  convertedLine += " ";
  
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
      convertedLine += characteristic;
      convertedLine += " "; 
    }
    else{
      position++;
    }
  }
  line = convertedLine;
}

void CommandDispatcher::setFigureDataFromLineOrCommand(std::vector<std::string>& figureData, std::string line){
  std::vector<std::string> dataFromLine = splitLineBySpace(line);
  std::string command = dataFromLine[0];
  if(command == "within"){
    // erase the command name
    dataFromLine.erase(dataFromLine.begin());
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
    if (numberOFLines > 3){
      convertLineFromFile(line); 
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
    std::cout << "Successfully created " << figureName << " (" << numberOfFigures << ")" << std::endl;
}

void CommandDispatcher::translate(std::string _command){
    std::string figureData[3];
    int numberOfCharacteristics = 0;
    
    _command += ' ';
    int position = 9;

    while(_command[position] != '\0'){

        if (_command[position] == ' '){
            std::string characteristic = "";
            position++;

            while(_command[position] != ' ' && _command[position] != '\0'){
                char character = _command[position];
                characteristic += character;
                position++;
            }

            figureData[numberOfCharacteristics] = characteristic;
            numberOfCharacteristics++;
        }
    }

    if(atoi(figureData[2].c_str()) != 0){ // за транслиране на всички фигури използвай 0 
        int p;
        p = atoi(figureData[2].c_str());
        figures.at(p-1)->translate(atoi(figureData[0].c_str()), atoi(figureData[1].c_str()));
        std::cout << "Successfully translated a figure " << std::endl;
    }
    else{
        for (int j = 0; j < numberOfFigures; j++)
        {
            figures.at(j)->translate(atoi(figureData[0].c_str()), atoi(figureData[1].c_str()));
        }
        std::cout << "Successfully translated all figures " << std::endl;
    }

}

void CommandDispatcher::within(std::string _command){
  std::vector<std::string> figureData; 
  setFigureDataFromLineOrCommand(figureData, _command);
  for (int j = 0; j < numberOfFigures; j++){
    figures.at(j)->within(figureData);
  }
}

void CommandDispatcher::erase(std::string command){
  std::vector<std::string> splitCommand = splitLineBySpace(command);
  int indexOfFigureToErase = atoi(splitCommand[1].c_str());
  if(indexOfFigureToErase <= figures.size()){
      figures.erase(figures.begin() + indexOfFigureToErase - 1);
      numberOfFigures--;
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
    
    for (int i = 0; i < numberOfFigures; ++i){
      figures.at(i)->save(file);
    }

    file << "</svg>";
    file.close();
    std::cout << "Successfully saved in"<< userFileName << std::endl;

}
void CommandDispatcher::exit() const{
  std::cout << "Exit" << std::endl;
}
