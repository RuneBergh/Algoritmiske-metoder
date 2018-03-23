//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_05.CPP

//   L›sningsforslag til oppgave nr.5  i  Algoritmiske metoder.


#include <iostream>                    //  cout
#include <cstdlib>                     //  (s)rand

using namespace std;


struct Node                            //  A node in the tree.
  {  int info;  Node* l, * r;  };

typedef Node* itemType;

itemType z;

int number;            //  Global variable, to get
				       //    sequenced numbers.


				       //  Recursive function that generates
				       //    (if possible) a node and may be
				       //    its left and right subtree.
				       //    Only called by 'generate'.
itemType generate2(int depth, int probability)  {
  itemType root = z;   //  Returning pointer.
					   //    NOTE: Initiated to 'z' !!
  if (depth > 0)  {                      //  Still generate a new level:
     if ((rand() % 100) < probability)  {   //  Number in legal interval:
	root = new Node;                 //  Create a new node.
					                 //  Generate left subtree:
	root->l =  generate2(depth-1, probability);
					                 //  Own ID is ONE higher than the
	root->info = ++number;           //    last one generated/created.
					                 //  Generate right subtree:
	root->r = generate2(depth-1, probability);
     }
  }
  return root;                           //  Returns the result.
}

					 //  Function called by the user.
					 //  Initiates some values, and
					 //  then calls 'generate2'.
itemType generate(int depth, int probability)  {
  itemType root;                         //  Returning pointer.

  number = 0;                            //  Initiating startpoint for
	                      				 //    numbering of keys/info/ID.
  root = z = new Node;  z->l = z;  z->r = z;    //  Initiating 'z' and root.
					                     //  Gets the whole tree by calling
  root = generate2(depth, probability);  //    a recursive function.

  return root;                           //  Returns the result.
}


void visit(itemType t)  {                //  Displays content for ONE node.
  cout << t->info << ' ';
}


void traverse(itemType t)  {             //  Traverses the tree INORDER.
  if (t != z)  {                         //  See page 60 in the lecture book.
     traverse(t->l);
     visit(t);
     traverse(t->r);
  }
}


// ************************   MAIN PROGRAM:   *****************************

int main()  {
  itemType root;

  cout << "\n\n";
  srand(0);

  root = generate(6, 80);              //  Generates the whole tree.

  traverse(root);                      //  Traverses (and shows) the tree.
  cout << "\n\n";
  return 0;
}
