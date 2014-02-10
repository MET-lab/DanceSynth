/*
 * JSONSequenceAnalyzer.h
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

#ifndef JSONSequenceAnalyzer_H
#define JSONSequenceAnalyzer_H


//-----------------------------------------------------------------------------
//------------------------ Dependencies ---------------------------------------
//-----------------------------------------------------------------------------

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <jansson.h>
#include "SequenceAnalyzer.h"

using namespace std;

//-----------------------------------------------------------------------------
//------------------------ Global Variables -----------------------------------
//-----------------------------------------------------------------------------

  //None yet
  
//-----------------------------------------------------------------------------
//------------------------ Class Declaration ----------------------------------
//-----------------------------------------------------------------------------

class JSONSequenceAnalyzer : public SequenceAnalyzer {
  public:
    //-------------------------------------------------  
    //-------------- Constructors ---------------------  
    //-------------------------------------------------  
    JSONSequenceAnalyzer();
    JSONSequenceAnalyzer(string filename);

    //-------------------------------------------------  
    //-------------- Destructor ---------------------  
    //------------------------------------------------- 
    ~JSONSequenceAnalyzer();

    //-------------------------------------------------  
    //-------------- Inspectors - ---------------------  
    //------------------------------------------------- 


    //-------------------------------------------------  
    //-------------- Mutators -------------------------  
    //------------------------------------------------- 
    void addSequence(string sequence);
	bool parse(string filename);

  protected:
    void analyzeSequence(int prefix, json_t* seqence);
    void analyzeOr(int prefix, json_t* list);
};

#endif
