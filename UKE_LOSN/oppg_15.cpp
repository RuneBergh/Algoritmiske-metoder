//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_15.CPP

//  ***************************************************************
//  ***************************************************************
//  ***                                                         ***
//  ***                                                         ***
//  ***      NB:  VIRKER KUN N�R CONIO.H KAN BRUKES !!!!!!      ***
//  ***                                                         ***
//  ***                                                         ***
//  ***************************************************************
//  ***************************************************************

//   Programmet vil IKKE virke korrekt for '�', '�', '�', '�', '�' og '�' da
//   disse IKKE har stigende ascii-numre, og "toupper" IKKE h�ndterer disse.


//   L�sningsforslag til oppgave nr.15  i  Algoritmiske metoder.


#include <iostream>          //  cout
#include <cctype>            //  toupper
#include <conio.h>           //  getch
#include "binTree.h"         //  Verkt�yklasse for � h�ndtere s�k,
			                 //    innsetting og fjerning fra bin�re tr�r.
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
