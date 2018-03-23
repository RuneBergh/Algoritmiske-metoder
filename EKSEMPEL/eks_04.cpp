//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_04.CPP

//  Eksemplet viser bruk av rekursjon for tegning av
//  kryss i stadig mindre og mindre vinduer.


//   **********************************************************
//   **                                                      **
//   **    EKSEMPLET KJÿùRER 'KUN' UNNDER BORLAND 4.5.        **
//   **    HENT OG KJùÿR ISTEDET FILEN "EKS_04.EXE"           **
//   **    SAMMEN MED FILEN "MSVCR70.DLL".                   **
//   **                                                      **
//   **********************************************************


#include <graphics.h>
#include <dos.h>

const int MAXDEPTH = 5;                //  Max. dybde pÂ rekursjon

				       //  Skal tegne et kryss i "vinduet"
				       //  med nedre venstre hj¯rne i (x1,y1),
				       //  og ¯vre h¯yre hj¯rne i (x2,y2).
				       //  'n' angir rekursjonsnivÂet.
void kryss(int x1, int y1, int x2, int y2, int n)  {
   int dx = (x2-x1)/2;                 //  Beregner midtpunktet i "vinduet".
   int dy = (y2-y1)/2;
   setcolor(n);                        //  Setter aktuell tegnefarge.
   line(x1+dx, y1, x1+dx, y2);         //  Tegner kryss MIDT i "vinduet".
   line(x1, y1+dy, x2, y1+dy);

   if (n < MAXDEPTH)  {                //  Tegne i de fire nye "vinduene"
      kryss(x1, y1, x1+dx, y1+dy, n+1);  //   som nÂ har oppstÂtt:
      kryss(x1+dx, y1, x2, y1+dy, n+1);
      kryss(x1, y1+dy, x1+dx, y2, n+1);
      kryss(x1+dx, y1+dy, x2, y2, n+1);
   }
}


int main()  {
 int driver = DETECT;
 int mode;
 char path[] = "\\borlandc\\bgi";

 initgraph(&driver, &mode, path);
 setcolor(WHITE);
 setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
 rectangle(0, 0, 639, 479);
 kryss(0, 0, 639, 479, 1);
 closegraph();
 return 0;
}
