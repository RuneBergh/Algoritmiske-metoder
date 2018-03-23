//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S99_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     19.august 1999, oppgave 4.

//     Laget av Frode Haug, HiG,  august 1999.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


/*
OPPGAVE A:
   N gjenstander skal fordeles vha. et fordelingstre. Dette medf›rer:
     - N niv†er med noder, der 1.niv† inneholder en gjenstand nr.1 node.
                           der 2.niv† inneholder to gjenstander nr.2 node.
                           der 3.niv† inneholder fire gjenstander nr.3 node.
                           ........
                           der N.niv† inneholder 2**(N-1) gjenstander nr.N node.
     - Det vil v‘re   (2**N)-1  interne noder i treet.
     - Det vil v‘re    2**N     eksterne noder (z-noder)
                               (= ant.interne + 1, prop.4.3 side 39 i l‘reboka)
     - Det vil finnes  2**(N-1) ulike l›sninger (for fordeling av gjenstandene).

   (Liten forklaring:  X**Y betyr:  X opph›yd i Y'te.)


OPPGAVE B:         */

#include <iostream>       //  cout
#include <cmath>          //  abs

using namespace std;

const int N = 10;         //  Antall gjenstander som skal fordeles.

                          //  De N gjenstandenes verdi:
int verdi[N+1] = { 0, 2, 14, 6, 18, 10, 12, 4, 16, 8, 20 };
char tildelt[N+1];        //  Hvem som har f†tt tildelt gjenstandene.
int min_diff = 9999;      //  Minste verdi-differanse hittil funnet.
int verdiA = 0, verdiB = 0;   //  Totalverdi av det A og B hittil har f†tt.


void skriv()  {           //  Skriver ut n†v‘rende beste tildeling:
  int i, j, tot;
  char ch;
  cout << "Min_diff: " << min_diff << '\n';  // Skriver n†v‘rende verdidifferanse.

  for (i = 0;  i <= 1;  i++)  {    //  G†r gjennom de to som blir tildelt:
      tot = 0;                     //  Nullstiller vedkommendes totalsum.
      cout << '\t' << char('A'+i) << ": ";   // Skriver 'A' eller 'B'.
      for (j = 1;  j <= N; j++)              // G†r gjennom tildelingen:
          if (tildelt[j] == char('A'+i))  {  // Om aktuell er tildelt:
             tot += verdi[j];                // Regner totalverdi.
             cout << verdi[j] << "  ";       // Skriver gjenstandens verdi.
          }
      cout << " Totalt: " << tot << '\n';    // Skriver totalverdi.
  }
  cin >> ch;
}


void fordel(int n)  {       //  Fordeler gjenstand nr.'n' etter tur til det to.
  if (n == N+1)  {          //  Alle gjenstandene er fordelt: 
     if (abs(verdiA - verdiB) < min_diff)  {   // Ny minimumsdifferanse:
        min_diff = abs(verdiA - verdiB);       // Oppdaterer "rekorden".
        skriv();                               // Skriver n†v‘rende fordeling.
     }
  } else {                  //  Flere gjenstander igjen † fordele:
     verdiA += verdi[n];   tildelt[n] = 'A';    // Lar 'A' f† nr.'n'.
     fordel(n+1);           //  Fordeler neste gjenstand. 
     verdiA -= verdi[n];    //  Tar den tilbake fra 'A'.

     verdiB += verdi[n];   tildelt[n] = 'B';    // Lar 'B' f† nr.'n'.
     fordel(n+1);           //  Fordeler neste gjenstand. 
     verdiB -= verdi[n];   tildelt[n] = '\0';   // Tar ogs† tilbake fra 'B'.
  }
}


int main()  {
  fordel(1);              //  Starter med † fordele 1.gjenstand.
  cout << "\n\n";
  return 0;
}
