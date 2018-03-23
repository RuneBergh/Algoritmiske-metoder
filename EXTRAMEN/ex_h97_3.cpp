//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H97_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     18.desember 1997, oppgave 3.

//     Laget av Frode Haug, HIG,  desember 1997.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


			//  INCLUDE:
#include <iostream>        //  cout, cin
using namespace std;


const int  UNSEEN = 0;
const int  SEEN   = 1;


struct node  {
  char id;
  node* naboer[10];
  int ant_naboer;
  int merke;
  node (char i, int a)  {  id = i;  ant_naboer = a;  merke = UNSEEN; }
};

node *a, *b, *c, *d, *e;
void lag_graf()  {            //  Bygger graf som i oppgaveteksten:
  a = new node('A', 2);    b = new node('B', 1);
  c = new node('C', 2);    d = new node('D', 1);
  e = new node('E', 0);
  a->naboer[0] = b;   a->naboer[1] = c;
  b->naboer[0] = d;
  c->naboer[0] = d;   c->naboer[1] = e;
  d->naboer[0] = e;
}

			      //  Kopierer rekursivt noden "start" og alle
node* kopier(node* start)  {  //    dens etterf›lgere.
  node* kopi = new node(start->id, start->ant_naboer);
  for (int i = 0;  i < start->ant_naboer;  i++)
      kopi->naboer[i] = kopier(start->naboer[i]);
  return kopi;
}

			      //  Selve oppgavebesvarelsen:
void brettut(node* start)  {  //  Bretter ut treet.
  start->merke = SEEN;  //    //  Noden er n† bes›kt 1.gang.
  for (int i = 0;  i < start->ant_naboer;  i++)  //  For hver etterf›lger/nabo:
      if (start->naboer[i]->merke == SEEN)       //  Naboen sett:
	     start->naboer[i] = kopier(start->naboer[i]);   //  Kopierer "bare".
      else                                //  Naboen usett:
	     brettut(start->naboer[i]);       //  Bretter rekursivt ut naboen
} 		       	           	              //    (og alle dens etterf›lgere).

			//  HOVEDPROGRAM:
int main()  {
  lag_graf();
  brettut(a);
  return 0;
}

