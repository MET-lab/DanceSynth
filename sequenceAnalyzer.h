/*
 * sequenceAnalyzer.h
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
 *
 */

#ifndef SEQUENCEANALYZER_H
#define SEQUENCEANALYZER_H


//-----------------------------------------------------------------------------
//------------------------ Dependencies ---------------------------------------
//-----------------------------------------------------------------------------

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

//-----------------------------------------------------------------------------
//------------------------ Global Variables -----------------------------------
//-----------------------------------------------------------------------------

  //None yet
  
//-----------------------------------------------------------------------------
//------------------------ Class Declaration ----------------------------------
//-----------------------------------------------------------------------------

class SequenceAnalyzer {
  public:
    //-------------------------------------------------  
    //-------------- Constructors ---------------------  
    //-------------------------------------------------  
    SequenceAnalyzer();
    SequenceAnalyzer(string fileName);

    //-------------------------------------------------  
    //-------------- Destructor ---------------------  
    //------------------------------------------------- 
    ~SequenceAnalyzer();

    //-------------------------------------------------  
    //-------------- Inspectors - ---------------------  
    //------------------------------------------------- 
    int getNextPosition() const;


    //-------------------------------------------------  
    //-------------- Mutators -------------------------  
    //------------------------------------------------- 
    bool load(string fileName);



  private:
    ifstream _file;
    vector<int> _basePositions;
    map<int, vector<int> > _positionMap;


};

#endif
