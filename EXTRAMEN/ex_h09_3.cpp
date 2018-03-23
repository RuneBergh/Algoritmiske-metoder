//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H09_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     21.desember 2009, oppgave nr.3.

//     Laget av Frode Haug, HiG, desember 2009.


#include <iostream>
using namespace std;

void byggTre();


struct Node  {
  char ID;      //  Nodens ID/navn (en bokstav).
  Node* left;	//  Peker til venstre subtre, evt. z-noden om det er tomt.
  Node* right;  //  Peker til h›yre subtre, evt. z-noden om det er tomt.
  Node (char id, Node* l, Node* r) { ID = id; left = l; right = r; }
};

                   //  Globale variable:
Node* z   = new Node('0', NULL, NULL);  //  z-noden.
Node* rot = z;                          //  Rot-peker.


/*  OPPGAVE 3A:  

3A-1: (T,16) (H,8) (X,17) (S,4) (G,9) (A,2) (V,10) (C,5) 
      (K,1) (D,12) (W,25) (L,6) (U,13) (F,3) (B,7) (J,15)

3A-2:                      W(1)
                     /              \
                  O(2)              S(3)
                /                        \
              G(4)                       J(7)
                                        /    \
                                    P(14)    X(15)
                                    /   \
                                Z(28)   B(29)
                                /   \
                             Y(56)  F(57)
                                    /
                                  T(114)
                                    \
                                    M(229)
*/


//  OPPGAVE 3B   -   Traverserer treet p† en inorder m†te.
//                   Skriver nodens ID og dets ikke-lagrede/"skjulte" nummer:
void skriv(Node* p, int n)  {    
  if (p != z)  {               //  Reell node i treet:
     skriv(p->left, n*2);      //  G†r til venstre med nr. dobbelt s† stor.
     cout << "\t(" << p->ID << ',' << n << ")\n";  //  Skriver ID og nr.
     skriv(p->right, n*2+1);   //  G†r til h›yre med nr. dobbelt s† stor + 1.
  }
}


//  OPPGAVE 3C   -  Returnerer true/false til om en node
//                  (ikke) er † finne i et usortert bin‘rtre:
bool finn(Node* p, char id)  {
 if (p == z)       return false;    //  N†dd z-node - ikke treff, hittil ...
 if (p->ID == id)  return true;     //  Node er funnet (med aktuell ID).
                          //  Finner ut om er † finne i minst ett av subtr‘rne:
 return (finn(p->left, id)  ||  finn(p->right, id));  
}


int main()  {

  byggTre();
  skriv(rot, 1);

  cout << "\n\n";
  cout << "Node med ID lik 'F' er" << (!finn(rot, 'F')? " IKKE ":" ") << "† finne i treet.\n";
  cout << "Node med ID lik 'R' er" << (!finn(rot, 'R')? " IKKE ":" ") << "† finne i treet.\n";
  cout << "Node med ID lik 'O' er" << (!finn(rot, 'O')? " IKKE ":" ") << "† finne i treet.\n";
  cout << "Node med ID lik 'D' er" << (!finn(rot, 'D')? " IKKE ":" ") << "† finne i treet.\n";
  cout << "Node med ID lik 'E' er" << (!finn(rot, 'E')? " IKKE ":" ") << "† finne i treet.\n";
  cout << "Node med ID lik 'S' er" << (!finn(rot, 'S')? " IKKE ":" ") << "† finne i treet.\n";
  cout << "Node med ID lik ' ' er" << (!finn(rot, ' ')? " IKKE ":" ") << "† finne i treet.\n";
  cout << "Node med ID lik 'D' er" << (!finn(rot, 'D')? " IKKE ":" ") << "† finne i treet.\n";
  cout << "Node med ID lik 'U' er" << (!finn(rot, 'U')? " IKKE ":" ") << "† finne i treet.\n";
  cout << "Node med ID lik 'S' er" << (!finn(rot, 'S')? " IKKE ":" ") << "† finne i treet.\n";
  cout << "Node med ID lik 'J' er" << (!finn(rot, 'J')? " IKKE ":" ") << "† finne i treet.\n";

  cout << "\n\n";
  return 0;
}


//  EXTRA   -   Bygger treet fra oppgavetekstens innledning:
void byggTre()  {
  Node *a, *b, *c, *d, *f, *g, *h, *j, *k, *l, *s, *t, *u, *v, *w, *x;
  t = new Node('T', z, z);  x = new Node('X', z, z);  w = new Node('W', z, z);
  g = new Node('G', z, z);  v = new Node('V', z, z);  u = new Node('U', z, z);
  j = new Node('J', z, z);  h = new Node('H', t, x);  d = new Node('D', z, w);
  s = new Node('S', h, g);  c = new Node('C', v, z);  l = new Node('L', d, u);
  b = new Node('B', z, j);  a = new Node('A', s, c);  f = new Node('F', l, b);
  k = new Node('K', a, f);
  rot = k;
}
