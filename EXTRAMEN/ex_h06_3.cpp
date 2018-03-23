//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H06_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     4.desember 2006, oppgave nr.3.

//     Laget av Frode Haug, HiG, november 2006.


#include <iostream>

using namespace std;

struct Node  {
   int   ID;    //  Nodens ID/key/n›kkel/navn (et tall).
   Node* left;	//  Peker til venstre subtre, evt. z-noden om det er tomt.
   Node* right; //  Peker til h›yre subtre, evt. z-noden om det er tomt.
   Node (int id, Node* l, Node* r)  {  ID = id ;  left = l;  right = r;  }
};


Node* z = new Node(0, NULL, NULL);  //  Globale variable:   z-noden og
Node* rot = z;                      //                      rot-peker


int hoyde(Node* p, int id)  {       //  Returnerer (om mulig) h›yden fra
  int hoy = 0;                      //    node 'p' og ned til verdien 'id'.
  while (p != z)  {                 //    Om 'id' ikke finnes returneres -1.
    if (p->ID == id)  return hoy;
    p = (id < p->ID) ? p->left : p->right;
    hoy++;
  }
  return -1;
}

                             //  OPPGAVEN:
                                    //  Funksjon som finner 'avstanden'  
int avstand(int id1, int id2)  {    //    (antall kanter) mellom nodene
                                    //    med 'id1' og 'id2'.
  Node* p = rot;                    //  Peker til † "bla" nedover.
  int v_hoyde, h_hoyde;             //  H›yden/avstanden ned til venstre/h›yre. 
                      //  Poenget er † finne de to nodenes n‘rmeste forgjenger.
                      //  Dette gj›r vi ved †:
                      //     - alltid s›rge for at 'id1' er den minste
                      //     - lete nedover inntil de to blir liggende p† hver
                      //       sin side av en node ('p').
  if (id1 > id2)  {                 //  S›rger for at ALLTID er id1 minst:
     int temp = id1;  id1 = id2;  id2 = temp;
  }
                                    //  Leter seg (om mulig) fram 'p' der id1 og
  while (p != z)  {                 //    id2 ligger p† hver sin side av denne:
    if (id2 < p->ID)      p = p->left;    //  BEGGE er til venstre.
    else if (id1 > p->ID) p = p->right;   //  BEGGE er til h›yre.
    else  {                               //  De er p† hver sin side:
      v_hoyde = hoyde(p, id1);            //  Finner h›yden i venstre subtre.
      if (v_hoyde == -1) return -1;       //  'id1' fantes ikke: returnerer -1.
      h_hoyde = hoyde(p, id2);            //  Finner h›yden i h›yre subtre.
      if (h_hoyde == -1) return -1;       //  'id2' fantes ikke: returnerer -1.
      return (v_hoyde + h_hoyde);         //  Returnerer avstanden mellom.
    }
  }
  return -1;                             //  Bladde helt ut/ned: returnerer -1.
}


void display(Node* p)  {            // EKSTRA:
  if (p != z)  {
     display(p->left);
     cout << "\tID: " << p->ID << "  (" << p->left->ID
                               << ", "  << p->right->ID << ")\n";
     display(p->right);
  }
}


int main()  {                          //  Bygger test-treet:
  Node* a = new Node( 3, z, z);        //  
  Node* b = new Node(12, z, z);        //                  22
  Node* c = new Node( 4, a, b);        //                /     \  
        a = new Node(28, z, z);        //              4        33
        b = new Node(46, z, z);        //            /   \    /    \        
  Node* d = new Node(33, a, b);        //           3    12  28    46
      rot = new Node(22, c, d);        //                   /  \  /  \  
  a->left  = new Node(23, z, z);       //                  23  31 40 49
  a->right = new Node(31, z, z);
  b->left  = new Node(40, z, z);
  b->right = new Node(49, z, z);
//                                    display(rot);       //    Gir svaret:
  cout << "\nAvstanden mellom  4 og 33: " << avstand( 4, 33);  //   2
  cout << "\nAvstanden mellom  3 og 12: " << avstand( 3, 12);  //   2
  cout << "\nAvstanden mellom  3 og 28: " << avstand( 3, 28);  //   4
  cout << "\nAvstanden mellom 23 og 49: " << avstand(23, 49);  //   4
  cout << "\nAvstanden mellom  3 og 40: " << avstand( 3, 40);  //   5
  cout << "\nAvstanden mellom 23 og 28: " << avstand(23, 28);  //   1
  cout << "\nAvstanden mellom 22 og 33: " << avstand(22, 33);  //   1
  cout << "\nAvstanden mellom 28 og 28: " << avstand(28, 28);  //   0
  cout << "\nAvstanden mellom  3 og 50: " << avstand( 3, 50);  //  -1
  cout << "\nAvstanden mellom  3 og 32: " << avstand( 3, 32);  //  -1
  cout << "\nAvstanden mellom  7 og 31: " << avstand( 7, 31);  //  -1
  cout << "\n\n";
  return 0;
}
