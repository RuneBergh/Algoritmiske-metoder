//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_11.CPP

//  Eksemplet omhandler et brikkespill med f›lgende forhold:
//    1) Brettet har st›rrelse N x N.
//    2) Det st†r brikker eller er ledige hull i posisjonene 1 til N-2.
//    3) En brikke kan hoppe over "naboen" dersom det finnes et ledig
//       hull p† bortsiden av denne. Den "overhoppede" brikke blir
//       da fjernet.
//    4) Gjenta steg 3) til kun EN brikke st†r igjen.
//
//
//  N†r nytt brett fors›kes l›st, s† m† det endres tre steder i koden:
//     1) "Tegne" det nye brettet vha.arrayen 'utseende'  (linje 38 og f›lg.)..
//         NB: Husk † ha en blank (' ') kant rundt brettet
//     2)  Sette opp starttrekket ('X' og 'Y')  (linje 35).
//     3)  Endre extension for filnavnet  (linje 128).



#include <fstream>           //  ofstream
#include <iostream>          //  cout

using namespace std;


const int N = 7;             //  Max. st›rrelse p† spillebrettet (Indeks 0-6).
const int MIN = 1;           //  Bruker indeksene f.o.m. MIN t.o.m. MAX.
const int MAX = 5;

const int X = 1;
const int Y = 3;

char utseende[N][N+1]  =  { "       ",
			  "  oxo  ",
			  " oxxxo ",
			  " xxoxx ",
			  " oxxxo ",
			  "  oxo  ",
			  "       " };
/*char utseende[N][N+1]  =  { "       ",
			  "  xxx  ",
			  " xxxxx ",
			  " xxoxx ",
			  " xxxxx ",
			  "  xxx  ",
			  "       " };  */

int brett[N][N];             //  Spillebrettet. Blir automatisk satt til '0'.
bool ferdig = false;         //  Om funnet EN l›sning eller ei.
int antall;                  //  Antall trekk totalt.

ofstream utfil;              //  Filobjekt for utskrift.


void initierBrett()  {
  int i, j;
  antall = 0;

  for (i = MIN;  i <= MAX ;  i++)
      for (j = MIN;  j <= MAX;  j++)
	  if (utseende[i][j] == 'x')  {
	     ++antall;
	     brett[i][j] = 1;
	  } else if (utseende[i][j] == 'o')
	     brett[i][j] = 2;
}


void display(int n)  {            //  Skriver ut brettets innhold til fil.
  int i, j;
  utfil << "\n\nTrekk nr." << n << "\n\t";
  for (i = MIN;  i <= MAX;  i++)  {
      for (j = MIN;  j <= MAX;  j++)
	  if (brett[i][j] == 0)
	     utfil << "  ";
	  else if (brett[i][j] == 1)
	     utfil << "X ";
	  else
	     utfil << "o ";
      utfil << "\n\t";
  }
}


void flyttBrikke(int x, int y, int dx, int dy, int nr)  {
  int i, j;

  if (nr == antall-1)  {
     cout << "\nLSNING FUNNET !\n\n";
     ferdig = true;
     display(nr);
  } else
    if (brett[x+dx][y+dy] == 1  &&  brett[x+dx+dx][y+dy+dy] == 2)  {
	brett[x+dx+dx][y+dy+dy]  = 1;
	brett[x+dx][y+dy]        = 2;
	brett[x][y]              = 2;
	
	for (i = MIN;  i <= MAX;  i++)
	    for (j = MIN;  j <= MAX;  j++)
		if (brett[i][j] == 1)  {
		     flyttBrikke(i, j,  1,  0, nr+1); if (ferdig) goto slutt;
		     flyttBrikke(i, j, -1,  0, nr+1); if (ferdig) goto slutt;
		     flyttBrikke(i, j,  0,  1, nr+1); if (ferdig) goto slutt;
		     flyttBrikke(i, j,  0, -1, nr+1); if (ferdig) goto slutt;
		}
	slutt:
	    brett[x+dx+dx][y+dy+dy]  = 2;
	    brett[x+dx][y+dy]        = 1;
	    brett[x][y]              = 1;
	    if (ferdig) display(nr);
    }
}



// ************************   HOVEDPROGRAM:   *****************************

int main()  {

  initierBrett();

  utfil.open("EKS_11.DIA");

  flyttBrikke(X, Y, 1, 0, 0);

  utfil.close();

  if (!ferdig)
     cout << "\n\nINGEN LSNING !\n\n";

  return 0;
}
