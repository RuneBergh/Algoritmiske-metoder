//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_18.CPP


//  Eksemplet viser rekursiv tegning av kvadrater rotert inni hverandre.


//   **********************************************************
//   **                                                      **
//   **    EKSEMPLET KJùRER 'KUN' UNNDER BORLAND 4.5.        **
//   **    HENT OG KJùR ISTEDET FILEN "EKS_18.EXE"           **
//   **    SAMMEN MED FILEN "MSVCR70.DLL".                   **
//   **                                                      **
//   **********************************************************


#include <graphics.h>
#include <dos.h>


void figur(int x, int y, int L, int n)  {
  if (n > 0)  {
     int d2 = L/2,  d4 = L/4;
     lineto(x+d2, y);
     lineto(x+d4, y-d4);

     figur(x+d4, y-d4, d2, n-1);

     lineto(x, y-d2);
     lineto(x+d2, y-L);    lineto(x+L, y-d2);    lineto(x+d2, y);

     lineto(x+L, y);
     lineto(x+L, y-L);     lineto(x, y-L);       lineto(x,y);
  }
}



int main()  {
 int driver = DETECT;
 int mode;
 char path[] = "\\borlandc\\bgi";

 initgraph(&driver, &mode, path);
 setcolor(WHITE);
 setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
 moveto(0, getmaxy());

 figur(getx(), gety(), getmaxy(), 5);

 closegraph();
 return 0;
}
