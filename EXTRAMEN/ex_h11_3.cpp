//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H11_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     20.desember 2011, oppgave nr.3.

//     Laget av Frode Haug, HiG, desember 2011.


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
Node* z   = new Node(0, NULL, NULL);      //  z-noden (ID = 0).
Node* rot = z;                            //  Rot-peker.



//  OPPGAVE 3A   -  Skriver stien fra 'rot' til bladnode lengst til h›yre:
void hoyreGren()  {
  Node* p = rot;                          //  Starter i rota.
  while (p != z)  {                       //  S† lenge ikke n†dd helt ned:
    cout << p->ID << ' ';                 //  Skriver nodes ID.
    p = (p->right != z) ?  p->right : p->left; //  G†r prim‘rt til h›yre,
  }                                            //    subsidi‘rt til venstre.
}


//  OPPGAVE 3B   -  Skriver stien fra rot til bladnoden 'p':
void gren(Node* p)  {
  int  id = p->ID;                        //  Gjemmer unna s›kt bladnodes ID.
  p = rot;                                //  Starter i rota.
  while (p != z)  {                       //  S† lenge ikke n†dd helt ned:
    cout << p->ID << ' ';                 //  Skriver nodes ID.
    p = (id < p->ID) ?  p->left : p->right; //  G†r til venstre eller h›yre.  
  }                                         //    Blar videre fra duplikate!
}


//  OPPGAVE 3C   - Skriver stiene fra rot og ned til ALLE bladnoder:
void grener(Node* p)  {
  if (p != z)  {           //  Reell/intern node:
                           //  Blad-/terminalnode - skriver stien ned til den:
     if (p->left == z  &&  p->right == z)  {  gren(p);  cout << '\n';  }
     grener(p->left);      //  Bes›ker venstre subtre.
     grener(p->right);     //  Bes›ker h›yre subtre.
  }
}



int main()  {
  Node  *n6,  *n8, *n11a, *n11b, *n12, *n13a, *n13b,
        *n17, *n28, *n31, *n33, *n34, *n35a, *n35b, *n39;

  n8   = new Node( 8,    z,   z);  // Bygger treet:          17              //
  n11b = new Node(11,    z,   z);  //                    /        \          //
  n13b = new Node(13,    z,   z);  //                   11         33        //
  n31  = new Node(31,    z,   z);  //                 /    \     /    \      //
  n34  = new Node(34,    z,   z);  //                6      13 28     35     //
  n35b = new Node(35,    z,   z);  //                 \    /  \ \     / \    //
  n12  = new Node(12, n11b,   z);  //                  8  12  13 31  34 39   //
  n39  = new Node(39, n35b,   z);  //                     /            /     //
  n6   = new Node( 6,    z,  n8);  //                    11           35     //
  n13a = new Node(13,  n12,  n13b);
  n28  = new Node(28,    z,  n31);
  n35a = new Node(35,  n34,  n39);
  n11a = new Node(11,   n6,  n13a);
  n33  = new Node(33,  n28,  n35a);
  n17  = new Node(17, n11a,  n33);
  rot  = n17;
                                 //  TESTER OPPGAVENS FUNKSJONER:
  hoyreGren(); cout << "\n\n";   //  Utskrift:  17 33 35 39 35

  gren(n31);   cout << '\n';     //  Utskrift:  17 33 28 31
  gren(n8);    cout << '\n';     //  Utskrift:  17 11 6 8
  gren(n35b);  cout << '\n';     //  Utskrift:  17 33 35 39 35
  gren(n13b);  cout << '\n';     //  Utskrift:  17 11 13 13
  gren(n11b);  cout << '\n';     //  Utskrift:  17 11 13 12 11
  gren(n34);   cout << "\n\n";   //  Utskrift:  17 33 35 34

  grener(rot);    //  Samme utskrift som seks forrige linjer,
                  //     bare litt annen rekkef›lge.
  cout << "\n\n";
  return 0;
}

