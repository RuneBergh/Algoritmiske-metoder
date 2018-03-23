//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H14_3.CPP

//     Løsningsforslag til eksamen i "Algoritmiske metoder",
//     15.desember 2014, oppgave nr.3.

//     Laget av Frode Haug, HiG, desember 2014.

#include <iostream>
using namespace std;

struct Node  {
  char  ID;	    //  Nodens ID/key/nøkkel/navn (et tegn).
  int   pos;    //  Posisjon i treet.
  Node* left;	//  Peker til venstre subtre, evt. NULL når tomt.
  Node* right;	//  Peker til høyre subtre, evt. NULL når tomt.
  Node (char id, int p)    //  Constructor:
       { ID = id;  pos = p;  left = right = NULL; }
};

Node* rot;	    // Rot-peker.

void preOrderTraverse(Node* n)  {    
  if (n)  {                             //  Reell node i treet:
     cout << ' ' << n->ID << " (pos: "  //  Skriver noden selv
          << n->pos << ") - barna:\t";  //       (ID og posisjon).
     if (n->left)  cout << n->left->ID;   cout << '\t'; //  Evt. venstre barn.
     if (n->right) cout << n->right->ID;  cout << '\n'; //  Evt. høyre barn.
     preOrderTraverse(n->left);         //  Går til venstre subtre.
     preOrderTraverse(n->right);        //  Går til høyre subtre.
  }
}



//  OPPGAVE 3A  -  Speilvender tre og setter nye posisjoner - 1.versjon:

void speilvend(Node* p)  {
  if (p)  {                              //  Reell node (ulik NULL).
                                         //  Bytter venstre/høyre subtre:
     Node* pp = p->left;  p->left = p->right;  p->right = pp;
     speilvend(p->left);                 //  Gjør det samme for venstre
     speilvend(p->right);                //       og høyre subtre/barn.
  }
}

void settPosisjoner(Node* p, int pos)  {
  if (p)  {                              //  Reell node (ulik NULL).
     p->pos = pos;                       //  Setter egen posisjon.
     settPosisjoner(p->left,  2*pos);    //  Gjør det samme for venstre
     settPosisjoner(p->right, 2*pos+1);  //       og høyre subtre/barn.
  }
}



//  OPPGAVE 3B  -  Speilvender tre og setter nye posisjoner - 2.versjon:

void speilvend(Node* p, int pos)  {
  if (p)  {                              //  Reell node (ulik NULL).
     p->pos = pos;                       //  Setter egen posisjon.
                                         //  Bytter venstre/høyre subtre:
     Node* pp = p->left;  p->left = p->right;  p->right = pp;
     speilvend(p->left,  2*pos);         //  Gjør det samme for venstre
     speilvend(p->right, 2*pos+1);       //       og høyre subtre/barn.
  }
}



//  OPPGAVE 3C - Returnerer (om mulig) noden med 'pos':
//               Poenget er å finne bitmønsteret for 'pos',
//               og så følge dette ned til noden med 'pos'.
//               Går derfor bare motsatt vei ift. bitmønster-bygging
//               ifm. Huffman-trie (jfr. s.329 i læreboka).

Node*  finnNode(int pos)  {
  Node* p = rot;                         //  Initierer søkepeker.
  if (p)  {                              //  Treet er ikke tomt:
     char intBinar[32];                  //  Array for bit-mønster (baklengs).
     int slutt = -1;                     //  Initieres til før arrayens start.
	                                 //  Bygger binærmønsteret for 'pos':
     while (pos)   {                     //  Så lenge bit igjen: Fyller med
       intBinar[++slutt] = (pos %  2) ? '1' : '0';  //  bakerste bitet (1/0).
       pos /= 2;                         //  Tar vekk det bakerste bitet(!).
     }
     slutt--;            //  Ignorerer første bit (rota), starter på 'slutt-1'.       
     for (int i = slutt;  p && i >= 0;  i--)    //  Gjennomgår baklengs-bitene. 
	 p = (intBinar[i] == '0') ? p->left : p->right; //  0-venstre, 1-høyre:
  } 
  return p;                           //  Returnerer noden der 'p' har stanset.


/* ALTERNATIVT:  Litt mindre effektiv, men enklere(?) å forstå/skjønne:

   Node* p = rot;			//  Initierer søkepeker.
   int   t = pos;                       //  Initierer til den søkte.

   while (p  &&  p->pos != pos)  {      //  Ennå ikke ferdig/funnet:
     while (t > p->pos*2+1)  t /= 2;    //  Finner neste barns 'pos' ift.'p'
                                        //      på veien ned mot den søkte.
     p = ((t%2) ? p->right : p->left);  //  Går ETT hakk ned til høyre/venstre.
     t = pos;                           //  Resetter til den søkte.
  } 
  return p;                           //  Returnerer noden der 'p' har stanset.
*/
}



int main()  {

//  Bygger test-tre:                              //         F(1)            //
  Node *nD = new Node('D', 19);                   //      /        \         //
  Node *nH = new Node('H', 26);                   //    E(2)       C(3)      //
  Node *nJ = new Node('J',  9);  nJ->right = nD;  //   /    \     /    \     //
  Node *nK = new Node('K', 10);                   // I(4)  A(5) M(6)  G(7)   //
  Node *nB = new Node('B', 13);  nB->left  = nH;  //   \    /    \     /     //
  Node *nL = new Node('L', 14);                   //  J(9) K(10) B(13) L(14) //
  Node *nI = new Node('I',  4);  nI->right = nJ;  //    \       /            //
  Node *nA = new Node('A',  5);  nA->left  = nK;  //    D(19)  H(26)         //
  Node *nM = new Node('M',  6);  nM->right = nB;
  Node *nG = new Node('G',  7);  nG->left  = nL;
  Node *nE = new Node('E',  2);  nE->left  = nI;   nE->right = nA;
  Node *nC = new Node('C',  3);  nC->left  = nM;   nC->right = nG;
  Node *nF = new Node('F',  1);  nF->left  = nE;   nF->right = nC;
  rot = nF;

  cout << "\n\nInitielt tre:\n";
  preOrderTraverse(rot);


//  Tester 3A:
  cout << "\n\nSpeilvender tre - 1.versjon:\n";
  speilvend(rot);
  settPosisjoner(rot, 1);
  preOrderTraverse(rot);


//  Tester 3B:
  cout << "\n\nSpeilvender tre - 2.versjon (får tilbake initielt tre):\n";
  speilvend(rot, 1);
  preOrderTraverse(rot);


//  Tester 3C:
  cout << "\n\nTester/viser 'finnNode':\n";
  cout << "Finn node med pos =  1:  " << finnNode(1)->ID  << '\n';  // F
  cout << "Finn node med pos =  2:  " << finnNode(2)->ID  << '\n';  // E
  cout << "Finn node med pos =  3:  " << finnNode(3)->ID  << '\n';  // C
  cout << "Finn node med pos =  4:  " << finnNode(4)->ID  << '\n';  // I
  cout << "Finn node med pos =  7:  " << finnNode(7)->ID  << '\n';  // G
  cout << "Finn node med pos =  9:  " << finnNode(9)->ID  << '\n';  // J
  cout << "Finn node med pos = 10:  " << finnNode(10)->ID << '\n';  // K
  cout << "Finn node med pos = 13:  " << finnNode(13)->ID << '\n';  // B
  cout << "Finn node med pos = 19:  " << finnNode(19)->ID << '\n';  // D
  cout << "Finn node med pos = 26:  " << finnNode(26)->ID << '\n';  // H
  Node* pp =  finnNode(27);
  if (pp) cout << "Finn node med pos = 27:  " << pp->ID;
  else    cout << "Ingen node med pos = 27";     cout << '\n';  
  pp =  finnNode(17);
  if (pp) cout << "Finn node med pos = 17:  " << pp->ID;
  else    cout << "Ingen node med pos = 17";     cout << '\n';  


  cout << "\n\n";
  return 0;
}
