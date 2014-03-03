/*
 * SequenceTable.cpp
 * Written by: Mark Koh
 * DARwIn-OP Dance Synthesis Project
 * 1/29/2014
 *
 * Description: This class contains an array and a map which creates a markov table linking sequences
 * dance positions together.  The bases vector contains a number of different base positions which will be
 * returned if a dance move sequence reaches NULL.
 *
 */

#include "SequenceTable.h"

using namespace std;


//-------------------------------------------------  
//-------------- Constructors ---------------------  
//-------------------------------------------------  
SequenceTable::SequenceTable() {

  //Initialize anything that we need to initialize here

  //Initialize the random variable
  srand(time(NULL));
}

//-------------------------------------------------  
//-------------- Destructor ---------------------  
//------------------------------------------------- 

SequenceTable::~SequenceTable() {
  //Any cleanup (freeing of dynamic memory?)
}

//-------------------------------------------------  
//-------------- Inspectors - ---------------------  
//------------------------------------------------- 
int SequenceTable::numBases() const {
  return _bases.size();
}

int SequenceTable::numMoves() const {
  return _moves.size();
}

int SequenceTable::getRandomBase() {
  int r = rand() % numBases();
  return _bases[r];
}

int SequenceTable::getRandomMove() {
  int r = rand() % numMoves();
  return _moves[r];
}


int SequenceTable::getRandomNext(int currentPos) {

  if(std::find(_moves.begin(),_moves.end(),currentPos) != _moves.end()){
    vector<int> possibles = _table[currentPos];
    int r = rand() % possibles.size();
    return possibles[r];
  }
  else
    return -1;

}

bool SequenceTable::isBase(int pos) const {
  bool result = false;
  if(std::find(_bases.begin(),_bases.end(),pos) != _bases.end()){
    result = true;
  }
  return result;
}

bool SequenceTable::isMove(int pos) const {
  bool result = false;
  if(std::find(_moves.begin(),_moves.end(),pos) != _moves.end()){
    result = true;
  }
  return result;
}


//-------------------------------------------------  
//-------------- Mutators -------------------------  
//------------------------------------------------- 

//Add a base position to the bases array
void SequenceTable::addBase(int pos){
  _bases.push_back(pos);
}

//Add a move to the move map
void SequenceTable::addMove(int prefix, int suffix){
  /*if (_table[prefix] == NULL){
  //If the current prefix doesn't exist in the table yet, add it
  _table[prefix] = new vector<int>();	
  }*/

  //If the moves list doesn't already include this prefix, add it
  if(find(_moves.begin(),_moves.end(),prefix) == _moves.end()){
    _moves.push_back(prefix);
  }
  //Add the move to the transition table
  _table[prefix].push_back(suffix);
}

//-------------------------------------------------  
//-------------- Facilitators ---------------------  
//-------------------------------------------------
void SequenceTable::print(ostream &out) {
  out<<"Bases:"<<endl;
  printVector(_bases,out);
  out<<endl;

  out<<"Dance Moves:"<<endl<<"<prefix: suffixes>"<<endl;
  map<int, vector<int> >::iterator i;
  for(i = _table.begin(); i != _table.end(); i++){
    out<< i->first <<": ";
    printVector( i->second, out );
    out<<endl;
  }

}

void printVector(vector<int> list, ostream &out) {
  int size = list.size();
  //cout<<"Base size = "<<size<<endl;
  for (int i=0; i < size-1; i++){
    out<<list[i]<<",";
  }
  out<<list[size-1];
}
