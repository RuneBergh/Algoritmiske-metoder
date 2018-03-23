//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H08_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     19.desember 2008, oppgave nr.3.

//     Laget av Frode Haug, HiG, desember 2008.



#include <iostream>
using namespace std;

struct Node  {
  int   ID;     //  Nodens ID/key/n›kkel/navn (et tall).
  Node* left;	//  Peker til venstre subtre, evt. z-noden om det er tomt.
  Node* right;  //  Peker til h›yre subtre, evt. z-noden om det er tomt.
  Node (int id, Node* l, Node* r) { ID = id; left = l; right = r; }
};

                   //  Globale variable:
Node* z   = new Node(0, NULL, NULL);  //  z-noden.
Node* rot = z;                        //  Rot-peker.


//  OPPGAVE 3A:          Finner antall noder i 'p' st›rre enn 'v':
int tellStorre(Node* p, int v)  {
  if (p != z)  {           //  Ulikt z-noden:
     if (p->ID > v)        //  Noden (fortsatt) st›rre enn 'v':
                           //  Returnerer seg selv + antallet i subtr‘rne:
        return (1 + tellStorre(p->left, v) + tellStorre(p->right, v));
     else                  //  Noden mindre enn eller lik 'v':
         return 0;         //  Returnerer 0 - avbryter/avskj‘rer rekursjonen.
  } else                   //  N†dd ned til en blad-/z-node:
    return 0;
}


//  OPPGAVE 3B:          Finner ut om 'p' tilfredsstiller heap-betingelse:
bool erHeapOrdnet(Node* p)  {
  if (p != z)  {         //  Er selv ikke z-noden:
                         //  Venstre barn finnes og er st›rre:
     if (p->left  != z  &&  p->left->ID > p->ID)  return false;
                         //  H›yre barn finnes og er st›rre:
     if (p->right != z  &&  p->right->ID > p->ID) return false;
                         //  St›rre eller lik begge barna. Sjekker om
                         //    det samme er sant for begge subtr‘rne:
     return (erHeapOrdnet(p->left)  &&  erHeapOrdnet(p->right));
  } else                 //  z-noden - er pr.def. heap-sortert:
    return true;
}


void byggTre();
void display(Node* p);


int main()  {
  int x;                 //  Innlest og ›nsket verdi fra brukeren.

  byggTre();   
//  display(rot);
  
  cout << "\n\nEr st›rre enn verdien: ";  cin >> x;
  cout << "\nAntall noder st›rre enn " << x << ": " 
       << tellStorre(rot, x) << '\n';

  cout << "\nTreet tilfredsstiller " << ((erHeapOrdnet(rot)) ? "" : "IKKE ")
       << "heap-betingelsen!\n\n\n";

  rot->left->ID = 28;            //  Endrer verdien 18 til 28.
//  display(rot);
  cout << "\nTreet tilfredsstiller " << ((erHeapOrdnet(rot)) ? "" : "IKKE ")
       << "heap-betingelsen!\n\n\n";

  return 0;
}


//  EXTRA:                   Bygger et tre som tilfredsstiller heap-betingelsen:
void byggTre()  {
  Node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;

  j = new Node( 4, z, z);    //   Bygger treet:      23
  i = new Node( 2, z, z);    //                   /      \  
  h = new Node( 7, z, z);    //                 18       21
  g = new Node( 8, z, z);    //                /  \     /  \  
  f = new Node(12, z, j);    //              18   13  12    8
  e = new Node(13, h, i);    //                   / \   \   
  d = new Node(18, z, z);    //                   7  2   4
  c = new Node(21, f, g);
  b = new Node(18, d, e);
  a = new Node(23, b, c);
  rot = a;
}


//  EXTRA:                   Traverserer og skriver treet preorder:
void display(Node* p)  {    
  if (p != z)  {
     cout << "\tID: " << p->ID << "   (" << p->left->ID
                               << ", "   << p->right->ID << ")\n";
     display(p->left);
     display(p->right);
  }
}
