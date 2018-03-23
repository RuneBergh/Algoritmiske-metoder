
//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S16_3.CPP

//  Løsningforslag til kontinuasjonseksamen i Alg.met, august 2016, oppgave nr.3.
//  Laget av Frode Haug, NTNU


#include <iostream>
using namespace std;

struct Node  {
  int   ID;	        //  Nodens ID/key/nøkkel/navn (et tall).
  Node* left;	    //  Peker til venstre subtre, evt. 'nullptr' når tomt.
  Node* right;	    //  Peker til høyre subtre, evt. 'nullptr' når tomt.
                    //  Constructor:
  Node (int id, Node* l, Node* r)  { ID = id;  left = l, right = r; }
};

Node* rot = nullptr;	        // Rot-peker.
const int MIN = 0, MAX = 9999;  //  Verdier mindre/større enn ALLE i treet.



//  OPPGAVE 3A1 - Finner MINSTE verdi i et binært (IKKE nødvendigvis SØKE)tre:
int finnMin(Node* n)  {
	if (n == nullptr)  return MAX;  //  Treet er tomt - returnerer 'høy' verdi.
	int min = n->ID,                //  Initierer til nodens egen ID.
		lmin = finnMin(n->left),    //  Finner venstre og høyre subtrærs
		rmin = finnMin(n->right);   //    minste verdier.
	if (lmin < min)  min = lmin;    //  Bestemmer den minste av de tre:
	if (rmin < min)  min = rmin;
	return min;                     //  Retunerer denne minste.
}


//  OPPGAVE 3A2 - Finner STØRSTE verdi i et binært (IKKE nødvendigvis SØKE)tre:
int finnMax(Node* n)  {
	if (n == nullptr)  return MIN;  //  Treet er tomt - returnerer 'lav' verdi.
	int max = n->ID,                //  Initierer til nodens egen ID.
		lmax = finnMax(n->left),    //  Finner venstre og høyre subtrærs
		rmax = finnMax(n->right);   //    største verdier.
	if (lmax > max)  max = lmax;    //  Bestemmer den største av de tre:
	if (rmax > max)  max = rmax;
	return max;                     //  Retunerer denne største.
}



//  OPPGAVE 3B - Finner ut om et binært tre er et binært SØKEtre (BST):
bool erBST(Node* n)  {
	if (n == nullptr)  return true;   //  Tomt - "er da pr.def" binært søketre.
	                                  //  Node til VENSTRE er større eller lik:
	if (n->left != nullptr  &&  finnMax(n->left) >= n->ID)  return false;
                        	          //  Node til HØYRE er mindre:
	if (n->right != nullptr  &&  finnMin(n->right) < n->ID)  return false ;
	                                  //  Minst ett av subtrærne er ikke BST: 
	if (!erBST(n->left) || !erBST(n->right)) return false ;
	return true;                      //  Alt OK - ER et BST.
}



int main()  {
//
//          Bygger treet:
//                       17
//                  /          \                  //
//                 33           11           
//               /    \       /    \              //
//              7      35   82      5
//            /   \           \    /              //
//           27     13        31  34
//                   \        /                   //
//                   10      57
//                          /  \                  //
//                         3   30

   Node *n3  = new Node( 3, nullptr, nullptr),
		*n30 = new Node(30, nullptr, nullptr),
		*n10 = new Node(10, nullptr, nullptr),
		*n57 = new Node(57, n3, n30),
		*n27 = new Node(27, nullptr, nullptr),
		*n13 = new Node(13, nullptr, n10),
		*n31 = new Node(31, n57, nullptr),
		*n34 = new Node(34, nullptr, nullptr),
		*n7  = new Node( 7, n27, n13),
		*n35 = new Node(35, nullptr, nullptr),
		*n82 = new Node(82, nullptr, n31),
		*n5  = new Node( 5, n34, nullptr),
		*n33 = new Node(33, n7,  n35),
		*n11 = new Node(11, n82, n5),
		*n17 = new Node(17, n33, n11);
   rot = n17;

   cout << "Minste  verdi i treet er:  " << finnMin(rot) << '\n';
   cout << "Største verdi i treet er:  " << finnMax(rot) << '\n';

   cout << "Treet er " << (erBST(rot)? "": "IKKE ") << "et binært SØKEtre\n";

   cout << "\n\n";
   return 0;
}
