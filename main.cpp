/*
 * main.cpp
 * Written by: Mark Koh
 * 2/14/2013
 *
 * Description: Based off of the action_script demo written by robotis corp.,
 * this program will recieve UDP packets from a localhost client in order to 
 * execute scripts in sync with the beat of a live audio signal.
 *
 */

#include <unistd.h>
#include <string.h>
#include <string>
#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <signal.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

//#include "Camera.h"
#include "Point.h"
#include "mjpg_streamer.h"
#include "minIni.h"
//#include "LinuxCamera.h"
//#include "ColorFinder.h"

#include "Action.h"
#include "Head.h"
#include "Walking.h"
#include "MX28.h"
#include "MotionManager.h"
#include "LinuxMotionTimer.h"
#include "LinuxCM730.h"
#include "LinuxActionScript.h"

#include "StatusCheck.h"
#include "LinuxDARwIn.h"

//Dance Generator Stuff
#include "SequenceTable.h"
#include "SequenceAnalyzer.h"
#include "JSONSequenceAnalyzer.h"
#include "DanceGenerator.h"
#include "csapp.h"

#ifdef MX28_1024
#define MOTION_FILE_PATH    "../../../Data/motion_1024.bin"
#else
#define MOTION_FILE_PATH    "../../../Data/motion_4096.bin"
#endif

#define INI_FILE_PATH       "../../../Data/config.ini"

#define PORT 9930
#define BUFLEN 70
#define SAMPLE_RATE (44100)

#define INIT_POS 1
#define KILL_POS 15


//Some globals
extern char** environ;
int BeatTrackerPID = 0;

void change_current_dir()
{
  char exepath[1024] = {0};
  if(readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
    chdir(dirname(exepath));
}

void sighandler(int sig)
{
  //Pass the signal onto any program in our process group
  kill(-1,sig);

  struct termios term;
  
  //Return DARwIn to his kill position (sitting)
  Action::GetInstance()->Start(KILL_POS);    /* Init(stand up) pose */
  while(Action::GetInstance()->IsRunning()) usleep(8*1000);
  tcgetattr( STDIN_FILENO, &term );
  term.c_lflag |= ICANON | ECHO;
  tcsetattr( STDIN_FILENO, TCSANOW, &term );

  exit(0);
}


int main(int argc, char* argv[])
{   
  signal(SIGABRT, &sighandler);
  signal(SIGTERM, &sighandler);
  signal(SIGQUIT, &sighandler);
  signal(SIGINT, &sighandler);

  /* Decalre server and socket variables */
  struct sockaddr_in sad; //Structure to hold server IP Address
  struct sockaddr_in cad; //Structure to hold client IP Address
  int serverSocket; //Socket descriptor
  int slen=sizeof(cad);
  char buf[BUFLEN];
  //int buf;
  //struct hostent *ptrh; //Pointer to host table entry


  printf( "\n=====   BeatTracker Dance Script Program   =====\n");
  printf(   "=====               Mark Koh               =====\n\n");

  change_current_dir();

  Action::GetInstance()->LoadFile(MOTION_FILE_PATH);

  //////////////////// Framework Initialize ////////////////////////////
  LinuxCM730 linux_cm730("/dev/ttyUSB0");
  CM730 cm730(&linux_cm730);
  if(MotionManager::GetInstance()->Initialize(&cm730) == false)
  {
    printf("Fail to initialize Motion Manager!\n");
    return 0;
  }
  MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
  MotionManager::GetInstance()->AddModule((MotionModule*)Head::GetInstance());
  MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());

  LinuxMotionTimer *motion_timer = new LinuxMotionTimer(MotionManager::GetInstance());
  motion_timer->Start();
  /////////////////////////////////////////////////////////////////////


  /////////////////// Initialize Motion ///////////////////////////////
  
  minIni* ini = new minIni(INI_FILE_PATH);
  
  MotionManager::GetInstance()->LoadINISettings(ini);
  Action::GetInstance()->m_Joint.SetEnableBody(true, true);
  MotionManager::GetInstance()->SetEnable(true);
  
  Action::GetInstance()->Start(INIT_POS);
  while(Action::GetInstance()->IsRunning()) usleep(8*1000);

  /////////////////// Dancing Server Script //////////////////////////

  //Initialize variables    
  JSONSequenceAnalyzer * sa;
  string filename;
  int current;

  if(argc > 1){
    filename = argv[1];
  }
  else {
    cout<<"Please enter the filename you would like to use for sequences:"<<endl;
    cin>>filename;
  }

  //Open the sequences file and fill the generator table
  sa = new JSONSequenceAnalyzer(filename);
  DanceGenerator dg(sa->getSequenceTable());

  /*
  //Commented out temporarily.  Maybe later.
  printf("Please choose the mode:\n");
  printf("a - use entire library, no base transitions. (default)\n");
  printf("b - use random positions, return to base position between moves.\n");
  printf("c - use dance sequence generator.\n");
  char mode = getchar();
  */

  
  
  /////////////////// Spawn a BeatTracker Process   //////////////////////////
  setpgid(0,0); //Give us our own process group
  pid_t pid = fork(); //Fork a process so we can run the Beat Tracker
  if (pid == 0){
    //This is the child process, spawn the BeatTracker
    printf("BeatTracker process spanwed, PID = %d\n",getpid());
    execve("BeatTrackerApp",argv,environ);
  }
  else {
    //This process should continue running the Dance Synth
    BeatTrackerPID = pid;
    printf("DanceSynth continuing, PID = %d\n",getpid());
  }
  



  //Connect to the server
  if ((serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    printf("Unable to connect to client.  Exiting...\n");
    exit(0);
  }


  //Initialize the socket information and bind it
  memset((char*) &sad, 0, sizeof(sad));
  sad.sin_family = AF_INET;
  sad.sin_port = htons(PORT);
  sad.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(serverSocket,(struct sockaddr*)&sad,sizeof(sad))==-1) {
    printf("Unable to bind socket.  Exiting...\n");
    close(serverSocket);
    exit(0);
  }
  else {
    printf("Waiting for packets from BeatTracker...\n\n"); 
    //We're ready! Start recieving UDP packets
    while(1) {
      if( recvfrom(serverSocket, buf, BUFLEN, 0, (struct sockaddr *)&cad, (socklen_t*)&slen) == -1 ) {
        printf("Unable to recieve packet from client.  Exiting...\n");
        close(serverSocket);
        exit(0);
      }
      else {
        //Do all activities when a beat is detected
        printf("Recieved packet from BeatTracker.\n");
        current = dg.currentPos();
        printf("Playing action %d...\n",current);
        Action::GetInstance()->Start( current );    // Call pose
        //while(Action::GetInstance()->IsRunning()) usleep(8*1000);
        //Change to base position between poses
        dg.next(); //Advance the dance generator
      }
    }
  }


  //Run an actionscript -- not needed for beattracking, just a reference
  /*
     LinuxActionScript::ScriptStart("script.asc");
     while(LinuxActionScript::m_is_running == 1) sleep(10);
     */

  return 0;
}

