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

   //The user will need to load a file now using the load function
   //_bases = 
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
	return _table.size();
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
