//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H12_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     18.desember 2012, oppgave nr.3.

//     Laget av Frode Haug, HiG, desember 2012.


#include <iostream>
#include <iomanip>
using namespace std;


struct Node  {
  int   ID;     //  Nodens ID/key/n›kkel/navn (et tall).
  Node* left;	//  Peker til venstre subtre, evt. z-noden om det er tomt.
  Node* right;  //  Peker til h›yre subtre, evt. z-noden om det er tomt.
  Node (int id, Node* l, Node* r)  //  Constructor:
       { ID = id; left = l; right = r;  }
};


//  Globale variable:
Node* z    = new Node(0, NULL, NULL);      //  z-noden (ID = 0).
Node* head = new Node(0, NULL, z);         //  Head->right peker til rota.


void insert(int v)  {                      //  Avskrift av s.206 i l‘reboka:
  Node *p, *x;
  p = head;  x = head->right;
  while (x != z)  {
    p = x;  x = (v < x->ID) ? x->left : x->right;
  }
  x = new Node(v, z, z);
  if (v < p->ID)  p->left = x;  else  p->right = x;
}


Node* search(int v)  {                     //  "Avskrift" av s.204 i l‘reboka:
  Node* x = head->right;
  while (x != z  &&  v != x->ID)
    x = (v < x->ID) ? x->left : x->right;
  return x;
}


void inorderTraverse(Node* p)  {           //  "Avskrift" av s.60 i l‘reboka:
  if (p != z)  {
     inorderTraverse(p->left);
     cout << ' ' << p->ID;
     inorderTraverse(p->right);
  }
}

                                           //  H›yrerotasjon omkring noden 'p'
Node* hoyreRotasjon(Node* p)  {            //  (jfr. kode s.225 i l‘reboka):
 Node* q = p->left;                        //  Peker venstre barn.
 p->left = q->right;                       //  Overf›rer subtre.
 q->right = p;                             //  H›yrerotasjon fullf›res.
 return q;                                 //  Returnerer ny "opprotert".
}


//  OPPGAVE 3A   -  Returnerer peker til den NEST MINSTE noden i 
//                    (sub)treet der 'p' er rot:

int nestMinst(Node* p)  {
  Node* q = z;                        //  'q' er mor/foreldre til 'p'.

  while (p->left != z)  {             //  Blar lengst mulig ned mot venstre:
     q = p;  p = p->left;
  }
                                      //  Har ingen h›yre (og venstre) - "mor"
  if (p->right == z)  return q->ID;   //    er derfor nest minste i treet.
                                      
  p = p->right;                       //  Har h›yre - blar helt til venstre
  while (p->left != z)  p = p->left;  //    i dette subtreet.

  return p->ID;                       //  DENNE er den nest minste.
}


//  OPPGAVE 3B   -  Avgj›r om et tre er fullstendig h›yreskjevt,
//                    dvs. om ALLE noder KUN har h›yrebarn:

bool erFullstendigHoyreskjevt(Node* p) {
  while (p != z)  {                   //  S† lenge ikke kommet helt ned.
    if (p->left != z)  return false;  //  Har venstrebarn - ikke h›yreskjevt.
    p = p->right;                     //  G†r videre ned mot h›yre.
  }
  return true;                        //  Bare h›yre funnet - h›yreskjevt!
}


//  OPPGAVE 3C   -  Gj›r HELE treet TOTALT h›yreskjevt:

void gjorFullstendigHoyreskjevt()  {
  Node* p = head;                     //  Starter med rota:
  while (p->right != z)  {            //  S† lenge finnes h›yrebarn:
                                      //  S† lenge h›yre har venstrebarn  -
                                      //    h›yreroter dette subtreet:
    while (p->right->left != z)  p->right = hoyreRotasjon(p->right);
    p = p->right;                     //  Bla ned til neste h›yrebarn.
  }
}


int main()  {

// Tester  Oppgave 3B p† tomt tre:
  cout << "\n\nTomt tre er ";
  if (!erFullstendigHoyreskjevt(head->right)) cout << "IKKE ";
  cout << "fullstendig h›yreskjevt.";

  insert(17);          //    Bygger treet:     17                //
  insert(22);          //                 /          \           //
  insert(19);          //               12            22         //
  insert(12);          //            /      \       /    \       //
  insert(4);           //           4        15   19      24     //
  insert(24);          //            \      /       \            //
  insert(8);           //             8    13        20          //
  insert(6);           //            / \                         //
  insert(10);          //           6   10                       //
  insert(15);
  insert(13);
  insert(20);
  cout << "\n\nTreet traversert inorder: ";
  inorderTraverse(head->right);

// Tester  Oppgave 3A:
  Node* node;
  node = search(17);
  cout << "\n\nNest minst i treet under 17 er noden: " << nestMinst(node);
  node = search(4);
  cout << "\nNest minst i treet under 4 er noden: " << nestMinst(node);
  node = search(8);
  cout << "\nNest minst i treet under 8 er noden: " << nestMinst(node);
  node = search(22);
  cout << "\nNest minst i treet under 22 er noden: " << nestMinst(node);
  node = search(15);
  cout << "\nNest minst i treet under 15 er noden: " << nestMinst(node);
  node = search(19);
  cout << "\nNest minst i treet under 19 er noden: " << nestMinst(node);

// Tester  Oppgave 3B:
  cout << "\n\nTreet er ";
  if (!erFullstendigHoyreskjevt(head->right)) cout << "IKKE ";
  cout << "fullstendig h›yreskjevt.";

// Tester  Oppgave 3C:
  gjorFullstendigHoyreskjevt();
  cout << "\n\nTreet er ";
  if (!erFullstendigHoyreskjevt(head->right)) cout << "IKKE ";
  cout << "fullstendig h›yreskjevt.";
  cout << "\n\nTreet traversert inorder: ";
  inorderTraverse(head->right);
  cout << "\n\nKun h›yrebarnene: ";
  node = head->right;
  while (node != z)
    {  cout << ' ' << node->ID;  node = node->right;  }
  cout << "\n\n";
  return 0;
}

