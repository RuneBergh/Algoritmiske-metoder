//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_J97_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder (I)",
//     24.februar 1997, oppgave 4.

//     Laget av Frode Haug, HIG,  februar 1997.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>
using namespace std;


const int ANT_ELEM = 10;

struct element  {
  int id;
  element* forrige, * neste;
};

element* toveisliste, * rot, * z;


void lag_liste();
void skriv_liste();
void traverser_preorder(element* elem);
element* lag_binaert_tre(element* liste);


int main()  {
  z = new element;  z->forrige = z->neste = z;
  lag_liste();
  cout << "\n\nListen:      ";   skriv_liste();

  rot = lag_binaert_tre(toveisliste);
  cout << "\n\n\nResultat-treet traversert preorder:\n\t";
  traverser_preorder(rot);
  cout << "\n\n";
  return 0;
}

void lag_liste()  {
  element* temp;
  toveisliste = z;
  for (int i = ANT_ELEM; i >= 1;  i--)  {
     temp = new element;   temp->id = i;   temp->forrige = temp->neste = z;
     if (toveisliste != z)  {
	temp->neste = toveisliste;
	toveisliste->forrige = temp;
     }
     toveisliste = temp;
  }
}


void skriv_liste() {
  element* pek = toveisliste;
  while (pek != z)  {
     cout << pek->id << "  ";
     pek = pek->neste;
  }
}

void traverser_preorder(element* elem)  {        //  Jfr. s.62 i l‘reboka.
  if (elem != z)  {
     cout << elem->id << "  ";
     cout << "L:"; traverser_preorder(elem->forrige);
     cout << "R:"; traverser_preorder(elem->neste);
  }
}

element* lag_binaert_tre(element* liste)  {
  element* v_liste, * h_liste;
  if (liste->neste != z)  {
     v_liste = liste;                       //  Finner midten av lista,
     h_liste = liste->neste->neste->neste;  //    og dermed deles i to.
     while (h_liste != z)                   //    Jfr. s.168 i l‘reboka.
	{ liste = liste->neste;  h_liste = h_liste->neste->neste;  }
     h_liste = liste->neste;   liste->neste = z;
					    //  Hekter ut midt-elementet
					    //    (det f›rste i h›yre liste)
					    //    og lar dette bli roten i
					    //    (sub)treet:
     liste = h_liste;  h_liste = h_liste->neste;  h_liste->forrige = z;
     liste->forrige = lag_binaert_tre(v_liste); //  Dets venstre og h›yre barn
     liste->neste   = lag_binaert_tre(h_liste); //    blir funnet ved rekursjon.
  }
  return liste;                        //  Returnerer rota (eller enkelt-node).
}

/*
  Liste med:  1  ->  2  ->  3  ->  4  ->  5  ->  z
  Gir treet:           3
		    /     \
		  2         5
		/         /
	      1         4


  Liste med:  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> z
  Gir treet:              6
		      /       \
		   3             9
		 /   \         /   \
		2     5       8     10
	       /     /       /
	      1     4       7
*/
