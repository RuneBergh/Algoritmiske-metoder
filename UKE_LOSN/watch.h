//  ***************************************************************
//  ***************************************************************
//  ***                                                         ***
//  ***  NB:  Deler av koden virker KUN under/p† BORLAND 4.5 !  ***
//  ***                                                         ***
//  ***************************************************************
//  ***************************************************************


#if !defined(__WATCH_H)
#define  __WATCH_H

#include <iostream>          //  cout
#include <dos.h>             //  struct time, gettime
using namespace std;


class Watch  {
  private:
    time* startTime;
    time* stopTime;
    int   timeTaken;

  public:
    Watch()  {  timeTaken = 0;  }
    void start();
    void stop();
    void usedTime();
};


void Watch::start()  {
  timeTaken = 0;
  gettime(startTime);
}


void Watch::stop()  {
  timeTaken = 1;
  gettime(stopTime);
}


void Watch::usedTime()  {
  if (timeTaken)  {
     long startTi, stopTi;
     long diff;
     startTi = (int(startTime->ti_hour)*360000)
	     + (int(startTime->ti_min)*6000)
	     + (int(startTime->ti_sec)*100)
	     +  int(startTime->ti_hund);
     stopTi  = (int(stopTime->ti_hour)*360000)
	     + (int(stopTime->ti_min)*6000)
	     + (int(stopTime->ti_sec)*100)
	     +  int(stopTime->ti_hund);
     diff = stopTi - startTi;
     cout << diff/100 << ':';
     if (diff % 100  < 10)  cout << '0';
     cout << diff % 100;
  } else
    cout << "\nNo time-difference available.\n";
}

#endif
