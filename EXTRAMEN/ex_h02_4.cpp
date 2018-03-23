//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H02_4.CPP

//     L›sningsforslag til eksamen i 
//     "Algoritmiske metoder (I)", oppgave nr.4, 9.desember 2002.

//     Laget av Frode Haug, HiG, november 2002.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>     //  cout
#include <fstream>      //  ifstream, ofstream

using namespace std;

const int LEN = 120;

ifstream innfil("KODE.CPP");
ofstream utfil("KODE2.CPP");


char buffer[LEN];       //  Global buffer med siste innleste linje.


int pen_kode(int n)  {  //  Lag pen kode med 'n' innledende blanke p† linjen.
  int i;                                       //  L›kkevariabel.
  innfil.getline(buffer, LEN);                 //  Henter (om mulig) ny linje.

  while (innfil)  {                            //  Ikke n†dd filslutt:
    if (buffer[0] == '}') n -= 2;              //  Blokk ferdig, lest en linje
                                               //   "for mye", m† kompensere.
    for (i = 1; i <= n;  i++)  utfil << ' ';   //  'n' innledende blanke.
    utfil << buffer << '\n';                   //  Skriver linjen slik den er.

    if (buffer[0] == '}') return 0;            //  Blokken ferdig - returnerer.
    else if (buffer[0] == '{') pen_kode(n+2);  //  Ny blokk starter - 
                                               //     rekursivt kall.
    innfil.getline(buffer, LEN);               //  Henter (om mulig) ny linje.
  }
  return 0;
}
 
                       
int main()  {          //  HOVEDPROGRAM:
  if (innfil)  {
     pen_kode(0);
	 cout << "\nSkrevet fil/kode med innrykk til filen 'KODE2:DTA'.\n\n";
  }
  else
     cout << "\nFinner ikke filen 'KODE.CPP'!\n\n";
  return 0;
}
