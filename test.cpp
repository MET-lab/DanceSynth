#include <iostream>
#include "SequenceTable.h"
#include "SequenceAnalyzer.h"
#include "JSONSequenceAnalyzer.h"
#include "DanceGenerator.h"

using namespace std;

/*
//Test main
int main(int argc, char* argv[]) {




return 0;
}*/

void TestSequenceTable();
void TestSequenceAnalyzer(string filename);


//Test main
int main(int argc, char* argv[]) {
	
	/*
	if (argc < 1) {
		cout<<"Usage:\n $ "<<argv[0]<<" <sequence_filename>"<<endl;
		return -1;
	}
	*/
	
  JSONSequenceAnalyzer sa(argv[1]);


  sa.printTable(cout);

  DanceGenerator dg(sa.getSequenceTable());

  char c;
  cout<<"Keep pressing enter to spit out a move.  Enter '.' to quit."<<endl;
  do {
    cout<<"Move:"<<dg.currentPos();
    if (dg.atBase())
      cout<<endl<<"***Reset to base***";
    dg.next();
    c=getchar();
  } while(c != '.');

  
	return 0;
}


void TestSequenceTable() {
	cout<< "**Sequence Table Test**"<<endl;

	SequenceTable st;

	//Add some base positions
	st.addBase(100);
	st.addBase(101);
	st.addBase(102);

	//Add some moves
	st.addMove(110,111);
	st.addMove(110,112);
	st.addMove(112,114);
	st.addMove(112,115);
	st.addMove(114,115);
	st.addMove(112,118);

	st.print(cout);
}

void TestSequenceAnalyzer(string filename) {
	cout<< "**Sequence Analyzer Test**"<<endl;

	JSONSequenceAnalyzer s(filename);

  s.printTable(cout);

  
}
