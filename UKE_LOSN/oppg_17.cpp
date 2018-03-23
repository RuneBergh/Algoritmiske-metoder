//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_17.CPP

//       L›sningsforslag til oppgave nr.17  i  Algoritmiske metoder.


				       //  INCLUDE:
#include <fstream>                     //    ifstream, ofstream
#include <iostream>                    //    cout

using namespace std;


const char itemMIN   = char(0);        //  CONST:
typedef char itemType;                 //  TYPEDEF:

				               //  GLOBALE VARIABLE:
struct Node *head, *z;                 //    Pekere til hode i 1.tre og 'z'.
itemType tegn;                         //    Aktuelt tegn i 1.tre (brukes
				                       //      av 'Visit' og 'Traverse').
ifstream innfil("OPPG_17.DTA");        //    Filene det leses fra og
ofstream utfil("OPPG_17.RES");         //      skrives til.


union TreAnt {                 //  UNION:
  int ant;                             //    Antall to-bokstavs-forekomster
  Node* tre;                           //    ELLER peker til hodet i 2.treet.
}; 


struct Node  {                 //  STRUCT:
  itemType key;                        //    Nodens ID/key/info/data.
  Node *l, *r;                         //    Nodens subtr‘r.
  union TreAnt tA;                     //    Peker til 2.tre ELLER antall.
				                       //    Constuctor:
  Node(itemType k,  Node* ll,  Node* rr,  int lev)  {
    key = k;   l = ll;  r = rr;        //    Initierer variable.
    if (lev == 1)  tA.tre = new Node(itemMIN, 0, z, 2);  //  Nytt 2.tre.
    else           tA.ant = 0;         //    Initierer antall kombinasjoner.
  }
};
				       //  FUNKSJONER:
				       //    Noe endret utgave av koden s.206 i l‘reboka. 
                       //    Leter etter noden 'v' i et tre p† 1. eller
				       //    2.niv†. Om den ikke finnes, s† legges den inn. 
                       //    Returnerer med peker til den fundne/ny-innlagte.
Node*  insert(Node* h, itemType v, int lev)  {
   Node *p, *x;
   p = h;  x = h->r;
   while (x != z  &&  v != x->key)     //    Leter etter noden:
     {  p = x;  x = (v < x->key)  ?  x->l  :  x->r;  }

   if (x == z) {                       //    Noden finnes ikke, lager ny:
      x = new Node(v, z, z, lev);      //    Oppretter ny node med 'z'-barn.
      if (v < p->key)  p->l = x;       //    Hekter inn under "mora":
      else             p->r = x;
   }
   if (lev == 2)  x->tA.ant++;         //    2.tre: ker antallet med '1'.
   return x;                           //    Returnere funnet/ny node.
}


void traverse(Node*, int);             //    Deklarasjon, da funksjonene
				                       //      nedenfor kaller hverandre.

void visit(Node* t, int lev)  {        //    Behandler noe i 1. eller 2.tre:
  if (lev == 1)                        //    Node i 1.tre:
     traverse(t->tA.tre->r, lev+1);    //      Traverserer dens 2.tre.
  else                                 //    Node i 2.tre:
				                       //      Skriver to bokstaver og antall.
     utfil << '\n' << tegn << t->key << ":  " << t->tA.ant;
}
				                       //    Traverserer et treet under 't'.
void traverse(Node* t, int lev) {
  if (t != z)  {                       //    Treet er IKKE tomt:
     traverse(t->l, lev);              //    Tar venstre subtre.
     if (lev == 1)  tegn = t->key;     //    Global variabel sette til
				                       //      1.treets bokstav, f›r
     visit(t, lev);                    //      2.treet bes›kes/traverseres.
     traverse(t->r, lev);              //    Tar h›yre subtre.
  }
}


int main()  {                   // HOVEDPROGRAM:
  char bokst[3];                       //   To bokstaver fra filen.
  Node* tre2;                   //   Hjelpepeker til aktuelt 2.tre.
				                       //   Initierer 1.treet:
  z = new Node( 0, 0, 0, 2);   head = new Node(itemMIN, 0, z, 2);

  cout << "Leser fra filen 'OPPG_17.DTA'.....";
  innfil >> bokst;
  while (innfil)  {
    tre2 = insert(head,          bokst[0], 1);   //  Legger inn i 1.treet.
	   insert(tre2->tA.tre, bokst[1], 2);        //  Legger inn i aktuell
		                    				     //    nodes 2.tre.
    innfil >> bokst;
  }

 cout << "\n\nSkriver til filen 'OPPG_17.RES'.....";
 traverse(head->r, 1);                            //  Skriver dataene til fil.
 cout << "\n\n";
 return 0;
}
