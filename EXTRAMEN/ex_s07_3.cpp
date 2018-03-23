//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S07_3.CPP

//     L›sningsforslag til kontinuasjonseksamen i "Algoritmiske metoder",
//     8.august 2007, oppgave nr.3.

//     Laget av Frode Haug, HiG, mai 2006.


#include <iostream>

using namespace std;

struct Node  {
   int   ID;	//  Nodens ID/key/nøkkel/navn (et tall).
   Node* left;	//  Peker til venstre subtre, evt. z-noden om det er tomt.
   Node* right;	//  Peker til høyre subtre, evt. z-noden om det er tomt.
   Node (int id, Node* l, Node* r)  {  ID = id ;  left = l;  right = r;  }
};


Node* z = new Node(0, NULL, NULL);  //  Globale variable:   z-noden og
Node* rot = z;                      //                      rot-peker

                             //  OPPGAVE A:
bool er_hoyre_skjevt()  {    //     Sjekker og retur om tre KUN består av 
  Node* p = rot;             //        høyre-barn (dvs. er en liste).
  while (p != z)  {          //  Ikke nådd ned til nederste/ytterst høyre node.
    if (p->left != z) return false;  // Venstre barn finnes:  Ikke høyreskjevt.
       p = p->right;         //  Går ned til neste høyre node.
  }
  return true;               //  Ingen v.barn funnet, alt OK, dvs. høyreskjevt!
}

                             //  OPPGAVE B:
Node* hoyre_rotasjon(Node* p)  {  //  Foretar en høyrerotasjon omkring 'p':
  if (p != z  &&  p->left)  {     //  Venstre-tre å rotere:
     Node* q  = p->left;          //  Hjelpepeker til den som skal roteres opp.
     p->left  = q->right;         //  Høyresiden overføres som venstreside.
     q->right = p;                //  Den nye "roten" får ny høyreside.
     return q;                    //  Returnerer ny "rot" som har rotert opp.
  } else                          //  Intet venstre-tre å rotere:
    return p;                     //  Returnerer opprinnelig peker bare.
}

                             //  OPPGAVE C:
void gjor_hoyre_skjevt()  {       //  Et tre blir fullstendig høyreskjevt:
  while (rot->left != z)          //  ALT roteres over til høyresiden av rota:
       rot = hoyre_rotasjon(rot); //   (Spesialbehandles da "p->right->left"
                                  //     (nedenfor) ikke vil ta med rota.)
  Node* p = rot;
  while (p->right != z)  {        //  Det samme gjøres for ALLE nedover mot høyre:
    while (p->right->left != z)   //  Høyrebarnet er ennå ikke høyreskjevt:
      p->right = hoyre_rotasjon(p->right);  // Gjør det høyreskjevt.
    p = p->right;                 //  Blar til neste høyre-barn.
  }
}


void display_treet()  {      // EKSTRA:
  Node* p = rot;                  // Går kun ned gjennom treet høyreside og
  while (p != z)  {               //   sjekker/ser at alle nodene nå er med:
     cout << "\tID: " << p->ID << '\n';
     p = p->right;
  }
}


int main()  {                          //  Bygger test-treet:
  Node* a = new Node(17, z, z);        //  
  Node* b = new Node(23, z, z);        //                   2
  Node* c = new Node( 4, a, b);        //                /     \  
        a = new Node(18, z, z);        //              4        93
        b = new Node( 6, z, z);        //            /   \    /    \        
  Node* d = new Node(93, a, b);        //          17    23  18     6           
      rot = new Node( 2, c, d);
  
  cout << "Treet er " << ((!er_hoyre_skjevt())? "IKKE " : "") << "høyreskjevt!\n\n";
  gjor_hoyre_skjevt();
  cout << "Treet er " << ((!er_hoyre_skjevt())? "IKKE " : "") << "høyreskjevt!\n\n";
  display_treet();
  return 0;
}
