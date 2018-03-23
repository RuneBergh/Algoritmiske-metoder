//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H96_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     19.desember 1996, oppgave 3.

//     Laget av Frode Haug, HIG,  desember 1996.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>       //  cout
using namespace std;


class node  {
public:
  char navn;                //  Nodens navn/ID.
  node* forste_subtre;      //  F›rste subtre. Er NULL dersom ingen subtr‘r.
  node* neste_sosken;       //  Neste node i listen man er subtre sammen med.
			    //  Er NULL dersom man selv er det siste subtreet.
			    // Ekstra constructor for † kunne bygge opp et
  node(char nvn, node* fs, node* ns)    // tre for testing av "skriv_ut".
     {  navn = nvn;   forste_subtre = fs;  neste_sosken = ns;  }
};


void skriv_ut(node* n)  {     //  ETT l›sningsforslag (best?):
  cout << ' ' << n->navn;     //  Prefiks: Skriver derfor alltid f›rst navnet.
  if (n->forste_subtre != NULL)  {     //  Dersom har noen subtre/barn:
     cout << '(';                      //  Skal ALLTID omsluttes av parantes.
     skriv_ut(n->forste_subtre);       //  Skriver subtreet.
     cout << ')';
  }
  if (n->neste_sosken != NULL)  {      //  Dersom har s›sken:
     cout << ',';                      //  Skal ALLTID skilles med komma.
     skriv_ut(n->neste_sosken);        //  Skriver s›skenet.
  }
}


void skriv_ut2(node* n)  {    //  Et ANNET l›sningsforslag:
  cout << ' ' << n->navn;     //  Prefiks: Skriver derfor alltid f›rst navnet.
  if (n->forste_subtre != NULL)  {     //  Dersom har noen subtre/barn:
     node* pk;                         //  Hjelpe-peker.
     cout << '(';                      //  Skal ALLTID omsluttes av parantes.
     pk = n->forste_subtre;            //  Initierer til f›rste subtre.
     while (pk != NULL)  {
	    skriv_ut2(pk);                 //  Skriver subtreet rekursivt nedover.
	    pk = pk->neste_sosken;         //  G†r gjennom alle ens egne subtr‘r!
	    if (pk != NULL) cout << ',';   //  Dersom ikke siste subtre.
     }
     cout << ')';                      //  Ferdig med alle ens egne subtr‘r.
  }
}


int main ()  {
  node* tmp1, * tmp2, * tmp3, * tmp4;
  tmp1 = new node('t', NULL, NULL);
  tmp1 = new node('s', NULL, tmp1);
  tmp1 = new node('r', NULL, tmp1);
  tmp2 = new node('z', NULL, NULL);
  tmp3 = new node('y', NULL, NULL);
  tmp3 = new node('x', NULL, tmp3);
  tmp4 = new node('K', tmp1, NULL);
  tmp4 = new node('H', tmp2, tmp4);
  tmp4 = new node('G', tmp3, tmp4);
  tmp4 = new node('F', tmp4, NULL);    // "Tmp4" peker n† til rota.

  cout << "EN versjon av 'skriv_ut':  ";
  skriv_ut(tmp4);
  cout << "\n\nEn ANNEN versjon av 'skriv_ut':  ";
  skriv_ut2(tmp4);
  cout << "\n\n";
  return 0;
}
