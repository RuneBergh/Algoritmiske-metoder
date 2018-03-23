//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_03.CPP

//  Eksemplet viser bruk av rekursjon for tegning av
//  fraktal stjerne (jfr. lÊreboka s.59).


//   **********************************************************
//   **                                                      **
//   **    EKSEMPLET KJùÿRER 'KUN' UNNDER BORLAND 4.5.        **
//   **    HENT OG KJùÿR ISTEDET FILEN "EKS_03.EXE"           **
//   **    SAMMEN MED FILEN "MSVCR70.DLL".                   **
//   **                                                      **
//   **********************************************************


#include <graphics.h>
#include <dos.h>


void star(int x, int y, int r)  {
  if (r > 0)  {
     star(x-r, y+r, r/2);
     star(x+r, y+r, r/2);
     star(x-r, y-r, r/2);
     star(x+r, y-r, r/2);
     rectangle(x-r, y-r, x+r, y+r);
  }
}


int main()  {
 int driver = DETECT;
 int mode;
 char path[] = "\\borlandc\\bgi";

 initgraph(&driver, &mode, path);
 setcolor(YELLOW);
 star(320, 240, 120);
 closegraph();
 return 0;
}

