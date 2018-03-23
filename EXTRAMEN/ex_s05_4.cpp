//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S05_4.CPP

//     L›sningsforslag til kontinuasjonseksamen i 
//     "Algoritmiske metoder", oppgave nr.4, 9.august 2005.

//     Laget av Frode Haug, HiG, juni 2005.



#include <fstream>
#include <iostream>
using namespace std;

const int ANTX = 9, ANTY = 9, STRLEN = 80, TOTSUM = 45;
int ant;
int s[ANTX][ANTY];


void les_fra_fil()  {
  ifstream innfil("sudoku.dta");
  int i, j;
  char dummy;
  char buffer[STRLEN];
  if (innfil)  {
   cout << "\n\n\tLeser fra filen 'SUDOKU.DTA' .....\n";
   for (i = 0;  i < ANTX;  i++)  {
      for (j = 0;  j < ANTY;  j+=3) {
        innfil >> s[i][j] >> s[i][j+1] >> s[i][j+2];
        if (s[i][j])  ant++;  if (s[i][j+1])  ant++;  if (s[i][j+2])  ant++;
        if (j+2 < ANTY-1) innfil >> dummy;    //  Hopper over '|'.
      }
      innfil.ignore();                        //  Hopper over prikket linje:
      if ((i==2  ||  i==5)) innfil.getline(buffer, STRLEN); 
   }
   cout << "\n\tAntall tall bestemt hittil: " << ant << "\n\n";
  } else
    cout << "\n\n\tFant ikke filen 'SUDOKU.DTA'!\n\n";
}


void skriv_losning()  {
   int i, j;
   for (i = 0;  i < ANTX;  i++)  {
      cout << "\n\t";
      for (j = 0;  j < ANTY;  j++)
         cout << s[i][j] << ' ';
   }
   cout << "\n\n";
}


bool finn_losning()  {
  int tot = ANTX*ANTY;
  int i, j, k, ii, jj, sum, n, tall, dx1, dx2, dy1, dy2;
  bool funn;

// char bingo;

  while (ant < tot)  {                          //  L›sning enn† ikke funnet:
    funn = false;                               //  Nytt tall IKKE funnet enn†.

    for (i = 0;  i < ANTX;  i++)                //  G†r gjennom ALLE rutene:
        for (j = 0;  j < ANTY;  j++) {
            if (s[i][j] == 0)  {                //  Tom/ledig rute:
               int brukt[ANTX+1] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
               sum = n = 0;
               for (jj = 0;  jj < ANTY;  jj++)  {  //  Tallene brukt på EN rad:
                   tall = s[i][jj];
                   if (tall  &&  !brukt[tall])  {
                      n++;   sum += tall;   brukt[tall] = 1;
                   }
               }

               for (ii = 0;  ii < ANTX;  ii++) {   //  Tallene brukt på EN kolonne:
                   tall = s[ii][j]; 
                   if (tall  &&  !brukt[tall])  {
                      n++;   sum += tall;   brukt[tall] = 1;
                   }
               }
                                                   //  De brukt i AKTUELL 3x3 rute:
               ii = i % 3;  jj = j % 3;            //  Hvor 'i' og 'j' er i ruten.
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
//cout << '[' << i << ',' << j << "]\tdx1: " << dx1 << "\tdx2: " << dx2 << "\tdy1: " << dy1 << "\tdy2: " << dy2;
//char bingo2;  cin >> bingo2;
               for (k = 1;  k <= ANTX;  k++)  {    //  G†r gjennom 3x3 ruten:
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
                   if (tall  &&  !brukt[tall])  { n++;   sum += tall;   brukt[tall] = 1;  }
               }

               if (n == ANTX-1)  {           //  Eksakt 8 tall er brukt:
                  ant++;  funn = true;       //  Kan da sette inn det
                  s[i][j] = TOTSUM - sum;    //     nye og kjente tallet.
cout << '[' << i << ',' << j << "]: " << s[i][j]
     << "\tN: " << n << "\tSum: " << sum << "\t\tAnt: " << ant << '\n';  
// skriv_losning();
// cin >> bingo;
                }
            }  //  end if
     }  // end for  i og j         //  Ingen nye tall funnet ved 
     if (!funn)  return false;     //    gjennomgang av HELE brettet:
  }
  return true;
}


int main()  {
  les_fra_fil();
  if (finn_losning())
     skriv_losning();
  else
     cout << "\n\n\tUmulig å finne en løsning!!!\n\n\n";
 return 0;
}
