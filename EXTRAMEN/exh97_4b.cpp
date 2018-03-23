//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EXH97_4B.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     18.desember 1997, oppgave 4B.

//     Laget av Frode Haug, HIG,  desember 1997.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



#include <iostream>          //  cout, cin
#include <cctype>            //  isdigit
using namespace std;


int beregn()  {
  char ch;                   //  Innlest tegn.
  int tall;                  //  Tallet funnet.

  cin >> ch;                 //  Leser neste tegn.
  if (isdigit(ch))  {        //  Dersom tall:
     tall = 0;               //     Bygger sammen fler-sifret tall:
     while (isdigit(ch))  {
       tall = tall*10 + (ch-'0');
       cin >> ch;            //  NB: Leser tilslutt tegnet ETTER tallet.
     }
  } else if (ch == '(')  {   //  Funnet starten p† nytt uttrykk:
    tall = beregn();         //    Bergner uttrykket. Returnerer n†r matchende
    cin >> ch;               //    ')' ER LEST. Leser neste tegn.
  }

//                 cout << "\n\t\t'(':   " << tall << "\tTegn: " << ch;
//                 char tegn;   cin >> tegn;
  if ( ch == ')'  ||  ch == '.' )  return tall;
			     //  Neste tegn avslutter (hele/del-) uttrykket.

		    //  Invariant:  Siste innleste tegn er ALLTID en operator !
//                     cout << "\nCh: " << ch;
  switch (ch)  {
    case '+':  return (tall + beregn());
    case '-':  return (tall - beregn());
    case '*':  return (tall * beregn());
    case '/':  return (tall / beregn());
    default:  cout << "\n\nFEIL: Denne meldingen burde ikke forekomme !!";
  }
}

			//  HOVEDPROGRAM:
int main()  {
  cout << "\n\nSkriv aritmetisk inorder uttrykk:  \n\t";
  cout << "\n\nSvaret blir:  " << beregn() << "\n\n";;
  return 0;
}

