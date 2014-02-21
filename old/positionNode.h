/*
 * positionNode.h
 * Written by: Mark Koh
 * DARwIn-OP Dance Synthesis Project
 * 07/02/2013
 *
 * Description: This class is essentially an aggrgation of a few attributes
 * that can hold dance positons.  Its intention is for what is supposed to be
 * pointed to by the sequenceAnalyzer array.
 *
 *
 */

#ifndef POSITIONNODE_H
#define POSITIONNODE_H


#include <vector>

//-----------------------------------------------------------------------------
//------------------------ Global Variables -----------------------------------
//-----------------------------------------------------------------------------

  //None yet
  
//-----------------------------------------------------------------------------
//------------------------ Class Declaration ----------------------------------
//-----------------------------------------------------------------------------

class positionNode {
  public:
    //-------------------------------------------------  
    //-------------- Constructors ---------------------  
    //-------------------------------------------------  
    positionNode();

    //-------------------------------------------------  
    //-------------- Destructor ---------------------  
    //------------------------------------------------- 
    ~postionNode();

    //-------------------------------------------------  
    //-------------- Inspectors - ---------------------  
    //------------------------------------------------- 
    int getSize();
    int genRandomInRange();
    int getNextPosition();

    //-------------------------------------------------  
    //-------------- Mutators -------------------------  
    //------------------------------------------------- 

    //-------------------------------------------------  
    //-------------- Public Vars ----------------------  
    //------------------------------------------------- 
    int positionNumber;
    int size;
    vector<int> nextPositions;

  private:

};

//-----------------------------------------------------------------------------
//------------------------ Class Implementation -------------------------------
//-----------------------------------------------------------------------------

  positionNode::positionNode() {
    nextPosition = new vector<int>();
    size = 0;
    //TODO: Check if random is instantiated yet, if not, instantiate it.
  }


#endif
