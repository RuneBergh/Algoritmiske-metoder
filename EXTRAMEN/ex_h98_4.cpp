//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H98_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     15.desember 1998, oppgave 4.

//     Laget av Frode Haug, HIG,  desember 1998.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



//  OPPGAVE 4A:

#include <iostream>       //  cin, cout

using namespace std;


const int N = 5;

int jente[N+1][N+1] = { { 0, 0, 0, 0, 0, 0 },  //  Matrise for hvor mye
                         { 0, 5, 4, 3, 2, 1 },  //    jente 'i' liker gutt 'j':
                         { 0, 1, 5, 4, 3, 2 }, 
                         { 0, 2, 1, 5, 4, 3 }, 
                         { 0, 3, 2, 1, 5, 4 }, 
                         { 0, 4, 3, 2, 1, 5 } };

int gutt[N+1][N+1]   = { { 0, 0, 0, 0, 0, 0 },  //  Matrise for hvor mye
                         { 0, 5, 4, 3, 2, 1 },  //    gutt 'i' liker jente 'j':
                         { 0, 1, 5, 4, 3, 2 }, 
                         { 0, 2, 1, 5, 4, 3 }, 
                         { 0, 3, 2, 1, 5, 4 }, 
                         { 0, 4, 3, 2, 1, 5 } };
/*
                         { 0, 5, 5, 5, 5, 5 },   // Om begge matrisene er dette
                         { 0, 5, 5, 5, 5, 5 },   //   vil vi f† det samme som
                         { 0, 5, 5, 5, 5, 5 },   //   ovenfor. Men hvis vi tar
                         { 0, 5, 5, 5, 5, 5 },   //   vekk "opptatt"-testen inni 
                         { 0, 5, 5, 5, 5, 5 } }; //   "finn_par", s† vil ALLE
                                                 //   jentene bli koplet med
                                                 //   gutt nr.1. 
*/

int  naavaerende[N+1];           //  N†v‘rende aktuelle kombinasjon.
int  beste[N+1];                 //  Den beste kombinasjonen hittil. 
int  opptatt[N+1];               //  Hvilke menn som er "okkupert"/opptatt.
int  abs_max = 0, naa_max = 0;   //  Beste  og n†v‘rende notering.


void finn_par(int n)  {    //  Pr›ver alle kombinasjoner av jente "n" med 
                           //    alle mulige menn.
  int j;                   //  L›kkevariabel.
  if (n == N+1)  {         //  Ferdig med † kombinere alle parene:
     if (naa_max  >  abs_max)  {     //  Ny bestekombinasjon ?
        abs_max = naa_max;           //  Oppdaterer variable:
        for (j = 1;  j <= N;  j++)  beste[j] = naavaerende[j];
     }
  } else  {                          //  Finne nye kombinasjoner:
     for (j = 1;  j <= N;  j++)  {   //  For alle mennene:
       if (!opptatt[j])  {
         opptatt[j] = 1;             //  Gutt 'j' er opptatt.
         naavaerende[n] = j;         //  Kobling mellom jente 'n' og gutt 'j'.
         naa_max += (jente[n][j] + gutt[j][n]);  //  Total forn›ydhet.
         finn_par(n+1);              //
         naa_max -= (jente[n][j] + gutt[j][n]);  //  Trekker fra igjen.
         naavaerende[n] = 0;         //  (Un›dvendig, overskrives senere igjen.)
         opptatt[j] = 0;             //  Gutt 'j' er ledig igjen.
       }
     }
  }
}


int main()  {
  finn_par(1);
  cout << "Beste kombinasjon av par har en totalsum p†  " 
       << abs_max << "  og er:";
  for (int i = 1;  i <= N;  i++)  {
     cout << "\n\tJente nr." << i << "  med gutt nr." << beste[i];
  }
  cout << "\n\n";
  return 0;
}



//  OPPGAVE 4B:
//      Algoritmen blir som f›lger:
//         - La den st›rste familien f† det st›rste rommet.
//         - La den NEST st›rste familien f† det NEST st›rste rommet.
//         - og s† videre .......
