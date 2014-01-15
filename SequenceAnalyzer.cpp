/*
 * sequenceAnalyzer.cpp
 * Written by: Mark Koh
 * DARwIn-OP Dance Synthesis Project
 * 06/04/2013
 *
  * Description: This class takes a file with line-separated lists
 * of comma-separated "dance positions" and loads them into a markov table.
 *
 * 
 * The first line of the file will list, comma separated list of base positions.
 * Any line starting with a "#" will be discarded as a comment.
 *
 */

#include "SequenceAnalyzer.h"

using namespace std;


//-------------------------------------------------  
//-------------- Constructors ---------------------  
//-------------------------------------------------  
SequenceAnalyzer::SequenceAnalyzer() {

  //Initialize anything that we need to initialize here

   //The user will need to load a file now using the load function
}


SequenceAnalyzer::SequenceAnalyzer(string fileName) {
  load(fileName);

}

//-------------------------------------------------  
//-------------- Destructor ---------------------  
//------------------------------------------------- 

SequenceAnalyzer::~SequenceAnalyzer() {

}

//-------------------------------------------------  
//-------------- Inspectors - ---------------------  
//------------------------------------------------- 
int SequenceAnalyzer::getNextPosition() const {

}


//-------------------------------------------------  
//-------------- Mutators -------------------------  
//------------------------------------------------- 

//This file will load a new file into the Sequence Analyzer and parse it, directing the values into the markov map
//It will return true if the file was successfully loaded and the map was filled
bool SequenceAnalyzer::load(string fileName) {
  
  //Clear the current position map
  _positionMap.clear();

  //Open the file and 
  _file.open(fileName.c_str(), ifstream::in);

  //Make sure we didn't run into any errors openeing the file
  if (! _file.is_open())
  {
    return false;
  }
  
  IgnoreComments(_file);
  
  //We assume the first [non-commented] line is base positions
  string line;
  getline(_file,line);

  cout << "Base positions: " << line <<endl;

  IgnoreComments(_file);

  cout<< "Dance Sequences: " << endl;

  while (!_file.eof())
  {
    //string line = _file.getLine();
    getline(_file,line);

    cout<< line << endl;

    IgnoreComments(_file);
  }


  cout << "Done reading file."<<endl;


  //The file was successfully loaded!  Return true.
  return true;

}


//Ignore commented lines
void IgnoreComments(ifstream & file) {
  string scrap;
  //Process file until next non-commented line
  while (!file.eof() && file.peek() == '#') {
    //file.getline();
    //file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(file,scrap);
  }
}


//Test main
int main(int argc, char* argv[]) {
  cout<< "**Sequence Analyzer Test**"<<endl;

  if (argc < 1) {
    return -1;
  }

  SequenceAnalyzer* s = new SequenceAnalyzer(argv[1]);

  return 0;
}
