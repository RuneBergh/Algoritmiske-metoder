//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S04_3.CPP

//     Løsningsforslag til kontinuasjonseksamen i
//     "Algoritmiske metoder", oppgave nr.3, 13.august 2004.

//     Laget av Frode Haug, HiG, juni 2004.


/*
 OPPGAVE 3A:

 Del 1:    
         Indeks  Node  Venstre  H›yre
            5     18       8     10      <---   Endret
           10     19      -1     -1      <---   Ny


 Del 2:
         Treet:            16
                        /      \
                     10          33
                    /  \        /
                   4     15   18
                    \           \
                     7           30
                                /
                               21
                                 \
                                  25

        Gir tabellen:
              Indeks  Node  Venstre  H›yre
                 0      16     1       4
                 1      10     3       2  
                 2      15    -1      -1
                 3       4    -1       7
                 4      33     5      -1
                 5      18    -1       6
                 6      30     8      -1
                 7       7    -1      -1
                 8      21    -1       9
                 9      25    -1      -1


 OPPGAVE 3B:
*/


#include <iostream>
using namespace std;

const int N = 100;
const int TOMT = -1;
int rot = TOMT;
int tab[N][3];          //  Global - og initieres derfor til bare 0'er.


                        //  SELVE OPPGAVEN:
void legg_inn(int v)  {
  int p, c, n = 0;      //  'c' er barn til 'p',
                        //  'n' er indeks for første ledige rad/linje i 'tab'.
  while (n < N   &&  tab[n][0] != 0)  n++;  //  Finner evt. første ledige rad.

  if (n != N)  {              //  Tabellen er IKKE full allerede:
     p = TOMT;   c = rot;     //  Initiere 'p' og 'c'.
	 while (c != TOMT)  {     //  Blar til finner plass der skal inn:
       p = c;                 //  'p' hopper etter/nedover.
	   c = (v < tab[c][0]) ? tab[c][1] : tab[c][2]; // Setter til aktuelt barn.
	 }
	
     if (p == TOMT)  rot = n;           //  Treet var tomt (ikke gått nedover).
	 else if (v < tab[p][0])  tab[p][1] = n;  // Mindre inn 'p' (venstre barn).
	 else tab[p][2] = n;                      // Større eller lik enn 'p'.
	 					 
	 tab[n][0] = v;  tab[n][1] = tab[n][2] = TOMT; // Legger inn ny node/verdi.

  } else
	cout << "\nIkke plass til flere noder/verdier i tabellen!\n\n";
}



int main()  {
  int vv, i;
  cout << "Verdi: ";  cin >> vv;

  while (vv > 0)  {
    legg_inn(vv);
	cout << "\n\tRot: " << rot;
    for (i = 0;  i < N;  i++)            //  Skriver ut HELE tabellen:
		cout << "\n\t" << i << ": " << tab[i][0]
		     << "\t" << tab[i][1] << "\t" << tab[i][2];
    cout << "\nVerdi: ";  cin >> vv;
  }
   return 0;
}
