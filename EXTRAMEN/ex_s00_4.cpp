//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S00_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     17.august 2000, oppgave 4.

//     Laget av Frode Haug, HiG, august 2000.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



#include <iostream>          //  cout 
using namespace std;


const int N = 10;            //  Antall perler i kjedet.

int kjede[N];                //  N†v‘rende perlekjede.
int antall;                  //  Totalt antall ulike perlekjeder.


void skriv_ut()  {           //  Skriver 'kjede's innhold som tekster:
  for (int i = 0;  i < N;  i++)      //  G†r gjennom hele 'kjede'.
// Fargene:    Ingen, Svart, Lilla, Blaa, Groenn, Roed, Orange, Gul, Hvit
//  tilsvarer:   0      1       2      3     4      5      6     7     8
    switch(kjede[i])  {              //  For hver "skuff":
      case 1:  cout << "Svart ";  break;
      case 2:  cout << "Lilla ";  break;
      case 3:  cout << "Blå ";    break;
      case 4:  cout << "Grønn ";  break;
      case 5:  cout << "Rød ";    break;
      case 6:  cout << "Orange "; break;
      case 7:  cout << "Gul ";    break;
      case 8:  cout << "Hvit ";   break;
      default: cout << "FEIL ";   break;
    }
  cout << '\n';  
//                      char ch;   cin >> ch;
  antall++;
}

                             //  Rekursiv (hoved)funksjon som setter inn alle
void lag_kjede(int i)  {     //    MULIGE farger i plass nr.'i' i kjedet.
  bool farge_ok;             //  Hjelpevaribel for † sjekke om farge er lovlig.
  if (i == N)                //  Kjedet er fullt:
     skriv_ut();             //  Skriver dets innhold/utseende.
  else  {
     for (int f = 1;  f <= 8;  f++)  {    //  Pr›ver alle kulerfarger:
         farge_ok = true;                          //  Antar at dette er OK.
                             //  1.perle trenger IKKE † sjekkes, da ALLE
                             //    farger kan v‘re der, sjekker derfor kun
         if (i > 0)  {       //    n†r to eller flere kuler:
                             //  Er krav 1 oppfylt:
                 if ((f == 4  &&  kjede[i-1] == 5)  ||
                     (f == 5  &&  kjede[i-1] == 4))  farge_ok = false;
                             //  Er krav 2 oppfylt:
            else if ((f == 3  &&  kjede[i-1] == 6)  ||
                     (f == 6  &&  kjede[i-1] == 3))  farge_ok = false;
                             //  Er krav 3 oppfylt:
            else if ((f == kjede[i-1])  ||
                     (i > 1  && f == kjede[i-2]))  farge_ok = false;
         }

         if (farge_ok)  {    //  Alt er fortsatt OK:
            kjede[i] = f;    //  Legger inn aktuell kule.
            lag_kjede(i+1);  //  Genererer den NESTE kulen
            kjede[i] = 0;    //  Nulltiller (overfl›dig kode/operasjon!)
            
         }
     }
  }
}


int main()   {               //  HOVEDPROGRAMMET:
  lag_kjede(0);              //  Genererer f.o.m den f›rste kula.
  cout << "\n\nAntall LOVLIGE perlekjeder med " << N << " kuler: " 
	   << antall << "\n\n";
  return 0;
}
