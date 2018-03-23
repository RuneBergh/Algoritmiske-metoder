//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S01_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     13.august 2001, oppgave 4.

//     Laget av Frode Haug, HiG, august 2001.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



//     Programmet er en LITEN omskriving av koden p† sidene 54-56 i l‘reboka,
//     der "mark"-funksjonen er erstattet med utskift vha. to for-l›kker.



#include <iostream>          //  cout 
using namespace std;

                             //  Etter "ant_bl" innledende blanke tegn,
                             //  skriv "n" stjerner ('*').
void skriv_monster(int n, int ant_bl) {   
  int i;                                 //  Løkkevariabel.
  if (n >= 1)  {                         //  Om fortsatt skal skrive stjerner:
     skriv_monster(n/2, ant_bl);         //  Skriv halvparten s† mange f›rst,
                                         //    startende i samme kolonne.
     for (i = 1;  i<= ant_bl;  i++)      //  Lag/skriv innledende blanke:
         cout << "  ";
     for (i = 1;  i<= n;  i++)           //  Lag/skriv rett antall stjerner:
         cout << "* ";
     cout << '\n';                       //  Skriv linjeskift.
     skriv_monster(n/2, ant_bl + n/2);   //  Skriv halvparten s† mange etterp†,
  }                                      //    startende rett etter eget
}                                        //    midtpunkt.



int main()   {               //  HOVEDPROGRAMMET:
  skriv_monster(8, 0);
  cout << '\n';
  return 0;
}
