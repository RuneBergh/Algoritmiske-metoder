//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S94_4.CPP

//     L›sningsforslag til kontinuasjonseksamen i "Algoritmiske metoder",
//     august 1994, oppgave 4.

//     Laget av Ove Johan Foss, HIG,  sommeren 1994.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;


const int SEEN   = 1;
const int UNSEEN = 0;


class Node  {
public:
   int data;
   int N;        //  antall naboer
   int merke;    //  brukes i merking.
   int smerke;   //  brukes i utskrift.
   Node** neste; //  array med pekere til nabonoder

public:
   Node (int d, int nn)  {
      data = d;       N = nn;       neste = new Node*[N+1];
      merke = 0;      smerke = UNSEEN;   }
   ~Node () {}
};


class Graf  {
public:
   Node* S;      //  pekere til en node i grafen
   int V;        //  antall noder

public:
   Graf (int ant_noder);
   ~Graf () { }
   void merking (Node* x, int m);  //  sjekker om graf kan merkes.
   void skrivGraf (Node* x);       //  traverserer og skriver ut data.
   void nullGraf (Node* x);        //  hjelpeprosedyre for utskrift.
};


//--------------------------------------------------
Graf :: Graf (int ant_noder)  {
//--------------------------------------------------
   int i, j, ant_kant_i_node, kant;
   Node** A = new Node*[ant_noder+1];   //  A er n† en array av pekere
					//  til noder.
   V = ant_noder;
   ifstream inn ("EX_S94_4.DTA");
   // lager alle nodene med riktig lengde p† nestearray
   for (i=1; i<=V; i++)  {
      inn >> ant_kant_i_node;   //  leser inn antall kanter for hver node
      A[i] = new Node (i, ant_kant_i_node);   //  lager node i graf
   }
   for (i=1; i<=V; i++)                        // fyller nestearray:
      for (j=1; j<=A[i]->N; j++)  {
	 inn >> kant;
	 A[i]->neste[j] = A[kant];
      }
   cout << "\n\nGraf best†r av:";
   for (i=1; i<=V; i++)  {
      cout << "\nNode " << i << " med flg. naboer: ";
      for (j=1; j<=A[i]->N; j++)
	 cout << A[i]->neste[j]->data << " ";
   }
   S = A[1];       //  hekter graf p†  S.
   for (i=1; i<=V; i++)    //  tar bort A.
      A[i] = NULL;
   delete [] A;
}


//----------------------------------------------------------------------------
void  Graf :: merking (Node* x, int m)  {
//----------------------------------------------------------------------------
   char ch;
   if ( x->merke == 0 )  {
      x->merke = m;
      for (int i=1; i<=x->N; i++)
	 merking (x->neste[i], -m);
   } else if ( x->merke == -m )  {
      cout << "\nIngen l›sning forel›pig funnet!\n";  cin >> ch;
   }
}


//----------------------------------------------------------------------------
void  Graf :: skrivGraf (Node* x)  {
//----------------------------------------------------------------------------
   if ( x->smerke == UNSEEN )  {
      x->smerke = SEEN;
      cout << "\nNode nr." << x->data << " sitt merke: " << x->merke;
      for (int i=1; i<=x->N; i++)
	 skrivGraf (x->neste[i]);
   }
}


//----------------------------------------------------------------------------
void  Graf :: nullGraf (Node* x)  {
//----------------------------------------------------------------------------
   if ( x->smerke == SEEN )  {
      x->smerke = UNSEEN;
      for (int i=1; i<=x->N; i++)
	 nullGraf (x->neste[i]);
   }
}


// -----------   hovedprogram    ---------------------------------------------

int main ()  {
   Graf G (7);          cout << endl;
   G.skrivGraf (G.S);   cout << endl;
   G.merking (G.S, 1);
   G.nullGraf (G.S);
   G.skrivGraf (G.S);
   cout << "\n\n";
   return 0;
}
