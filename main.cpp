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

#ifdef MX28_1024
#define MOTION_FILE_PATH    "../../../Data/motion_1024.bin"
#else
#define MOTION_FILE_PATH    "../../../Data/motion_4096.bin"
#endif

#define PORT 9930
#define BUFLEN 70
#define SAMPLE_RATE (44100)


void change_current_dir()
{
    char exepath[1024] = {0};
    if(readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
        chdir(dirname(exepath));
}

void sighandler(int sig)
{
    struct termios term;
        Action::GetInstance()->Start(1);    /* Init(stand up) pose */
    tcgetattr( STDIN_FILENO, &term );
    term.c_lflag |= ICANON | ECHO;
    tcsetattr( STDIN_FILENO, TCSANOW, &term );

    exit(0);
}


int main(void)
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
    LinuxMotionTimer *motion_timer = new LinuxMotionTimer(MotionManager::GetInstance());
    motion_timer->Start();
    /////////////////////////////////////////////////////////////////////

      
    /////////////////// Dancing Server Script //////////////////////////
    
    //Initialize variables
    int numPos = 18;
    int numBases = 4;
    int firstPos = 111;
    int firstBase = 100;

    int dancePoses[numPos];
    int basePoses[numBases];

    int danceSeq1[11] = {100,111,113,114,115,116,117,123,125,124,125};
    
    int current = 0;
    int eyeValue;

    //int base = 0; //Start from base
    int base = 1; //Start from pose

    //Fill dance and base position arrays
    for (int i=0; i<numPos; i++)
      dancePoses[i] = firstPos+i;
    for (int i=0; i<numBases; i++)
      basePoses[i] = firstBase+i;

    srand (time(NULL));

    MotionManager::GetInstance()->SetEnable(true);

    Action::GetInstance()->Start(1);    /* Init(stand up) pose */
    while(Action::GetInstance()->IsRunning()) usleep(8*1000);

    //printf("Press the ENTER key to begin!\n");
    printf("Please choose the mode:\n");
    printf("a - use entire library, no base transitions. (default)\n");
    printf("b - use random positions, return to base position between moves.\n");
    printf("c - use dance sequence, no base transitions.\n");
    char mode = getchar();
    /* 
    //Randomly choose dance position whenever the enter key is hit. No BeatTracker Needed
    //this is mainly for previewing dance moves
    while (1) {
      getchar();
      
      Action::GetInstance()->Start( firstpose+current );    // Call pose
      current = (current+1)%numPos;
    }
    */

    
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
      if ( mode != 'b' && mode != 'c') {
        //Default mode: Use all moves in library  
        while(1) {
          if( recvfrom(serverSocket, buf, BUFLEN, 0, (struct sockaddr *)&cad, (socklen_t*)&slen) == -1 ) {
            printf("Unable to recieve packet from client.  Exiting...\n");
            close(serverSocket);
            exit(0);
          }
          else {
            //Do all activities when a beat is detected
            printf("Recieved packet from BeatTracker.\n");
            //**Use all dance poses in library**
            current = (current+1)%numPos;
            printf("Playing action %d...\n",dancePoses[current]);
            Action::GetInstance()->Start( dancePoses[current] );    // Call pose
          }
        }
      }
      else if ( mode == 'b') {
        while(1) {
            if( recvfrom(serverSocket, buf, BUFLEN, 0, (struct sockaddr *)&cad, (socklen_t*)&slen) == -1 ) {
            printf("Unable to recieve packet from client.  Exiting...\n");
            close(serverSocket);
            exit(0);
          }
          else {
            //Do all activities when a beat is detected
            printf("Recieved packet from BeatTracker.\n");
            if (base == 0) {
              current = rand()%numBases;
              printf("Playing action %d, ...\n",basePoses[current]);
              Action::GetInstance()->Start( basePoses[current] );    // Call pose 
              //while(Action::GetInstance()->IsRunning()) usleep(8*1000);
              base = 1;
            }
            else if (base == 1) {
              //**Use random dance poses in library**
              current = rand()%numPos;
              printf("Playing action %d...\n",dancePoses[current]);
              Action::GetInstance()->Start( dancePoses[current] );    // Call pose
              //while(Action::GetInstance()->IsRunning()) usleep(8*1000);
              //Change to base position between poses
              base = 0;
            }
          }
        }
      }
      if ( mode == 'c') {      
        while(1) {
            if( recvfrom(serverSocket, buf, BUFLEN, 0, (struct sockaddr *)&cad, (socklen_t*)&slen) == -1 ) {
            printf("Unable to recieve packet from client.  Exiting...\n");
            close(serverSocket);
            exit(0);
          }
          else {
            //Do all activities when a beat is detected
            printf("Recieved packet from BeatTracker.\n");
            //**Use the set dance sequence**
            current = (current+1)%11;
            printf("Playing action %d...\n",danceSeq1[current]);
            Action::GetInstance()->Start( danceSeq1[current] );    // Call pose 
            
          }
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

