//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H15_3.CPP

//     Løsningsforslag til eksamen i "Algoritmiske metoder",
//     14.desember 2015, oppgave nr.3.

//     Laget av Frode Haug, HiG, november 2015.

#include <iostream>
using namespace std;

struct Node  {
  int   ID;	        //  Nodens ID/key/nøkkel/navn (et tall).
  Node* left;	    //  Peker til venstre subtre, evt. NULL når tomt.
  Node* right;	    //  Peker til høyre subtre, evt. NULL når tomt.
  Node (int id)  { ID = id;  left = right = NULL; }     //  Constructor.
};

Node* rot = NULL;	// Rot-peker.
int   hoyde = 0;    // Treets nåværende/aktuell høyde.


void inOrderTraverse(Node* n)  {    
  if (n != NULL)  {                //  Reell node i treet:
     inOrderTraverse(n->left);     //  Går til venstre subtre.
	 cout << ' ' << n->ID << '\n'; //  Skriver noden selv
     inOrderTraverse(n->right);    //  Går til høyre subtre.
  }
}


//  OPPGAVE 3A - Setter inn ny node. Endrer evt. max.høyde for treet:

void insert(int id)  {         //  Mye lik kode med s.206 i læreboka:
   Node *x = rot, *p = NULL;        //  Initierer 2x pekere.
   int nivaa = 1;              //  NYTT:  Nivå-teller.
   while (x != NULL)  {             //  Blar ned til der ny skal inn.
	  nivaa++;				   //  NYTT:  Teller opp antall nivå.
	  p = x;                        //  'q' hopper etter 'p'.
      x = (id < x->ID) ? x->left : x->right;  //  Blar left/right.
   }
   x = new Node(id);                 //  Lager ny node.
   if (p == NULL)  rot = x;          //  Spesialbehandler tomt tre.
   else if (id < p->ID) p->left = x; //  Hektes inn til venstre.
   else p->right = x;                //  Hektes inn til høyre.
                               //  NYTT:  Oppdaterer evt. 'hoyde':
   if (nivaa > hoyde) hoyde = nivaa; 
}


//  OPPGAVE 3B - Returnerer (om mulig) peker til node med siste/største
//               verdi som er MINDRE enn (men IKKE lik) 'v':

Node* mindreEnn(int v)  {
  Node* p = rot, *potensiell = NULL; //  Initierer 2x pekere.
  while (p != NULL)  {              //  Går ned til "forrige" bladnode.
	if (v <= p->ID)  p = p->left;   //  SKAL/MÅ til venstre.
	else {                          //  SKAL/MÅ til høyre, men den man forlater
     potensiell = p;                //    KAN være den siste/største FØR 'v'.
	 p = p->right;                  //  Går til høyre.
   }
  }                    
  return potensiell;      //  Returnerer siste før 'v' eller (fortsatt) NULL.
}


//  OPPGAVE 3C - Siste funksjon sjekker 'niva's gyldighet.
//               Starter så evt. den første rekursive funksjonen.

void nivaaIDer(Node* p, int k, int niva)  {
  if (p)  {                                 //  Reell node:
	 if (k == niva)  cout << ' ' << p->ID;  //  Selv på aktuelt nivå: skriver
	 else  {                                //  Besøker istedet evt. subtrær:
	   nivaaIDer(p->left,  k + 1, niva);    //  Går ned til venstre.
	   nivaaIDer(p->right, k + 1, niva);    //  Går ned til høyre.
	}
  }
} 


void verdierPaaNivaa(int niva)  {
  if (niva < 0 || niva >= hoyde)
	 cout << " Ingen noder i treet har nivå nr. " << niva;
  else
	 nivaaIDer(rot, 0, niva);
  cout << '\n';
}



int main()  {

//  Tester 3A:
//  ==========
//
//          Bygger treet:
//                      17                 nivå = 0    høyde = 1
//                  /        \                 //
//                 11         33           nivå = 1    høyde = 2
//               /    \     /    \             //
//              6      13 28     35        nivå = 2    høyde = 3
//            /   \    /    \    /             //
//           5     8  12    31  34         nivå = 3    høyde = 4
//                   \      /                  //
//                   10    29              nivå = 4    høyde = 5
//                           \                 //
//                           30            nivå = 5    høyde = 6

  cout << "\n\nOppgave A:\n";
  insert(17);	cout << "Insert 17, hoyde: " << hoyde << '\n';     //  1
  insert(11);	cout << "Insert 11, hoyde: " << hoyde << '\n';     //  2
  insert(6);	cout << "Insert  6, hoyde: " << hoyde << '\n';     //  3
  insert(5);	cout << "Insert  5, hoyde: " << hoyde << '\n';     //  4
  insert(13);	cout << "Insert 13, hoyde: " << hoyde << '\n';     //  4
  insert(12);	cout << "Insert 12, hoyde: " << hoyde << '\n';     //  4
  insert(8);	cout << "Insert  8, hoyde: " << hoyde << '\n';     //  4
  insert(10);	cout << "Insert 10, hoyde: " << hoyde << '\n';     //  5
  insert(33);	cout << "Insert 33, hoyde: " << hoyde << '\n';     //  5
  insert(35);	cout << "Insert 35, hoyde: " << hoyde << '\n';     //  5
  insert(34);	cout << "Insert 34, hoyde: " << hoyde << '\n';     //  5
  insert(28);	cout << "Insert 28, hoyde: " << hoyde << '\n';     //  5
  insert(31);	cout << "Insert 31, hoyde: " << hoyde << '\n';     //  5
  insert(29);	cout << "Insert 29, hoyde: " << hoyde << '\n';     //  5
  insert(30);	cout << "Insert 30, hoyde: " << hoyde << '\n';     //  6

  cout << "\n\nTreet traversert inorder:\n";
  inOrderTraverse(rot);   cout << '\n';



//  Tester 3B:
//  ==========
  Node* pp;
  cout << "\n\nOppgave B:\n";
  pp = mindreEnn(13);
  cout << "Mindre enn 13: " << ((pp) ? pp->ID : 0) << '\n';   //  12
  pp = mindreEnn(10);
  cout << "Mindre enn 10: " << ((pp) ? pp->ID : 0) << '\n';   //   8
  pp = mindreEnn(28);
  cout << "Mindre enn 28: " << ((pp) ? pp->ID : 0) << '\n';   //  17
  pp = mindreEnn(34);
  cout << "Mindre enn 34: " << ((pp) ? pp->ID : 0) << '\n';   //  33
  pp = mindreEnn(5);
  cout << "Mindre enn  5: " << ((pp) ? pp->ID : 0) << '\n';   //   0
  pp = mindreEnn(24);
  cout << "Mindre enn 24: " << ((pp) ? pp->ID : 0) << '\n';   //  17
  pp = mindreEnn(40);
  cout << "Mindre enn 40: " << ((pp) ? pp->ID : 0) << '\n';   //  35
  pp = mindreEnn(32);
  cout << "Mindre enn 32: " << ((pp) ? pp->ID : 0) << '\n';   //  31
  pp = mindreEnn(3);
  cout << "Mindre enn  3: " << ((pp) ? pp->ID : 0) << '\n';   //   0


//  Tester 3C:
//  ==========
  cout << "\n\nOppgave C:\n";
  cout << "Nivå nr.0:  ";    verdierPaaNivaa(0);    //  17
  cout << "Nivå nr.1:  ";    verdierPaaNivaa(1);    //  11  33
  cout << "Nivå nr.2:  ";    verdierPaaNivaa(2);    //   6   13   28   35
  cout << "Nivå nr.3:  ";    verdierPaaNivaa(3);    //   5    8   12   31   34
  cout << "Nivå nr.4:  ";    verdierPaaNivaa(4);    //  10   29
  cout << "Nivå nr.5:  ";    verdierPaaNivaa(5);    //  30
  cout << "Nivå nr.6 : ";    verdierPaaNivaa(6);    //  Ingen
  cout << "Nivå nr.-1: ";    verdierPaaNivaa(-1);   //  Ingen

  cout << "\n\n";
  return 0;
}
