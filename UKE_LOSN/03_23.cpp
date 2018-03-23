//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ 03_23.CPP

//   L›sningsforslag til oppgave nr. 2 og 3
//   i kap.3 s.34 i l‘reboka "Algorithms in C++".


//   Programmet viser bruken av en enkel liste best†ende av struct'er.
//   To funksjoner "movenexttofront" og "exchange" s›rger for at ulike
//   noder i listen blir flyttet om. Bruken av pekere og nodenes next-
//   peker st†r derfor sentralt i programmet.


                             //  INCLUDE:
#include <iostream>

using namespace std;

                             //  STRUCT:
struct Node  {
   int key;
   Node* next;
};
                             //  FUNKSJONSDEKLARASJONER:
void displayList(Node* t);
void movenexttofront(Node* t);
void exchange(Node* t, Node* u);

                             //  GLOBALE VARIABLE: 
Node *head, *z;

                             //  HOVEDPROGRAM:
int main()  {
        z    = new Node;   z->key  = 0;    z->next = z;
  Node* n6   = new Node;   n6->key = 6;    n6->next = z;
  Node* n5   = new Node;   n5->key = 5;    n5->next = n6; 
  Node* n4   = new Node;   n4->key = 4;    n4->next = n5; 
  Node* n3   = new Node;   n3->key = 3;    n3->next = n4; 
  Node* n2   = new Node;   n2->key = 2;    n2->next = n3; 
  Node* n1   = new Node;   n1->key = 1;    n1->next = n2; 
        head = new Node;   head->key = 0;  head->next = n1;

  cout << "\n\nInitiell liste:";
  displayList(head->next);            //   1  2  3  4  5  6

  movenexttofront(n3);
  cout << "\n\nN†r 'n4' er flyttet f›rst:";
  displayList(head->next);            //   4  1  2  3  5  6

  movenexttofront(n6);
  cout << "\n\nN†r halen er fors›kt flyttet f›rst:";
  displayList(head->next);            //   4  1  2  3  5  6

  movenexttofront(n5);
  cout << "\n\nN†r siste er flyttet f›rst:";
  displayList(head->next);            //   6  4  1  2  3  5 

  movenexttofront(n4);
  movenexttofront(n4);
  movenexttofront(n3);
  cout << "\n\nN†r 'n1', 'n2' og 'n5' er flyttet f›rst:";
  displayList(head->next);            //   5  2  1  6  4  3


  exchange(n2, n3);
  cout << "\n\nPr›ver † bytte 'n1' med halen:";
  displayList(head->next);            //   5  2  1  6  4  3

  exchange(n6, n6);
  cout << "\n\nPr›ver † bytte 'n4' med seg selv:";
  displayList(head->next);            //   5  2  1  6  4  3

  exchange(n2, n6);
  cout << "\n\nN†r 'n1' er byttet med 'n4':";
  displayList(head->next);            //   5  2  4  6  1  3

  exchange(n6, n5);
  cout << "\n\nN†r 'n1' er byttet med 'n2':";
  displayList(head->next);            //   5  1  4  6  2  3

  exchange(head, n2);
  cout << "\n\nN†r 'n5' er byttet med 'n3':";
  displayList(head->next);            //   3  1  4  6  2  5

  cout << "\n\n";
  return 0;
}
                             //  DEFINISJONER AV FUNKSJONER:
                                       //  Viser listens innhold, 
void displayList(Node* t)  {           //    startende med 't'.     
   cout << "\n";
   while (t != z)  {                   //  S†lenge ikke n†dd halen:
     cout << t->key << "  ";           //  Skriver ID/key.
     t = t->next;                      //  ker peker til neste node.
   }
}

                                       //  Flytter (om mulig) Noden ETTER t 
void movenexttofront(Node* t)  {       //    til starten av listen. 
  if (t->next != z)  {                 //  Den neste er IKKE halen:
     Node* w = t->next;                //  Hjelpepeker til den som skal ut.
     t->next = w->next;                //  Hekter ut av listen.
     w->next = head->next;             //  Setter inn igjen f›rst 
     head->next = w;                   //    (etter hodet).
  }
}
                                       //  Bytter (om mulig) nodene ETTER
void exchange(Node* t, Node* u)  {     //    henholdsvis t og u.
                                       //  INGEN av de neste er halen:
  if (t->next != z  &&  u->next != z)  {
     if (t != u)  {                    //  De to er IKKE like:
        Node *x, *y;
                                       //  De to er IKKE etterf›lgende:
        if (t->next != u  &&  u->next != t)  {
           x = t->next;                //  Setter hjelpepekere til de
           y = u->next;                //    to som skal tas ut.
           t->next = x->next;          //  Hekter de to ut av listen.
           u->next = y->next;
           y->next = t->next;          //  Hekter y inn igjen etter t.
           t->next = y;
           x->next = u->next;          //  Hekter x inn igjen etter u.
           u->next = x;
        } else  {                      //  De to er etterf›lgende:
           if (u->next == t)           //  't' kommer RETT ETTER 'u'
                                       //  Bytter da om pekerne:
              {  Node *w = u;   u = t;   t = w;  }
                       // Invariant: 't' peker ALLTID til den f›rste av de to.
           y = u->next;                //  Setter hjelpepeker til den siste.
           u->next = y->next;          //  Hekter den ut.
           y->next = t->next;          //  Hekter inn igjen mellom t og u.
           t->next = y;                //    (Husk at:  t->next == u) 
        }
     }
  }
}
