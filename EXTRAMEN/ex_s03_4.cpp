//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \ EX_S03_4.CPP

//     L›sningsforslag til eksamen i 
//     "Algoritmiske metoder (I)", oppgave nr.4, 8.august 2003.

//     Laget av Frode Haug, HiG, august 2003.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>     //  cout
using namespace std;


struct node  {               //  Nodene/elementene i lista:
  char ID;                   //  Dens ID/key.
  node* neste;               //  Peker til neste noden (etterf›lgeren).
  node(char c)  {  ID = c;  neste = NULL;  }    //  Constructor.
};


void bruk_liste(node* n)  {  //  "Bruker" (skriver ut) n†v‘rende liste:
  n = n->neste;              //  Hopper over "hodet".
  while (n != NULL)  {  cout << n->ID << ' ';   n = n->neste;  }
  cout << '\n';
}

                             //  Globale pekere til listens dummy hode
node *forste, *siste;        //    (denne forblir uendret) og dens
                             //    n†v‘rende siste element (denne endrer seg).

                             //  Flytter f->neste bakerst. Dvs. venstre-
                             //    roterer lista ETTER den tilpekt av 'f':
void flytt_bakerst(node* f) {   // INVARIANT: f->neste peker ALDRI til NULL
  siste->neste = f->neste;   f->neste = f->neste->neste;  //  eller 'siste'!
  siste = siste->neste;  siste->neste = NULL;
}
                        //  SELVE OPPGAVEN:
                             //  Skal lage ALLE permutasjoner av lista f.o.m.
                             //    'e->neste' t.o.m 'siste':
                             //  Skal ogs† "levere tilbake" lista n›yaktig 
void permuter(node* e)  {    //     slik man fikk den inn selv.
  node* ss;                  //  Hjelpepeker.
  if (e->neste == siste)     //  N†dd det siste elementet (og ny permutasjon).
     bruk_liste(forste);     //  Bruker/gj›r noe med aktuell versjon.
  else  {                    //  Fortsatt igjen † permutere:
     ss = siste;             //  Lager peker til n†v‘rende siste node. 
     permuter(e->neste);  flytt_bakerst(e);     //  Permuterer n†v‘rende liste.
     while (ss != siste)  {  //  S† lenge sublisten ikke er rotert rundt:
        permuter(e->neste);  flytt_bakerst(e);  //  Permuterer og flytter den 
     }                                          //    forrerste inn bakerst.
  }
}


int main()  {           //  HOVEDPROGRAM:
 node* ny;                   //  Lager en liste best†ende av fire elementer
 ny = new node('D');  forste = siste = ny;      //  pluss dummy hode ('.'):
 ny = new node('C');  ny->neste = forste;  forste = ny;
 ny = new node('B');  ny->neste = forste;  forste = ny;
 ny = new node('A');  ny->neste = forste;  forste = ny;
 ny = new node('.');  ny->neste = forste;  forste = ny;

 permuter(forste);           //  F†r generert alle mulige permutasjoner.

 bruk_liste(forste);         //  Viser at lista er rotert tilbake
                             //    til utgangspunktet.
 cout << '\n';
 return 0;
}
