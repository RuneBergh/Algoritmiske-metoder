//  Fil:  FRODEH \ ALG_MET1 \ EXTRAMEN \EX_S98_4.CPP

//     L›sningsforslag til kontinuasjonseksamen i
//     "Algoritmiske metoder I", oppgave nr.4,  17.august 1998.

//     Laget av Frode Haug,  HIG,  august 1998.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



#include <iostream>          //  cout
using namespace std;


const int N = 8;             //  8 personer og 8 jobber tilgjengelig.

                             //   Fire ulike kostnads-matriser:
/*
int  kostnad[N+1][N+1]  =   { { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 10, 2, 3, 4, 5, 6, 7, 8 },
                              { 0, 8, 10, 2, 3, 4, 5, 6, 7 },
                              { 0, 7, 8, 10, 2, 3, 4, 5, 6 },
                              { 0, 6, 7, 8, 10, 2, 3, 4, 5 },
                              { 0, 5, 6, 7, 8, 10, 2, 3, 4 },
                              { 0, 4, 5, 6, 7, 8, 10, 2, 3 },
                              { 0, 3, 4, 5, 6, 7, 8, 10, 2 },
                              { 0, 2, 3, 4, 5, 6, 7, 8, 10 } };

int  kostnad[N+1][N+1]  =   { { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 1, 2, 3, 4, 5, 6, 7, 0 },
                              { 0, 0, 1, 2, 3, 4, 5, 6, 7 },
                              { 0, 7, 0, 1, 2, 3, 4, 5, 6 },
                              { 0, 6, 7, 0, 1, 2, 3, 4, 5 },
                              { 0, 5, 6, 7, 0, 1, 2, 3, 4 },
                              { 0, 4, 5, 6, 7, 0, 1, 2, 3 },
                              { 0, 3, 4, 5, 6, 7, 0, 1, 2 },
                              { 0, 2, 3, 4, 5, 6, 7, 0, 1 } };
*/
int  kostnad[N+1][N+1]  =   { { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 4, 2, 3, 1, 5, 6, 7, 8 },
                              { 0, 8, 5, 2, 3, 4, 1, 6, 7 },
                              { 0, 1, 8, 7, 2, 3, 4, 5, 6 },
                              { 0, 6, 7, 1, 8, 2, 3, 4, 5 },
                              { 0, 5, 6, 7, 8, 3, 2, 1, 4 },
                              { 0, 4, 5, 6, 7, 1, 8, 2, 3 },
                              { 0, 3, 4, 5, 6, 7, 8, 2, 1 },
                              { 0, 2, 1, 4, 5, 6, 7, 8, 3 } };

                        //  I "skuff" nr.i ligger personnummeret som for
int besatt[N+1];        //    ›yeblikket har blitt tildelt jobb nr.i.
int losning[N+1];       //  Den mest optimale fordelingen hittil.
int aktuell_min = 0,    //  N†v‘rende totale kostnad.
    best_min = 9999;    //  N†v‘rende totale MINIMUMSkostnad.
//  int ant = 0;        //  Hjelpevariabel for † telle opp ganger i for-l›kke.


void kopier(int a[], int b[])  {          //  Kopierer alt i "b" til "a":
  for (int i = 1;  i <= N;  i++)   a[i] = b[i];
}


void skriv(int a[])  {                    //  Skriver array's innhold:
  cout << "\n<Jobbnr>: <Personnr>\n\t";
  for (int i = 1;  i <= N;  i++)
      cout << i << ": " << a[i] << "    ";
}

                              // Rekursiv funksjon som fordeler jobber og
                              //   finner den absolutte minimumskostnad.
void finn_min(int i)  {       //   Pr›ver med alle jobber for person nr."i".
  if (i == N+1  &&  aktuell_min < best_min)  {   //  Ny minimumsrekord:
     best_min = aktuell_min;                     //  Oppdaterer aktuelle 
     kopier(losning, besatt);                    //    variable.
  } else {                                       //  M† pr›ve videre: 
     for (int j = 1;  j <= N;  j++)  {           //  Lar "i" f† alle jobber:
//      cout << '.';  ant++;  // Skriver at "innom" og teller opp antall ganger.
                                                 //  Dersom jobb nr.j ikke
                                                 //    er besatt/opptatt og
                                                 //   muligheter for ny minimum:
         if (besatt[j] == 0  &&  (aktuell_min+kostnad[i][j]) < best_min)  {
//            cout << i << ' ';    //  Skriver personnr. n†r KAN sette rekord.
            besatt[j] = i;                       //  Setter at opptatt.
            aktuell_min += kostnad[i][j];        //  Oppdaterer totalkostnad.
            finn_min(i+1);                       //  Gir neste person jobb.
            aktuell_min -= kostnad[i][j];        //  Tilbakestiller det
            besatt[j] = 0;                       //    oppdaterte variable.
         }
     }
  }
}


int main()   {

  finn_min(1);              //  Finner l›sning p† oppgaven.
  skriv(losning);           //  Skriver l›sningen.
  cout << "\n\nTotal minimumskostnad:  "  << best_min << "\n\n";;

//  cout << "\n\nAntall: " << ant;   //  Skriver antall ganger i for-l›kke.
  return 0;
}
