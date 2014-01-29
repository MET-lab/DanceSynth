#include <iostream>
#include "SequenceTable.h"
//#include "SequenceAnalyzer.h"

using namespace std;

/*
//Test main
int main(int argc, char* argv[]) {
  cout<< "**Sequence Analyzer Test**"<<endl;

  if (argc < 1) {
	  cout<<"Usage:\n $ "<<argv[0]<<" <sequence_filename>"<<endl;
    return -1;
  }

  SequenceAnalyzer s = new SequenceAnalyzer(argv[1]);



  return 0;
}*/

//Test main
int main(int argc, char* argv[]) {
  cout<< "**Sequence Table Test**"<<endl;

	SequenceTable st;

	st.addBase(100);
	st.addMove(110,112);

	st.print(cout);

  return 0;
}
