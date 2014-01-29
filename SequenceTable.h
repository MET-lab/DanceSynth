/*
 * SequenceTable.h
 * Written by: Mark Koh
 * DARwIn-OP Dance Synthesis Project
 * 06/04/2013
 *
 * Description: This class contains an array and a map which creates a markov table linking sequences
 * dance positions together.  The bases vector contains a number of different base positions which will be
 * returned if a dance move sequence reaches NULL.
 *
 */

#ifndef SEQUENCETABLE_H
#define SEQUENCETABLE_H


//-----------------------------------------------------------------------------
//------------------------ Dependencies ---------------------------------------
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------
//------------------------ Global Variables -----------------------------------
//-----------------------------------------------------------------------------

  //None yet
  
//-----------------------------------------------------------------------------
//------------------------ Class Declaration ----------------------------------
//-----------------------------------------------------------------------------

class SequenceTable {
  public:
    //-------------------------------------------------  
    //-------------- Constructors ---------------------  
    //-------------------------------------------------  
    SequenceTable();

    //-------------------------------------------------  
    //-------------- Destructor ---------------------  
    //------------------------------------------------- 
    ~SequenceTable();

    //-------------------------------------------------  
    //-------------- Inspectors - ---------------------  
    //------------------------------------------------- 
    vector<int> getSuffixes(int pos);
	int numMoves() const;
	int numBases() const;

    //-------------------------------------------------  
    //-------------- Mutators -------------------------  
    //------------------------------------------------- 
    void addBase(int pos);
	void addMove(int prefix, int postfix);

	//-------------------------------------------------  
    //-------------- Facilitators----------------------  
    //------------------------------------------------- 
	void print(ostream &out);

  private:
    vector<int> _bases;
    map<int, vector<int> > _table;


};

void printVector(vector<int> list, ostream &out);

#endif
