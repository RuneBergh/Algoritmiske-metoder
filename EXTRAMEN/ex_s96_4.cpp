//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S96_4.CPP

//     L›sningsforslag til kontinuasjonseksamen i
//     "Algoritmiske metoder", oppgave nr.4, september 1996.

//     Laget av Frode Haug,  HIG,  september 1996.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>
using namespace std;


const int N = 6;                                 //  Antall noder i grafen
int G[N+1][N+1] = { { 0, 0, 0, 0, 0, 0, 0 },     //  Nabomatrisen (laget ut
                    { 0, 1, 1, 0, 1, 0, 0 },     //    fra figuren i oppgaven)
					{ 0, 1, 1, 1, 1, 1, 1 },
					{ 0, 0, 1, 1, 0, 0, 0 },
					{ 0, 1, 1, 0, 1, 0, 1 },
					{ 0, 0, 1, 0, 0, 1, 0 },
					{ 0, 0, 1, 0, 1, 0, 1 } };
int utplukk[N+1];                                //  Ikke-nabo utplukk.
int ant = 0;                                     //  Antallet i utplukket.


void genresten(int k)  {
  int i, j, m;
  for (i = k;  i <= N;  i++)  {     // Fors›k med ALLE en-nodes utvidelser:
      for (j = 1;  j <= ant;  j++)
	  if ( G[utplukk[j]][i] )  goto Ikke_mulig;   // Ubrukelig pga. kant.
      //  Vet her at 'i' er en brukbar utvidelse:
      utplukk[++ant] = i;           //  Utskrift:
	 cout << '\n';   for (m = 1;  m <= ant;  m++)  cout << utplukk[m];
      if (i < N) genresten(i+1);    //  Genererer mere ?
      ant--;
    Ikke_mulig:  ;   //  NB: Label M etterf›lges av (tom) setning/statement.
  }
}


int main()  {
  genresten(1);
  cout << "\n\n";
  return 0;
}
