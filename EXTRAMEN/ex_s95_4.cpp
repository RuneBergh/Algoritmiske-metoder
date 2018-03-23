//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S95_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     august 1995, oppgave 4.

//     Laget av Frode Haug, HIG, sommeren 1995.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


/*  OPPGAVE A:                  7
			    /       \
			  4           10
		       /     \      /    \
		     2        5    8      13
		    / \        \    \    /  \
		   1   3        6    9  12  14
				       /
				      11



    OPPGAVE B:  42  1 1
		23  1 1
		 9  1 0
		 2  0 0
		32  1 1
		25  0 0
		40  0 0
		69  0 1
		75  1 0
		71  0 0



    OPPGAVE C:   */

#include <fstream>           //  ifstream
#include <iostream>          //  cout
#include <cstdlib>           //  exit
using namespace std;


struct node  {               //  Noden:
  int number;                //  Nodens navn/identifikasjon.
  node* left, * right;       //  Pekere til subtr‘rne.
};

node* root;                  //  Peker til hele treet.
ifstream innfil("EX_S95_4.DTA");


void feil()  {  cout << "\nFeil i dataene om nodene p† filen.";  exit(0);  }


node* lagtre()  {
  int tall,                  //  Nodens navn/ID.
      l, r;                  //  Har venstre/h›yre subtre. Brukes boolsk.
  node* p;                   //  Pekeren til aktuell ny node.

  innfil >> tall;            //  Pr›ver † lese 1.tall om noden.
  if (innfil.eof()) feil();  //  Data finnes ikke, og det SKAL det !

  p = new node;              //  Oppretter ny node.
  p->number = tall;          //  Initierer nodens navn/ID.
  innfil >> l;               //  Har den venstre subtre ?
  innfil >> r;               //  Har den h›yre subtre ?
  p->left  = l  ?  lagtre()  :  NULL;  //  Is†fall p†hektes disse
  p->right = r  ?  lagtre()  :  NULL;  //    to subtr‘rne.
  return p;                  //  Returnerer peker til noden selv.
}



int main()  {
  root = lagtre();
  return 0;
}

