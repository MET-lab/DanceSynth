/*
 * JSONSequenceAnalyzer.cpp
 * Written by: Mark Koh
 * DARwIn-OP Dance Synthesis Project
 * 06/04/2013
 *
 * Description: This class takes a file with either a JSON or proprietary sequence list and loads them 
 * into a SequenceTable.
 *
 */

#include "JSONSequenceAnalyzer.h"

using namespace std;


//-------------------------------------------------  
//-------------- Constructors ---------------------  
//-------------------------------------------------  
JSONSequenceAnalyzer::JSONSequenceAnalyzer() {

  //Initialize anything that we need to initialize here

   //The user will need to load a file now using the load function
}


JSONSequenceAnalyzer::JSONSequenceAnalyzer(string fileName) {
  parse(fileName);

}

//-------------------------------------------------  
//-------------- Destructor ---------------------  
//------------------------------------------------- 

JSONSequenceAnalyzer::~JSONSequenceAnalyzer() {

}

//-------------------------------------------------  
//-------------- Inspectors - ---------------------  
//------------------------------------------------- 
/*int JSONSequenceAnalyzer::getNextPosition() const {

}*/


//-------------------------------------------------  
//-------------- Mutators -------------------------  
//------------------------------------------------- 

//This file will load a new file into the Sequence Analyzer and parse it, directing the values into the markov map
//It will return true if the file was successfully loaded and the map was filled
bool JSONSequenceAnalyzer::parse(string filename) {

  //Open the file and 
  _file.open(filename.c_str(), ifstream::in);

  //Make sure we didn't run into any errors openeing the file
  if (! _file.is_open())
  {
    return false;
  }
  _file.close();

  json_t *json;
  json_error_t error;

  json = json_load_file(filename.c_str(),0,&error);

  if (!json) {
	  cout<<"Error loading JSON file: "<<error.text<<endl;
	  cout<<"Line: "<<error.line<<", Column: "<<error.column<<endl;
	  return false;
  }

  if (!json_is_array(json)){
	cout<<"Error in JSON formatting."<<endl;
	return false;
  }

  json_t *bases = json_object_get(json, "bases");

  if(!json_is_array(bases)){
	  cout<<"Base positions unable to be read as an array."<<endl;
	  return false;
  }

  cout<<"Success!"<<endl;

  //IgnoreComments(_file);
  
  //We assume the first [non-commented] line is base positions
  /*string line;
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
  */

  //The file was successfully loaded!  Return true.
  return true;

}


