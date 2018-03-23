//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H10_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     21.desember 2010, oppgave nr.3.

//     Laget av Frode Haug, HiG, desember 2010.


#include <iostream>
#include <iomanip>
using namespace std;


struct Node  {
  int   ID;     //  Nodens ID/key/n›kkel/navn (et tall).
  Node* left;	//  Peker til venstre subtre, evt. z-noden om det er tomt.
  Node* right;  //  Peker til h›yre subtre, evt. z-noden om det er tomt.
  Node* parent;	//  Peker til oppover igjen til forelder/mor, evt. z om er rota.
  Node (int id, Node* l, Node* r, Node* p)  //  Constructor:
       { ID = id; left = l; right = r; parent = p; }
};

//  Globale variable:
Node* z   = new Node(0, NULL, NULL, NULL);	//  z-noden (ID = 0).
Node* rot = z;                        		//  Rot-peker.

enum Type { Pre, In, Post };

void traverse(Type ty, Node* n)  {    
  if (n != z)  {               //  Reell node i treet:
     if (ty == Pre)  cout << ' ' << n->ID;
     traverse(ty, n->left);    //  G†r til venstre subtre.
     if (ty == In)   cout << ' ' << n->ID;
     traverse(ty, n->right);   //  G†r til h›yre subtre.
     if (ty == Post) cout << ' ' << n->ID;
  }
}


//  OPPGAVE 3A   -  Returnerer neste noden i preorder rekkef›lgen ift.'n':
Node* nestePreorder(Node* n)  {   //  Forutsetter at 'n' IKKE peker til z.
                      //  'n' har venstre - denne er neste i preorder:
  if (n->left != z)  return n->left;        
                      //  'n' har KUN h›yre, denne er neste i preorder:
  else if (n->right != z)  return n->right;
  else  {             //  'n' er bladnode - har hverken venstre eller h›yre:
     Node* p = n->parent;       //  Starter hos mora/forelder.
                      //  S† lenge ikke bladd helt opp og forbi rota og
                      //    s† lenge kommer fra h›yre side eller at
                      //    mora/forelder IKKE har et h›yre barn/subtre: 
     while (p != z  &&  (n == p->right ||  p->right == z))  {
        n = p;  p = n->parent;  //  Bla ett hakk opp (til mora/forelder).
     }                //  Om stanset inni treet, med en reell h›yre node -
                      //    returneres denne h›yre noden, ellers z-noden.
     return ((p != z) ? p->right : z);
  }
}


//  OPPGAVE 3B   -  Returnerer forrige noden i preorder rekkef›lgen ift.'n':
Node* forrigePreorder(Node* n)  {   //  Forutsetter at 'n' IKKE peker til z.
                     //  'n' er rotnode, derfor ingen forrige/f›r:
 if (n->parent == z)  return z;
 Node* q = n->parent->left;   //  Starter ›verst i mor's venstre subtre.
                     //  Er selv dette venstre barnet ELLER mor har 
                     //    ingen venstre - forrige er da mora selv:
 if (n == q  ||  q == z) return n->parent;
                     //  Looper "evig" til har funnet forrige i preorder -
                     //     som ALLTID(!) er en bladnode: 
 while (true)        //  Prim‘rt blas det nedover mot h›yre:
   if (q->right != z) q = q->right;
                     //  Sekund‘rt blas det nedover mot venstre:
   else if (q->left != z) q = q->left;
   else return q;    //  Kommet ned til bladnode - og dette var den forrige!
}


//  OPPGAVE 3C   -  Returnerer neste noden i preorder rekkef›lgen ift.'n',
//                    men bruker IKKE parent-pekeren:
Node* nestePreorder2(Node* n)  {     //  Forutsetter at 'n' IKKE peker til z.
                      //  'n' har venstre - denne er neste i preorder:
   if (n->left != z)  return n->left;
                      //  'n' har KUN h›yre, denne er neste i preorder:
   else if (n->right != z)  return n->right;
   else  {            //  'n' er bladnode - har hverken venstre eller h›yre:
                      //  Neste preorder er n‘rmeste forfedre ovenfor som har
                      //    et h›yre barn/subtre, som ikke er bes›kt hittil.
      Node* q = rot,  //  Starter † lete etter 'n' igjen fra rota.
          * r = z;    //  'r' blir etterhvert neste i preorder rekkef›lge!
      while (true)  { //  Looper "evig" til har funnet neste i preorder: 
        if (n->ID < q->ID)  {         // 'n' er til venstre for 'q':
                                      // 'q' har h›yre, sett 'r' til denne -
           if (q->right != z) r = q->right; // KANSKJE er neste preorder denne.
           q = q->left;               // G† videre ned til venstre (etter 'n').
        } else if (q == n) return r;  // 'q' bladd seg frem til 'n' igjen,
                                      //    returnerer det 'r' er satt til.
        else q = q->right;            // G† videre ned til h›yre (etter 'n').
      } 
   }
}


int main()  {
  Node *n6, *n8, *n11, *n12, *n13, *n17, *n28, *n31, *n33, *n34, *n35, *n39;

                                    // Bygger treet:          17              //
                                    //                    /        \          //
  n8  = new Node(8,    z,   z, z);  //                   11         33        //
  n12 = new Node(12,   z,   z, z);  //                 /    \     /    \      //
  n31 = new Node(31,   z,   z, z);  //                6      13 28     35     //
  n34 = new Node(34,   z,   z, z);  //                 \    /    \     / \    //
  n39 = new Node(39,   z,   z, z);  //                  8  12     31  34 39   //
  n6  = new Node(6,    z,  n8, z);  n8->parent  = n6;
  n13 = new Node(13, n12,   z, z);  n12->parent = n13;
  n28 = new Node(28,   z, n31, z);  n31->parent = n28;
  n35 = new Node(35, n34, n39, z);  n34->parent = n35;    n39->parent = n35;
  n11 = new Node(11, n6,  n13, z);  n6->parent  = n11;    n13->parent = n11;
  n33 = new Node(33, n28, n35, z);  n28->parent = n33;    n35->parent = n33;
  n17 = new Node(17, n11, n33, z);  n11->parent = n17;    n33->parent = n17;
  rot = n17;

  traverse(Pre,  rot);   cout << '\n';
  traverse(In,   rot);   cout << '\n';
  traverse(Post, rot);   cout << '\n';

  cout << "\n\nNESTE PREORDER ift (MED bruk av 'parent'):\n";
  cout << "\t17: " << setw(4) << nestePreorder(n17)->ID << '\n'; // 11
  cout << "\t11: " << setw(4) << nestePreorder(n11)->ID << '\n'; //  6
  cout << "\t 6: " << setw(4) << nestePreorder(n6)->ID  << '\n'; //  8
  cout << "\t13: " << setw(4) << nestePreorder(n13)->ID << '\n'; // 12
  cout << "\t 8: " << setw(4) << nestePreorder(n8)->ID  << '\n'; // 13
  cout << "\t12: " << setw(4) << nestePreorder(n12)->ID << '\n'; // 33
  cout << "\t31: " << setw(4) << nestePreorder(n31)->ID << '\n'; // 35
  cout << "\t34: " << setw(4) << nestePreorder(n34)->ID << '\n'; // 39
  cout << "\t39: " << setw(4) << nestePreorder(n39)->ID << '\n'; //  0(z)
  
  cout << "\n\nFORRRIGE PREORDER ift (MED bruk av 'parent'):\n";
  cout << "\t17:" << setw(4) << forrigePreorder(n17)->ID << '\n'; // 0(z)
  cout << "\t11:" << setw(4) << forrigePreorder(n11)->ID << '\n'; // 17
  cout << "\t 6:" << setw(4) << forrigePreorder(n6)->ID  << '\n'; // 11
  cout << "\t13:" << setw(4) << forrigePreorder(n13)->ID << '\n'; //  8
  cout << "\t 8:" << setw(4) << forrigePreorder(n8)->ID  << '\n'; //  6
  cout << "\t12:" << setw(4) << forrigePreorder(n12)->ID << '\n'; // 13
  cout << "\t31:" << setw(4) << forrigePreorder(n31)->ID << '\n'; // 28
  cout << "\t34:" << setw(4) << forrigePreorder(n34)->ID << '\n'; // 35
  cout << "\t39:" << setw(4) << forrigePreorder(n39)->ID << '\n'; // 34
  cout << "\t33:" << setw(4) << forrigePreorder(n33)->ID << '\n'; // 12
  cout << "\t35:" << setw(4) << forrigePreorder(n35)->ID << '\n'; // 31

  cout << "\n\nNESTE PREORDER ift (UTEN bruk av 'parent'):\n";
  cout << "\t17: " << setw(4) << nestePreorder2(n17)->ID << '\n'; // 11
  cout << "\t11: " << setw(4) << nestePreorder2(n11)->ID << '\n'; //  6
  cout << "\t 6: " << setw(4) << nestePreorder2(n6)->ID  << '\n'; //  8
  cout << "\t13: " << setw(4) << nestePreorder2(n13)->ID << '\n'; // 12
  cout << "\t 8: " << setw(4) << nestePreorder2(n8)->ID  << '\n'; // 13
  cout << "\t12: " << setw(4) << nestePreorder2(n12)->ID << '\n'; // 33
  cout << "\t31: " << setw(4) << nestePreorder2(n31)->ID << '\n'; // 35
  cout << "\t34: " << setw(4) << nestePreorder2(n34)->ID << '\n'; // 39
  cout << "\t39: " << setw(4) << nestePreorder2(n39)->ID << '\n'; //  0(z)
  cout << "\n\n";
  return 0;
}
