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

  //Decalare our json types
  json_t *root, *bases, *sequences;
  json_error_t error;


  //Read the root from the file
  root = json_load_file(filename.c_str(),0,&error);

  //Do some error checking
  if (!root) {
    cout<<"Error loading JSON file: "<<error.text<<endl;
    cout<<"Line: "<<error.line<<", Column: "<<error.column<<endl;
    return false;
  }
  if (!json_is_object(root)){
    cout<<"Error in JSON formatting."<<endl;
    return false;
  }

  //Grab our bases and sequences
  bases = json_object_get(root, "bases");
  sequences = json_object_get(root, "sequences");


  //Some more error checking (just make sure everything is as expected)
  if(!json_is_array(bases) || !json_is_array(sequences)){
    cout<<"Base positions unable to be read as an array."<<endl;
    return false;
  }

  //Handle the base positions
  int numBases = json_array_size(bases);

  //cout<<"Base positions read: "<<endl;
  for (int i=0; i<numBases;i++){
    json_t *pos = json_array_get(bases,i);
    if (json_is_integer(pos)){
      int unpacked;
      json_unpack(pos,"i",&unpacked);
      //cout<<unpacked<<",";
      _table.addBase(unpacked);
    }
  }
  cout<<endl;

  //Handle the base positions
  int numSequences = json_array_size(sequences);

  for (int i=0; i<numSequences;i++){
    json_t *bundle = json_array_get(sequences,i);
    if (json_is_object(bundle)){
      const char *name;
      json_t *json_name = json_object_get(bundle,"name");
      json_t *sequence = json_object_get(bundle,"sequence");

      if (json_is_string(json_name) && json_is_array(sequence)){
        json_unpack(json_name,"s",&name);

        int length = json_array_size(sequence); 

        //Analyze sequence with NULL for prefix
        analyzeSequence(sequence);

        //cout<<"Sequence read: "<<name<<", Sequence length of "<<length<<endl;

      }


    }
  }
  cout<<endl;

  //The file was successfully loaded!  Return true.
  return true;

}


//Given a sequence (with potentialy nested arrays), this function will add moves to the
//sequence table 
void JSONSequenceAnalyzer::analyzeSequence(json_t* sequence) {
  //from i=0 to length-1
  //Add the current element and the next element

  if (json_is_array(sequence)){

    //Call linkpair on the rest of the array
    int size = json_array_size(sequence);
    for (int i=0; i<size-1; i++) {
      json_t *pre  = json_array_get(sequence, i);
      json_t *post = json_array_get(sequence, i+1); 

      linkPair(pre,post);
    }
  }
}


//This will check to see if the prefix and postfixes are various types
void JSONSequenceAnalyzer::linkPair(json_t* prefix, json_t* postfix){

  if (json_is_integer(prefix) && json_is_integer(postfix)) {
    //Link the prefix and postfix
    int pre, post;
    json_unpack(prefix,"i",&pre);
    json_unpack(postfix,"i",&post);
    _table.addMove(pre,post);
  }
  else  {
    cout<<"Error: Non-integer value found in sequence."<<endl;
  }
}

void JSONSequenceAnalyzer::printTable(ostream &out){
  _table.print(cout);
}
