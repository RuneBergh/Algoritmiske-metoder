//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S17_3.CPP

//  Løsningforslag til kontinuasjonseksamen i Alg.met, august 2017, oppgave nr.3.
//  Laget av Frode Haug, NTNU


#include <iostream>
using namespace std;

struct Node  {
  int   ID;          //  Nodens ID/key/nøkkel/navn (et tall).
  Node* left;        //  Peker til venstre subtre (evt. 'nullptr').
  Node* right;       //  Peker til høyre subtre (evt. 'nullptr').
  int   leftNumber;  //  Antall noder totalt i venstre subtre.
  Node(int id) { ID = id;  left = right = nullptr;  leftNumber = 0; }
};

Node* root = nullptr;        // root-peker.


//  OPPGAVE 3A - Tre stk deloppgaver:
/*

  Del 1:
     Nodene 1-15 settes først inn i treet i inorder rekkefølge
     (jfr. figur rett nedenfor).
     Når treet leses levelorder, vil EN rekkefølge for innsetting kunne være:
     9   3   14   1   5   11   15   2   4   7   10   13   6   8   12
     Men, det er mange andre(!) rekkefølger som også gir det samme treet.


  Del 2:   Nodene 1-15 innsatt i det gitte binære søketreet,
           samt 'leftNumber' i parentes bak hver node/ID:
                          9(8)
                   /               \
             3(2)                     14(4)
        /         \                 /     \
      1(0)          5(1)         11(1)     15(0)
        \        /     \         /    \
          2(0)  4(0)     7(1)  10(0)  13(1)
                       /   \          /
                      6(0)  8(0)    12(0)


  Del 3:    */

int minst() {
  Node* p = root;
  if (!p)  return 0;
  while (p->left)  p = p->left;
  return p->ID;
}


//  OPPGAVE 3B - Setter inn i binært søketre, OG OPPDATERER 'leftNumber':
                             //  Setter inn i binært søketre (jfr.side 206 i
void settInn(int id) {       //    læreboka UTEN 'head', men med ETT tillegg):
  Node *p = nullptr, *x = root;      //  Initierer pekere.
  while (x) {                        //  Ikke nådd ned til bladnode.
      p = x;                         //  p hopper etter.
      if (id < x->ID) {              //  Skal ned til venstre:
         x->leftNumber++;   //  NYTT: Antall i venstre subtre kommer til å øke.
         x = x->left;                //  Går til venstre.
      } else                         //  Skal ned til høyre:
         x = x->right;               //  Går til høyre.
  }
  x = new Node(id);                  //  Lager ny node.
  if (!p)  root = x;                 //  Treet er tomt (blir første node).
  else if (id < p->ID) p->left = x;  //  Hektes på nederst til venstre.
  else p->right = x;                 //  Hektes på nederst til høyre.
}


//  OPPGAVE 3C - Returnerer IDen til noden som er nr.'n' i inorder
//               rekkefølge i treet. Den første noden er nr.0. 
//               Forutsetning: 'n' er gyldig ift. antall noder i treet.

int hent(int n) {
    Node* p = root;                 //  Starter i rota.

    while (true) {                          //  Ennå ikke funnet relevant node:
        if (n < p->leftNumber) p = p->left; //  Noden er blant de venstre.
        else if (n == p->leftNumber) return p->ID;  //  Funnet  nr.'n'.
        else {                              //  Noden er ned til høyre:
            n -= (p->leftNumber + 1);       //  Oppdaterer nr å lete etter.
            p = p->right;                   //  Går ned til høyre.
        }
    }
}


// ---------------------------------------------------------------------------


void skrivInorder(Node* n) {
    if (n) {
        skrivInorder(n->left);
        cout << "   " << n->ID << '(' << n->leftNumber << ')';
        n->ID *= 3;                         //  Tredobler nodens ID.
        skrivInorder(n->right);
    }
}


int main()  {

//  Tester 3B, og skriver ut treet:
  settInn(9);  settInn(3);  settInn(14); settInn(1); settInn(5);
  settInn(11); settInn(15); settInn(2);  settInn(4); settInn(7);
  settInn(10); settInn(13); settInn(6);  settInn(8); settInn(12);
  skrivInorder(root);

//  Tester 3A - del 3 - etter at alle nodenes ID er tredoblet:
  cout << "\n\nTreets minste verdi: " << minst() << "\n\n";

//  Tester 3C:
  cout << "Den  0.noden i inorder har verdien:  " << hent(0) << '\n';    //   3
  cout << "Den  1.noden i inorder har verdien:  " << hent(1) << '\n';    //   6
  cout << "Den  4.noden i inorder har verdien: "  << hent(4) << '\n';    //  15
  cout << "Den  8.noden i inorder har verdien: "  << hent(8) << '\n';    //  27
  cout << "Den 10.noden i inorder har verdien: "  << hent(10) << '\n';   //  33
  cout << "Den 12.noden i inorder har verdien: "  << hent(12) << '\n';	 //  39
  cout << "Den 14.noden i inorder har verdien: "  << hent(14) << "\n\n"; //  45

  return 0;
}
