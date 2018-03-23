//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H13_3.CPP

//     Løsningsforslag til eksamen i "Algoritmiske metoder",
//     18.desember 2013, oppgave nr.3.

//     Laget av Frode Haug, HiG, desember 2013.


#include <iostream>
using namespace std;


struct Node  {
  int   ID;	//  Nodens ID/key/nøkkel/navn (et tall).
  int   height;	//  Nodens høyde ift. dypeste subtre, dvs.
                //    lengste sti ned til en nedenforliggende bladnode.
  Node* left;	//  Peker til venstre subtre, evt. NULL når tomt.
  Node* right;	//  Peker til høyre subtre, evt. NULL når tomt.
  Node* parent;	//  Peker oppover igjen til forelder/mor,
		//		      evt. NULL om er rota.
  Node (int id, Node* p)    //  Constructor:
     { ID = id;  parent = p;  height = 0;  left = right = NULL; }
};


Node* rot = NULL;	// Rot-peker.



void inOrderTraverse(Node* n)  {    
  if (n != NULL)  {               //  Reell node i treet:
     inOrderTraverse(n->left);    //  Går til venstre subtre.
     cout << ' ' << n->ID << " (" //  Skriver noden selv
          << n->height << ")\n";  //       (ID og høyde).
     inOrderTraverse(n->right);   //  Går til høyre subtre.
  }
}



//  OPPGAVE 3A  -  Setter inn ny node. Endrer evt. høyde langs stien mot rota:

void insert(int id)  {         //  Kode (ni linjer) mye lik s.206 i læreboka:
   Node *p = rot, *q = NULL;        //  Initierer 2x pekere (q == p->parent).
   while (p != NULL)  {             //  Blar ned til der ny skal inn.
      q = p;                        //  'q' hopper etter 'p'.
      p = (id < p->ID) ? p->left : p->right;  //  Blar left/right.
   }
   p = new Node(id, q);              //  Lager ny node.
   if (q == NULL)  rot = p;          //  Spesialbehandler tomt tre.
   else if (id < q->ID) q->left = p; //  Hektes inn til venstre.
   else q->right = p;                //  Hektes inn til høyre.
                        //  NYTT/TILLEGG ift. læreboka:
                              //  Ikke kommet til rota, og mor/parent
                              //       må økes, da barnet er likt/har økt(!):
   while (q != NULL  &&  q->height == p->height)  {
     q->height++;                    //  Øker mors/parents høyde.
     p = q;                          //  'p' hopper etter 'q' OPPOVER.
     q = q->parent;                  //  'q' blar opp til mor/parent.
   }
}



//  OPPGAVE 3B  -  Returnerer node med stilengde lik 'dist' ift. 'p':
//  Forutsetning: 'p' != NULL og at de eksisterer/finnes minst en sti 
//                 med lengde >= 'dist' under 'p'.

Node* distance(Node* p, int dist)  {
  while (dist > 0)  {          //  Ikke kommet frem ennå:
    dist--;                    //  Teller ned til neste node.
                               //  Har venstre, og lang nok stilengde:
    if (p->left != NULL  &&  dist <= p->left->height)
       p = p->left;            //  Blar primært ned til venstre.
    else p = p->right;         //  Ellers MÅ det være ned til høyre,
  }                            //    pga. forutsetningen.
  return p;                    //  Returnerer noden der har stanset.
}



//  OPPGAVE 3C - Skriver nodene i treets lengste sti/path,
//                 der høyre subtre primært traverseres:

void longestPath(Node* p)  {
  while (p != NULL)  {          //  Ikke nådd ned til bladnode:
    cout << p->ID << "  ";      //  Skriver nodens ID/key.
    if (p->right != NULL)  {    //  Har et høyre barn:
                                //  Har venstre OG dette har lengste sti:
       if (p->left != NULL  &&  p->left->height > p->right->height)
          p = p->left;          //  Går til venstre.
       else                     //  Ikke venstre barn ELLER venstre minst:
          p = p->right;         //  Går til høyre.
    } else if (p->left != NULL) //  Har kun et venstre barn:
       p = p->left;             //  Går til venstre.
    else p = NULL;              //  Kommet til bladnode.
  }
}



int main()  {
  Node *n6, *n8, *n10, *n11, *n12, *n13, *n17, *n28, *n29, *n31, *n33, *n34, *n35;
  Node *pp;

//  Tester 3A:
  insert(4);
  cout << "\n\nTomt tre - etter 'insert(4)':\n";
  inOrderTraverse(rot);   cout << '\n';    // Initielt tomt tre.
  delete rot;   rot = NULL;

//  Bygger test-tre:                            //           17            //
  n10 = new Node(10, NULL);                     //       /        \        //
  n29 = new Node(29, NULL);                     //      11         33      //
  n8  = new Node( 8, NULL); n8->right = n10;    //    /    \     /    \    //
                            n10->parent = n8;   //   6      13 28     35   //
  n12 = new Node(12, NULL);                     //    \    /    \     /    //
  n31 = new Node(31, NULL); n31->left = n29;    //     8  12     31  34    //
                            n29->parent = n31;  //      \       /          //
  n34 = new Node(34, NULL);                     //      10     29          //
  n6  = new Node( 6, NULL);  n6->right  = n8;   n8->parent  = n6;
  n13 = new Node(13, NULL);  n13->left  = n12;  n12->parent = n13;
  n28 = new Node(28, NULL);  n28->right = n31;  n31->parent = n28;
  n35 = new Node(35, NULL);  n35->left  = n34;  n34->parent = n35;
  n11 = new Node(11, NULL);  n11->left  = n6;   n6->parent  = n11;  
                             n11->right = n13;  n13->parent = n11;
  n33 = new Node(33, NULL);  n33->left  = n28;  n28->parent = n33; 
                             n33->right = n35;  n35->parent = n33;
  n17 = new Node(17, NULL);  n17->left  = n11;  n11->parent = n17; 
                             n17->right = n33;  n33->parent = n17;
                           //  Setter 'height' for alle IKKE-bladnoder:
  n17->height = 4;    n11->height = 3;    n33->height = 3;    
  n6->height  = 2;    n13->height = 1;    n28->height = 2;    n35->height = 1;  
  n8->height  = 1;    n31->height = 1;
  rot = n17;

//  Tester 3A (igjen):
  cout << "\n\nInitielt tre:\n";
  inOrderTraverse(rot);   cout << '\n';

  cout << "\n\nEtter 'insert(15)' - ingen høyder har endret seg:\n";
  insert(15);
  inOrderTraverse(rot);   cout << '\n';    // Alt fortsatt samme høyde.

  cout << "\n\nEtter 'insert(30)' - høydene fra '30' mot 'rot' har endret seg:\n";
  insert(30);
  inOrderTraverse(rot);   cout << '\n';    // Sti (inkl. rot) endret høyde.


//  Tester 3B:
  pp = distance(n17, 4);   cout << "Distanse 4 ift nr.17: " << pp->ID << '\n';

  pp = distance(n33, 3);   cout << "Distanse 3 ift nr.33: " << pp->ID << '\n';

  pp = distance(n28, 1);   cout << "Distanse 1 ift nr.28: " << pp->ID << '\n';

  pp = distance(n6, 2);    cout << "Distanse 2 ift nr.6:  " << pp->ID << '\n';

  pp = distance(n17, 5);   cout << "Distanse 5 ift nr.17: " << pp->ID << '\n';


//  Tester 3C:
  cout << "\nLengste sti under '17': ";    longestPath(n17);

  cout << "\nLengste sti under '33': ";    longestPath(n33);

  cout << "\nLengste sti under '13': ";    longestPath(n13);

  cout << "\nLengste sti under '10': ";    longestPath(n10);

  cout << "\nLengste sti under 'NULL': ";  longestPath(NULL);

  cout << "\n\n";
  return 0;
}
