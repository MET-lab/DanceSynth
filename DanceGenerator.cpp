/*
 * DanceGenerator.h
 * Written by: Mark Koh
 * DARwIn-OP Dance Synthesis Project
 * 06/04/2013
 *
 * Description: This object takes a ssequenceTable and uses it to generate dances
 * based as a state-based machine.
 * 
 */

#include "DanceGenerator.h"

using namespace std;


//-------------------------------------------------  
//-------------- Constructors ---------------------  
//-------------------------------------------------  
DanceGenerator::DanceGenerator(SequenceTable table) {

  //Initialize anything that we need to initialize here
  _table = table;
  init();
}

//-------------------------------------------------  
//-------------- Destructor ---------------------  
//------------------------------------------------- 

DanceGenerator::~DanceGenerator() {

}

//-------------------------------------------------  
//-------------- Inspectors - ---------------------  
//------------------------------------------------- 
void DanceGenerator::init(){
  int pos = _table.getRandomBase();
  _currentPos = pos;
  _atBase = true;
}

int DanceGenerator::currentPos(){
  return _currentPos;
}

//-------------------------------------------------  
//-------------- Mutators -------------------------  
//------------------------------------------------- 
int DanceGenerator::next() {
  int pos;
  if(_atBase){
    //We're at a base, switch to a move
    pos = (int)_table.getRandomMove();
    _atBase = false;
  }
  else {
    //We're at a move, get a random sequential move
    pos = _table.getRandomNext(_currentPos);
    if (pos == -1){
      //We're at the end of the line, switch back to a base position
      pos = _table.getRandomBase();
      _atBase = true;
    }
  }

  //Update the current move
  _currentPos = pos;

  return _currentPos;
}

void DanceGenerator::setPos(int pos){
  if (_table.isMove(pos)){
    _currentPos = pos;
    _atBase = false;
  }
  else if (_table.isBase(pos)){
    _currentPos = pos;
    _atBase = true;
  }

}

bool DanceGenerator::atBase() const{
  return _atBase;
}
