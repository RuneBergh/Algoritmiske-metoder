//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H14_4.CPP

//     Løsningsforslag til eksamen i "Algoritmiske metoder",
//     15.desember 2014, oppgave nr.4.

//     Kode hentet fra:  http://rosettacode.org/wiki/Perfect_numbers
//     Litt omskrevet av Frode Haug, HiG, desember 2014.



#include <iostream>
using namespace std;

 
const int SLUTT = 33550336;         //  Det 5.perfekte tallet.


                        
bool erPerfekt(int n) {             //  Finner ut om 'n' er et perfekt tall:
   int sum = 0, slutt = n/2;        //  Initierer 2x variable.
   for (int i = 1;  i <= slutt;  i++) { //  Går gjennom aktuelle kandidater:
       if (n % i == 0) sum += i;    //  Heltallig delelig: oppsummerer.
       if (sum > n) return false;   //  Har passert forbi 'n' i summeringen.
   }
   return (sum == n);               //  Er tallet perfekt (totalsum ER tallet)?
}



int main( ) { 
   cout << "De fem første perfekte tallene:\n";
   for (int tall = 1;  tall <= SLUTT;  tall++)   //  Går gjennom aktuelle tall:
      if (erPerfekt(tall)) cout << tall << '\n'; //  Perfekt! - Skriver tallet.

// Når man VET at slike perfekte tall ALLTID slutter på 6 eller 28,
// så kan den siste if-setningen effektiviseres adskillig vha:
//   if ((tall % 10 == 6  ||  tall % 100 == 28)  &&  erPerfekt(tall)) 
//      cout << tall << '\n';

   return 0; 
}
