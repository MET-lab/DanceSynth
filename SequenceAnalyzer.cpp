/*
 * SequenceAnalyzer.cpp
 * Written by: Mark Koh
 * DARwIn-OP Dance Synthesis Project
 * 06/04/2013
 *
 * Description: This class takes a file with either a JSON or proprietary sequence list and loads them 
 * into a SequenceTable.
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

//-------------------------------------------------  
//-------------- Destructor ---------------------  
//------------------------------------------------- 

SequenceAnalyzer::~SequenceAnalyzer() {

}

//-------------------------------------------------  
//-------------- Inspectors - ---------------------  
//------------------------------------------------- 
SequenceTable SequenceAnalyzer::getSequenceTable() const {
	return _table;
}


//-------------------------------------------------  
//-------------- Mutators -------------------------  
//------------------------------------------------- 
//void SequenceAnalyzer::addSequence(

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


