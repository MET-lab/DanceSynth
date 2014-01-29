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
LFLAGS += -lpthread -ljpeg -lrt

OBJECTS =   main.o

all: $(TARGET)

clean:
	rm -f *.a *.o $(TARGET) core *~ *.so *.lo

darwin.a:
	make -C ../../build
	
test: SequenceAnalyzer.o
	SequenceAnalyzer.o sequences.json

SequenceAnalyzer.o: SequenceAnalyzer.cpp SequenceAnalyzer.h
	$(CXX) -o SequenceAnalyzer.o SequenceAnalyzer.cpp


$(TARGET): darwin.a $(OBJECTS)
	$(CXX) $(CFLAGS) $(LFLAGS) $(OBJECTS) ../../lib/darwin.a -o $(TARGET)
	chmod 755 $(TARGET)

# useful to make a backup "make tgz"
tgz: clean
	mkdir -p backups
	tar czvf ./backups/camera_`date +"%Y_%m_%d_%H.%M.%S"`.tgz --exclude backups *
