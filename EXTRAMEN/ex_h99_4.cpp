//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H99_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     13.desember 1999, oppgave 4.

//     Laget av Frode Haug, HIG,  desember 1999.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>          //  cout 

using namespace std;

const int N    = 10;         //  Brettets st›rrelse.
const int SEEN =  2;         //  Verdien for n†r en rute er ferdig bes›kt.

int brett[N+2][N+2];         //  Matrise som representerer brettet. Alle rutene
                             //    er initielt '0'. Bruker indeks 1-N. 
                             //    Har derfor en ekstra randkant rundt det hele
                             //    for † slippe † sjekke om n†r utenfor brettet.

void initier_brett()  {               //  Setter opp brikker likt med
 brett[1][10] = brett[2][10] = 1;     //    det i oppgaveteksen:
 brett[2][4]  = brett[2][5]  = 1;
 brett[4][5]  = 1;
 brett[5][4]  = 1;
 brett[4][8]  = brett[5][8]  = brett[6][8]  = brett[6][9] = 1;
 brett[7][5]  = brett[7][6]  = 1;
 brett[8][2]  = brett[8][3]  = brett[9][2]  = brett[9][3] = 1;
 brett[9][9]  = brett[10][8] = brett[10][9] = 1;
}


void besok_en_gruppe(int x, int y, int & ant)  {
  if (brett[x][y] == 1)  {             //  Aktuell rute er en del av en gruppe.
     ant++;                            //  Teller opp antall brikker i gruppen.
     brett[x][y] = SEEN;               //  Setter FOR GODT at er ferdig bes›kt.
     cout << " (" << x << ',' << y << ')';    //  Skriver rutens indekser.
     besok_en_gruppe(x+1,y,ant);  // under    Bes›ker naborutene for † finne ut
     besok_en_gruppe(x,y+1,ant);  // h›yre    om de er med i gruppen. 
     besok_en_gruppe(x,y-1,ant);  // venstre
//   besok_en_gruppe(x-1,y,ant);  // over     NB: Bes›ker IKKE denne, da
  }                               //              den allerede er bes›kt!
}                                 //     (For-l›kka i 'main' s›rger for dette.)

int main()   {
  int ant_grupper = 0, ant_i_en_gruppe;   //  Variable for de to opptellingene.
  int i, j;                               //  L›kkevariable

  initier_brett();                        //  Setter opp/initierer brettet.
  for (i = 1;  i <= N;  i++)              //  Traverserer hele brette, ALT p†
      for (j = 1;  j <= N;  j++)          //    en og en linje nedover:
        if (brett[i][j] == 1)  {          //  Har funnet "starten" p† en gruppe:
           ant_grupper++;                 //  Teller opp at funnet en ny gruppe.
           cout << "\nGruppe nr. " << ant_grupper << " best†r av ruten(e):\n\t";
           ant_i_en_gruppe = 0;           //  Nullstiller antallet i gruppen.
           besok_en_gruppe(i, j, ant_i_en_gruppe); // Bes›ker RESTEN av gruppen.
           cout << "\n\tAntall i gruppen: " << ant_i_en_gruppe;
        }
  cout << "\n\n";
  return 0;
}
