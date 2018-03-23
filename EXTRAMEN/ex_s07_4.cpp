//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S07_4.CPP

//     L›sningsforslag til kontinuasjonseksamen i "Algoritmiske metoder",
//     8.august 2007, oppgave nr.4.

//     Laget av Frode Haug, HiG, mai 2006.


#include <iostream>
#include <iomanip>

using namespace std;

const int MAXN = 50;         //  Max.antall å trekke blant.
const int MAXT = 10;         //  Max.antall som kan trekkes.

int a[MAXT+1];               //  Ant.rekker med de ulike sekv. (bruker 1-MAXT).
int b[MAXN+1];               //  Nåværende/aktuelt utvalg/rekke (bruker 1-MAXN).
int antall, N, T;            //  Tot.ant.rekker, AKTUELT antall 
                             //     å trekke BLANT (N) og trekke UT (T).

void skriv_utvalg()  {       //  Skriver nåværende utvalg/rekke:
  for (int i = 1;  i <= N;  i++)
      if (b[i])              //  Tall nr.i er valgt/trukket ut:
         cout << ' ' << i;
   cout << '\n';
}


void sjekk_utvalg()  {       //  Finner ut om ulike sekvenser forekommer i 'b':
  int i, r = 1;              //  Løkke- og indeksvariabel.
  int aa[MAXT+1];            //  Hjelpearray for å registrere sekvenser.

  antall++;                  //  Teller opp antall ulike utvalg TOTALT.
//                        skriv_utvalg();

  for (i = 1;  i <= MAXT;  i++)  aa[i] = 0;  //  Nullstiller hjelpearray.

  for (i = 2;  i <= N+1;  i++)  //  Går gjennom hele nåværende utvalg/rekke:
      if (b[i-1]  &&  b[i])     //  Tall er i sekvens:
         aa[++r]++;             //  Teller opp indeksteller og antallet.
      else                      //  Tall ikke (lengre) i sekvens: 
         r = 1;                 //  Tilbakestiller indeksteller.
/*                        cout << "\t\t\t"; 
                          for (i = 0;  i < MAXT;  i++)  cout << ' ' << aa[i];
                          cout << '\n';
                          char ch;  cin >> ch;  */
                                //  For ulike sekvenser funnet, teller opp 'a'.
  for (i = 1;  i <= MAXT;  i++)  if (aa[i])  a[i]++;
}


void lag_utvalg(int j, int t)  {    //  Genererer rekursivt ALLE mulige utvalg:
  if (t == 0)                       //  Nådd frem til et fullt utvalg/rekke:
     sjekk_utvalg();                //  Finner om ulike sekvenser i den.
  else                              //  
     for (int i = j;  i <= N-t+1; i++)  {  // ALLE MULIGE tall plukkes ut:
        b[i] = 1;                   //  Markerer at tallet er med.
        lag_utvalg(i+1, t-1);       //  Alle mulige ETTERFØLGENDE plukkes ut.
        b[i] = 0;                   //  Tallet er ikke med lengre.
    }
}


int main()  {

  do  {                 //  Leser inn aktuell 'T':
    cout << "\n\tAntall tall som trekkes ut (<=" << MAXT << "): ";  cin >> T;
  } 
  while (T < 1  ||  T > MAXT);
  do  {                 //  Leser inn aktuell 'N':
    cout << "\n\tAntall tall det trekkes blant (>=" << T 
         << " og <=" << MAXN << "): ";   cin >> N;
  } while (N < T  ||  N > MAXN);

                        //  Genererer alle mulige utvalg/rekker og teller
  lag_utvalg(1, T);     //     opp om ulike sekvenser forekommer:

                        //  Formelen for antall utvalg er:
                        //      N * (N-1) * .... * (N-T+1)
                        //      --------------------------
                        //                T!

  cout << "\n\n\tAntall ulike utvalg: " << antall << "\n\n"; 

  for (int i = 2;  i <= T;  i++)   //  Skriver data om ulike sekvenser:
     if (a[i])
        cout << "\t" << i << " på rad: " 
             << setw(8) << a[i] << '/' << antall << " = " 
             << (100.0*a[i])/antall << "%\n";

  cout << "\n\n";
  return 0;
}
