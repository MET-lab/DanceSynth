DanceSynth
==========

You can find photos of all of the dance moves on the wiki for this GitHub: https://github.com/MET-lab/DanceSynth/wiki

###Description
  This project uses David Grunberg's BeatTracker (https://github.com/MET-lab/BeatTracker) along with an adapted Markov-Chain algorithm to make DARwIn dance to the beat of music.  The DanceSynth is separated into modules to allow for scaling of the project to other mediums. 
  It currently uses a SequenceAnalyzer to read in sequences from a file and put them into a Markov-table, which is then used by the DanceGenerator which uses the probabilities in the sequences to determine the most likely next dance move to go to.  The system can be looked at from a higher level as a probablistic state machine.  The DanceSynth program now spawns an instance of the BeatTracker (previously you had to run them separately) and communicates with it through a UDP connection.
  *Note: The JSONSequenceAnalyzer uses a C libary called jansson to parse the JSON.  You can find this library at http://www.digip.org/jansson/*
  

###Running the DanceSynth
You may compile the program using make:
```
$ make
```
**(Note: Any make command WILL build the BeatTracker as well, so make sure that it is in a good state before running)**
and run it using the default sequences file (*sequences.json*)
```
$ make run
```
This can be run with a custom input file as
```
$ ./DanceSynth <filename>
OR
$ make run FILE=<filename>
```

###Sequences
The program can read in sequences from any JSON file, but I'd recommend sticking with *sequences.json*.  A sequence file is defined by the following structure:
```
{
  "bases":[101,102,103],
  "sequences":[
    {
      "name":"sequence_1",
      "sequence":[111,115,126,118,120]
    },
    {
      "name":"sequence_2",
      "sequence":[122,114,126,118,130]
    },
    ...
  ]
}
```
Note that the root of the structure has a "bases" attribute and a "sequences" attribute.  The base moves are used whenever the current state is one for which there are no moves which follow it in any of the training sequences.
From there, each sequence has a name and a sequence definition.  The sequence definitions can be as long as you'd like.

##Current state (and where to go from here)
###Mark, 3/14/2014
#####Code/Algorithm status
  The code for the project at the moment is healty, which is good. Everything compiles, it's pretty modular, all good stuff.  Where we could use some work is we need to be careful of repetiton in sequences because if there are 20 sequnces were he moves from move a->b and one sequence where he moves from a->c, then he will *very* rarely go to c.  My thought on this is to modify the DanceGenerator so that it determines the next move based on a log factor of the next possible states.  To do this, we'll need to refactor the DanceGenerator to select the next move differently.  Keep in mind that the beats don't come nearly as fast as the CPU can do basic math, so as long as we don't have thousands of sequences and moves, we should be alright with a little more grunt per move selection.
####Training data expansion
Currently, the DanceSynth is in pretty good shape.  What it really lacks is good sequences.  The more sequences that DARwIn has to work from, the more realistic and smoother his dancing looks. So, there are a few things that I'd like to do with the training data library.  Firstly, I'd like to expand it - get some more sequences in there, as well as more moves into his position library.  One way to do this would be to build a site that generates moves based on an image point-and-click interface.  The more visual the better.  Otherwise, just think of moves and dances, and place them in manually.

###Contact
Any questions, please contact Mark Koh(mkoh@drexel.edu)
