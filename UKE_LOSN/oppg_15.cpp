//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_15.CPP

//  ***************************************************************
//  ***************************************************************
//  ***                                                         ***
//  ***                                                         ***
//  ***      NB:  VIRKER KUN NèR CONIO.H KAN BRUKES !!!!!!      ***
//  ***                                                         ***
//  ***                                                         ***
//  ***************************************************************
//  ***************************************************************

//   Programmet vil IKKE virke korrekt for 'ë', 'õ', 'Ü', 'í', 'ù' og 'è' da
//   disse IKKE har stigende ascii-numre, og "toupper" IKKE hÜndterer disse.


//   Lõsningsforslag til oppgave nr.15  i  Algoritmiske metoder.


#include <iostream>          //  cout
#include <cctype>            //  toupper
#include <conio.h>           //  getch
#include "binTree.h"         //  Verktõyklasse for Ü hÜndtere sõk,
			                 //    innsetting og fjerning fra binëre trër.
using namespace std;


char lesKommando()  {                 //  Leser og returnerer ETT tegn.
   gotoxy(1,22);
   cout << "Kommando (I(nsert), R(emove), S(earch), Q(uit)):  ";
   return toupper(getche());
}

itemType lesKey()  {
  cout << "\n\tTegn:\t";
  return toupper(getche());
}


void main()  {
  BinTree tree;
  char kommando;

  kommando = lesKommando();
  while (kommando != 'Q')  {
    switch (kommando)  {
      case 'I':  tree.insert(lesKey(), "Node med INFO");     break;
      case 'R':  tree.remove(lesKey());                      break;
      case 'S':  cout << "\n\tInfo:\t"
		      << tree.search(lesKey());   getch();   break;
    }
    tree.display(1, 80);
    kommando = lesKommando();
  }
}
