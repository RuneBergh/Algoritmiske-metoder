//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H07_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     4.desember 2007, oppgave nr.3.

//     Laget av Frode Haug, HiG, november 2007.



//  OPPGAVE 3A:
//      De 11 nodene p† niv† nr.6 vil ha verdiene (fra venstre mot h›yre):
//        111111  21111  2211  222  3111  321  33  411  42  51  6 



//  OPPGAVE 3B:
//      - Venste node inneholder alltid ETT 1-tall (bakerst) mer en mor-noden.
//      - H›yre node er EN h›yere enn mor-noden, men finnes/eksisterer BARE
//           om mor-noden IKKE har ender med to like sifre i sin ID/nummer.
//
//    ( I tillegg vil nodenes verdier ha f›lgende egenskaper:
//      - Summen av alle sifrene (tverrsummen) i EN nodes ID er nodens niv†.
//      - Sifrene i de ulike nodenes IDer p† et visst niv† utgj›r til sammen
//        ALLE mulige m†ter † skrive nodenes niv† vha. deres tverrsummer. )



#include <iostream>
using namespace std;

const int MAX_NIVA = 6;


struct Node  {
   int   ID;    //  Nodens ID/key/n›kkel/navn (et tall).
   Node* left;	//  Peker til venstre subtre, evt. z-noden om det er tomt.
   Node* right; //  Peker til h›yre subtre, evt. z-noden om det er tomt.
   Node (int id, Node* l, Node* r)  {  ID = id ;  left = l;  right = r;  }
};


Node* z   = new Node(0, NULL, NULL);  //  Globale variable:   z-noden og
Node* rot = new Node(1, z, z);        //                      rot-peker



//  OPPGAVE 3C:

void bygg_tre(int lev, Node* p)  {  //  Bygger aktuelt tre:

  if (lev < MAX_NIVA) {             //  Ikke n†dd max. niv† for treet:
                                    //  Venstre node m/ETT 1-tall til
     p->left = new Node((p->ID*10)+1, z, z);  //  (bakerst) i sin ID:
     bygg_tre(lev+1, p->left);      //  Bygger resten av venstre subtre.
                                    //  H›yre node OM egen ID IKKE ender
     if (p->ID % 10  !=  (p->ID / 10) % 10)  {  //  p† to like sifre:
        p->right = new Node(p->ID+1, z, z);  // H›yre node EN mer enn egen ID.
        bygg_tre(lev+1, p->right);  //  Bygger resten av h›yre subtre.
     }
  }
}


//  EXTRA:
void display(Node* p)  {
  if (p != z)  {
     cout << "\tID: " << p->ID << "   (" << p->left->ID
                               << ", "   << p->right->ID << ")\n";
     display(p->left);
     display(p->right);
  }
}


int main()  {
  bygg_tre(1, rot);

  display(rot);
  return 0;
}
