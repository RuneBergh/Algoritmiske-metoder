//  Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ 32_7.CPP

//  Programmet finner ut om en gitt rettet graf er en "dag" (Directed Acyclic
//  Graph) eller ei. Dette gj›res ved † ta utgangspunkt i hver enkelt node,
//  og unders›ke om det er mulig † komme tilbake til denne noden, ved † f›lge
//  rettede kanter i grafen.

#include <iostream>

using namespace std;


const int  V = 13;              // Antall noder i grafen (A-M)
enum status  { unseen, seen };  // En nodes status.
			//  Jfr. fig.32.8  evnt. med ekstra kanter slik at
			//    vi f†r cykel (f.eks. snu JG eller JM):
			//     A  B  C  D  E  F  G  H  I  J  K  L  M
int graph[V+1][V+1]  =  { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		/* A */   { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
		/* B */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		/* C */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		/* D */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		/* E */   { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		/* F */   { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		/* G */   { 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
		/* H */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
		/* I */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		/* J */   { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1 },
		/* K */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		/* L */   { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		/* M */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

int val[V+1];      // Hvilke noder er for ›yeblikket i stien (val[i] == seen).


void visit(int k, int n)  {       //  Koden s.427 i l‘reboka (noe endret):
  char ch;
//         cout << "\nK: " << char(k+'A'-1) << "\tN: " << n;   cin >> ch;
  int t;
  val[k] = seen;                  //  Setter at node 'k' er med i stien.
  for (t = 1;  t <= V;  t++)
     if (graph[k][t] != 0)       //  Bes›ker alle naboene:
	    if (val[t] == unseen) visit(t, n+1);    // Naboen er IKKE med i stien:
	    else  {                  //  Naboen er med i stien - CYKEL !! :
	       cout << "\n\nNoden '" << char(k+'A'-1) << "' ligger i en cykel.";
	       cin >> ch;
		}
  val[k] = unseen;                //  Node 'k' er IKKE lenger med i stien.
}


int main()  {
  int k;
  cout << "Ingen cykel funnet !\n\n";    //  Antar at ingen cykler (skriver dette).

  for (k = 1;  k <= V;  k++)  val[k] = unseen;   // Se s.424 i l‘reboka.
  for (k = 1;  k <= V;  k++)  visit(k, 0);
  return 0;
}
