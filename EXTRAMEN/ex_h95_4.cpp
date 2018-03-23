
//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H95_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     12.desember 1995, oppgave 4.

//     Laget av Frode Haug, HIG, h›sten 1995.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003

//     NB: Det er KUN funksjonen "los_labyrint"
//         som er svar p† eksamensoppgaven.

//  ***************************************************************
//  ***************************************************************
//  ***                                                         ***
//  ***                                                         ***
//  ***      NB:  KJØRER BEST/"KUN" UNDER BORLAND !!!!!         ***
//  ***                                                         ***
//  ***                                                         ***
//  ***************************************************************
//  ***************************************************************

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <fstream.h>   //  ifstream
#include <iostream.h>  //  cout
#include <string.h>    //  strcpy, strlen
#include <conio.h>     //  clrscr, getch, gotoxy, putch
#include <dos.h>       //  delay

const int BUF_LEN = 100;
const int MAX_BREDDE = 75;
const int MAX_HOYDE = 20;

enum retning  {  nord, sor, ost, vest, slutt  };

int  bredde, hoyde, s_x, s_y;
char labyrint[MAX_HOYDE][MAX_BREDDE];


void les_labyrint()  {
  ifstream innfil("EX_H95_4.DTA");
  char buffer[BUF_LEN];
  int ok = 1;
  hoyde = 0;

  innfil.getline(buffer, BUF_LEN);   bredde = strlen(buffer);
  while (!innfil.eof()  &&  ok  &&  strlen(buffer) >= 10  &&
	 strlen(buffer) <= MAX_BREDDE  &&  hoyde <= MAX_HOYDE)  {
     strcpy(labyrint[hoyde++], buffer);
     if (bredde != strlen(buffer)) ok = 0;
     innfil.getline(buffer, BUF_LEN);
  }
  if (strlen(buffer) > MAX_BREDDE)
     cout << "\n\nMax." << MAX_BREDDE << " tegn pr.linje.";
  if (hoyde > MAX_HOYDE)
     cout << "\n\nMax." << MAX_HOYDE << " linjer i filen.";
  if (!ok)
     cout << "\n\nLinjene er IKKE like lange.";
}


void tegn_labyrint()  {
  int i, j;
  clrscr();
  for (i = 0;  i < hoyde; i++)  {
    for (j = 0;  j < bredde; j++)  {
      cout << labyrint[i][j];
      if (labyrint[i][j] == 'S')
	 {  s_x = i;  s_y = j;  labyrint[i][j] = ' ';  }
    }
    cout << '\n';
  }
}


bool los_labyrint(int x, int y)  {
  retning retn;
  bool funn = false;

  switch (labyrint[x][y])  {
    case 'M':            funn = true;   break;
    case 'ù': case 'Û':  funn = false;  break;
    case ' ':
	labyrint[x][y] = 'ù';
	gotoxy(y+1, x+1);  putch('ù');  // delay(50);

	retn = nord;
        while (!funn  &&  retn != slutt)  {
	  switch(retn)  {
	    case nord:  funn = los_labyrint(x-1, y);  break;
	    case sor:   funn = los_labyrint(x+1, y);  break;
	    case ost:   funn = los_labyrint(x, y+1);  break;
	    case vest:  funn = los_labyrint(x, y-1);  break;
	  }
	  retn++;
	}
	if (!funn)  {
	   labyrint[x][y] = ' ';
	   gotoxy(y+1, x+1);  putch(' '); /* delay(50);*/   }   break;
  }
 return funn;
}


int main()  {
  les_labyrint();
  tegn_labyrint();
  if (!los_labyrint(s_x, s_y))
     cout << "\n\nIngen l›sning finnes.";
  cout << "\n\n";
  return 0;
}
