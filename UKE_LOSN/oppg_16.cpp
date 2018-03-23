//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_16.CPP

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


//   L�sningsforslag til oppgave nr.16  i  Algoritmiske metoder.


#include <iostream>          //  cout
#include <cctype>            //  toupper
#include <cstdlib>           //  rand  (brukt i oppgave C)
#include <conio.h>           //  getch
#include "balTree.h"         //  Verkt�yklasse for � h�ndtere innsetting
			                 //    og displaying av BALANSERTE bin�re tr�r.
using namespace std;


char lesKommando()  {                 //  Leser og returnerer ETT tegn.
   gotoxy(1,22);
   cout << "Kommando (I(nsert), Q(uit)):  ";
   return toupper(getche());
}

itemType lesKey()  {
  cout << "\n\tTegn:\t";
  return toupper(getche());
}


void main()  {

//  OPPGAVE B:
  BalTree tree;
  char kommando;

  kommando = lesKommando();
  while (kommando != 'Q')  {
    if (kommando == 'I')
       tree.insert(lesKey(), "Node med INFO");

//    clrscr();
    tree.display(1, 80);
    kommando = lesKommando();
  }


//  OPPGAVE C:
//  clrscr();
  BalTree bigtree;
  for (int i = 1;  i <= 1000; i++)
      bigtree.insert(char((rand() % 26) + 65), "INFO");  //  ASCII-tegn: 65-90.
  bigtree.status();           //  Se property 15.3 og 15.4 s.228 i l�reboka.
  getch();
}
