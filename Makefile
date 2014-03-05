###############################################################
#
# Purpose: Makefile for "action_script"
# Author.: robotis
# Version: 0.1
# License: GPL
#
###############################################################

TARGET = DanceSynth 

INCLUDE_DIRS = -I../../include -I../../../Framework/include

CXX = g++
CXXFLAGS += -O2 -g -DLINUX -Wall $(INCLUDE_DIRS)
#CXXFLAGS += -O2 -DLINUX -DDEBUG -Wall $(INCLUDE_DIRS)
LFLAGS += -lpthread -ljpeg -lrt -ljansson

OBJECTS =   main.o JSONSequenceAnalyzer.o SequenceTable.o SequenceAnalyzer.o DanceGenerator.o csapp.o

FILE ?= sequences.json

TEST_COMPONENTS = test.cpp SequenceAnalyzer.cpp SequenceTable.cpp JSONSequenceAnalyzer.cpp DanceGenerator.cpp

all: $(TARGET)

clean:
	rm -f *.a *.o $(TARGET) core *~ *.so *.lo

darwin.a:
	make -C ../../build
	
BeatTrackerApp.a:
	make -C ../beatTracker
	cp ../beatTracker/BeatTrackerApp .

$(TARGET): darwin.a BeatTrackerApp.a $(OBJECTS)
	$(CXX) $(CFLAGS) $(LFLAGS) $(OBJECTS) ../../lib/darwin.a -o $(TARGET)
	chmod 755 $(TARGET)

run: $(TARGET)
	./$(TARGET) $(FILE)

# useful to make a backup "make tgz"
tgz: clean
	mkdir -p backups
	tar czvf ./backups/camera_`date +"%Y_%m_%d_%H.%M.%S"`.tgz --exclude backups *
