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
  _currentMove = pos;
  _atBase = true;
}

int DanceGenerator::currentPos() const{
  return _currentPos;
}

//-------------------------------------------------  
//-------------- Mutators -------------------------  
//------------------------------------------------- 
int DanceGenerator::next() const {
  int pos;
  if(_atBase){
    //We're at a base, switch to a move
    pos = _table.getRandomMove();
    _atBase = false;
  }
  else {
    //We're at a move, get a random sequential move
    pos = _table.getRandomNext(_currentMove);
    if (pos == -1){
      //We're at the end of the line, switch back to a base position
      pos = _table.getRandomBase();
      atBase = true;
    }
  }

  //Update the current move
  _currentPos = pos;

  return _currentPos;
}

void DanceGenerator::setPos(int pos){
  if (_table.isMove(pos)){
    _currentMove = pos;
    _atBase = false;
  }
  else if (_table.isBase(pos)){
    _currentMove = pos;
    _atBase = true;
  }
  
}
