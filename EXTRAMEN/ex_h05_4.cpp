//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H05_4.CPP

//     Løsningsforslag til eksamen i "Algoritmiske metoder",
//     8.desember 2005, oppgave nr.4.

//     Laget av Frode Haug, HiG, november 2005.

#include <fstream>
#include <iostream>
using namespace std;

const int ANTX = 9, ANTY = 9, N = ANTX*ANTY, STRLEN = 80;    // ~ linje nr.2
int s[ANTX][ANTY];                                           // = linje nr.4


void les_fra_fil()  {                                        // = linje nr.5
  ifstream innfil("sudoku.dta");
  int i, j;
  char dummy;
  char buffer[STRLEN];
  if (innfil)  {
   cout << "\n\n\tLeser fra filen 'SUDOKU.DTA' .....\n";
   for (i = 0;  i < ANTX;  i++)  {
      for (j = 0;  j < ANTY;  j+=3) {
        innfil >> s[i][j] >> s[i][j+1] >> s[i][j+2];
        if (j+2 < ANTY-1) innfil >> dummy;    //  Hopper over '|'.
      }
      innfil.ignore();                        //  Hopper over prikket linje:
      if ((i==2  ||  i==5)) innfil.getline(buffer, STRLEN); 
   }
  } else
    cout << "\n\n\tFant ikke filen 'SUDOKU.DTA'!\n\n";
}


void skriv_losning()  {                                      // = linje nr.6
   int i, j;
   for (i = 0;  i < ANTX;  i++)  {
      cout << "\n\t";
      for (j = 0;  j < ANTY;  j++)
         cout << s[i][j] << ' ';
   }
   cout << "\n\n";
}


void finn_losning(int n)  {           //  'n' = 0 ... ANTX*ANTY (=81)
  int brukt[ANTX+1] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };  // Brukt allerede.
                                                         //   = linje nr.16
  int i = n/ANTX, j = n%ANTY;         //  Konverterer 'n' til i=[0-8] j=[0-8]
  int ii, jj, tall, k, dx1, dx2, dy1, dy2; //  Div. hjelpevariable.  = lin.nr.9

  if (n == N)                         //  Brettet er fylt ut ferdig:
      skriv_losning();                //  Skriver EN løsning.
  else if (s[i][j] == 0)  {           //  Aktuell rute er tom/ufylt: = l.nr.15
      for (jj = 0;  jj < ANTY;  jj++)  { //  Tallene brukt på EN rad:
                                         //          = linje nr.18-21
          tall = s[i][jj];
          if (tall  &&  !brukt[tall]) brukt[tall] = 1;
      }
      for (ii = 0;  ii < ANTX;  ii++) {  // Tallene brukt på EN kolonne:
                                         //          = linje nr.22-25
          tall = s[ii][j]; 
          if (tall  &&  !brukt[tall]) brukt[tall] = 1;
      }
                                          //  De brukt i AKTUELL 3x3 rute:
      ii = i % 3;  jj = j % 3;            //  Hvor 'i' og 'j' er i ruten.
                                          //          = linje nr.27-51
      switch (ii)  {                      //  Naborutenes relative
        case 0:  dx1 = 1;   dx2 = 2;  break;
        case 1:  dx1 = -1;  dx2 = 1;  break;
        case 2:  dx1 = -2;  dx2 = -1; break;
      }
      switch (jj)  {                      //     posisjon ift.dette:
        case 0:  dy1 = 1;   dy2 = 2;  break;
        case 1:  dy1 = -1;  dy2 = 1;  break;
        case 2:  dy1 = -2;  dy2 = -1; break;
      }

      for (k = 1;  k <= ANTX;  k++)  {    //  Går gjennom 3x3 ruten:
          switch(k)  {                    //  Beregner absolutt ruteindeks:
            case 1: ii = i;      jj = j;      break;
            case 2: ii = i+dx1;  jj = j;      break;
            case 3: ii = i+dx2;  jj = j;      break;
            case 4: ii = i;      jj = j+dy1;  break;
            case 5: ii = i+dx1;  jj = j+dy1;  break;
            case 6: ii = i+dx2;  jj = j+dy1;  break;
            case 7: ii = i;      jj = j+dy2;  break;
            case 8: ii = i+dx1;  jj = j+dy2;  break;
            case 9: ii = i+dx2;  jj = j+dy2;  break;
          }
          tall = s[ii][jj];               //  Er tallet brukt:
          if (tall  &&  !brukt[tall]) brukt[tall] = 1;
      }

      for (k = 1;  k <= ANTX;  k++)       //  Går gjennom ALLE tallene:
          if (!brukt[k]) {                //  Ikke brukt/prøvd:
              s[i][j] = k;                //  Prøver med dette tallet.
              finn_losning(n+1);          //  Neste rute fylles (om mulig).
              s[i][j] = 0;                //  Tar vekk igjen prøvet tall.
         }
  } else                    //  Ruten er fylt allerede, går rett til neste:
    finn_losning(n+1);
}
	
	
int main()  {
  les_fra_fil();
  finn_losning(0);
 return 0;
}
