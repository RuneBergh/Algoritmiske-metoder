//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H96_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     19.desember 1996, oppgave 4.

//     Laget av Frode Haug, HIG,  desember 1996.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>         //  cout
#include <fstream>          //  ifstream
#include <cstdlib>          //  exit

using namespace std;

const int ANT   = 3;        //  Max. antall ›nsker for EN person.
const int MAX_M = 200;      //  Max. antall gjenstander til fordeling
const int MAX_N = 100;      //  Max. antall personer som har ›nsker.

int N,      //  Aktuelt antall personer som har tre ›nsker hver.
    M;      //  Aktuelt antall gjenstander som skal fordeles.

int gjenstand[MAX_M+1];     //  Den som i ›yeblikket er tildelt gjenstand nr.i
int beste_fordeling[MAX_M+1];     //  Beste fordeling av gjenstander.
int onsker[MAX_N+1][ANT+1];       //  Personenes ›nsker.
bool losning_funnet = false;      //  Funnet noen l›sning i det hele tatt.
int beste_prioritet = (MAX_N * ANT) + 1;  //  Beste TOTALE prioritet.
int total_prioritet = 0;                  //  N†v‘rende totale prioritet.


void les_fra_fil()  {         //  Leser ›nskene fra fil:
  ifstream inn("EX_H96_4.DTA");
  inn >> M >> N;              //  Leser antall gjenstander og personer.
	   if (M <= 0  ||  M > MAX_M  ||  N <= 0  ||  N > MAX_N)
	      {  cout << "\nM og/eller N i galt intervall";  exit(0);  }
  for (int i = 1;  i <= N;  i++)     //  Leser personenes ›nsker:
      inn >> onsker[i][1] >> onsker[i][2] >> onsker[i][3];
}


void kopier(int a[], int b[])  {     //  Kopier innholdet mellom to arrayer:
  for (int i = 1;  i <= M;  i++)   b[i] = a[i];
}


void fordel_gjenstander(int n)  {   //  Person nr.'n' skal tildeles gjenstand.
  if (n > N)  {                     //  Ny beste-l›sning funnet:
     if (!losning_funnet)  losning_funnet = true;  //  1.gang finner l›sning.
     beste_prioritet = total_prioritet;            //  Oppdaterer den beste.
     kopier(gjenstand, beste_fordeling);           //  Kopierer den beste.
  }  else  {
     for (int i = 1;  i <= ANT;  i++)       //  G†r gjennom en brukers ›nsker:
	 if (!gjenstand[onsker[n][i]])  {   //  Gjenstanden er IKKE opptatt:
	    total_prioritet += i;           //  Teller opp total-prioriteten.
						       //  AVSKJ’RING:
	    if (total_prioritet < beste_prioritet)  {  //    Ny rekord mulig ?
	       gjenstand[onsker[n][i]] = n;      //  Gjenstanden setts opptatt.
	       fordel_gjenstander(n+1);          //  Neste personer tildeles.
	       gjenstand[onsker[n][i]] = 0;      //  Tilbakestiller.
	    }
	    total_prioritet -= i;                //  Tilbakestiller.
	 }
  }
}


int main ()  {
   les_fra_fil();
   fordel_gjenstander(1);
   if (losning_funnet)  {
      cout << "\n\nTotalt beste prioritet ble " << beste_prioritet
	   << ", i forhold til " << N << " som er et minimum.";
      cout << "\n\nBeste l›sning er:";
      for (int i = 1;  i <= M;  i++)
	  cout << "\nGjenstand nr."  << i
	       << "  til person nr." << beste_fordeling[i];
   } else
     cout << "\n\nIngen fordeling mulig, da for mange "
	  << "personer ›nsker seg de samme gjenstandene!";
   cout << "\n\n";
   return 0;
}
