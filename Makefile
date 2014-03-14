###############################################################
#
# Purpose: Makefile for "DanceSynth"
# Author.: Mark Koh
# Version: 0.1
# Date: 1/12/2014
#
###############################################################

TARGET = DanceSynth 

INCLUDE_DIRS = -I../../include -I../../../Framework/include

CXX = g++
CXXFLAGS += -O2 -g -DLINUX -Wall $(INCLUDE_DIRS)
#CXXFLAGS += -O2 -DLINUX -DDEBUG -Wall $(INCLUDE_DIRS)
LFLAGS += -lpthread -ljpeg -lrt -ljansson

OBJECTS =   main.o JSONSequenceAnalyzer.o SequenceTable.o SequenceAnalyzer.o DanceGenerator.o csapp.o

FILE ?=sequences.json

BEATTRACKER = BeatTrackerApp

all: $(TARGET)

clean:
	rm -f *.a *.o core *~ *.so *.lo $(TARGET) $(BEATTRACKER)

darwin.a:
	make -C ../../build
	
$(BEATTRACKER):
	make -C ../beatTracker
	cp ../beatTracker/$(BEATTRACKER) .

$(TARGET): darwin.a $(BEATTRACKER) $(OBJECTS)
	$(CXX) $(CFLAGS) $(LFLAGS) $(OBJECTS) ../../lib/darwin.a -o $(TARGET)
	chmod 755 $(TARGET)

run: $(TARGET)
	./$(TARGET) $(FILE)

# useful to make a backup "make tgz"
tgz: clean
	mkdir -p backups
	tar czvf ./backups/camera_`date +"%Y_%m_%d_%H.%M.%S"`.tgz --exclude backups *
