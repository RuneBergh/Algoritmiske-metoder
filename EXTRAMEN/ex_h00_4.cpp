//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H00_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     11.desember 2000, oppgave 4.

//     Laget av Frode Haug, HiG, desember 2000.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>          //  cout 
using namespace std;

const int N       =  4;      //  Max. antall steg.
const int MAAL    = 91;      //  Slutt-/m†lverdi.
const int INITIAL = 99;      //  Initiell-/startverdi. 
const int FLERE   = 53;      //  Mottar (om ›nskelig) FLERE stk. til.

                             //  Rekursiv funksjon som (om mulig) finner l›sning.
                             //  Input er antall n†v‘rende kroner, og hvor mange
                             //  steg ('n') som er igjen.
bool spill(int ant_kroner, int n)  {
  bool ferdig = false;       //  Hjelpevariabel for † sjekke om er ferdig.
                                            //  Har funnet en l›sning ! 
  if (ant_kroner == MAAL)  {  cout << MAAL;  return true; }
  else if (n == 0) return false;            //  Ikke flere steg igjen.
  else  {
    ferdig = spill(ant_kroner+FLERE, n-1);  //  Pr›ver med † motta flere.
    if (!ferdig  &&  !(ant_kroner % 2))     //  Ingen l›sning og partall stk:
      ferdig = spill(ant_kroner/2, n-1);    
    if (ferdig) cout << "  " << ant_kroner; //  L›sning funnet: skriver stk.
    return ferdig;                          //  Returnerer om l›sning eller ei.
 }
}


// *********************  ALTERNATIVT:  *****************************
/*
bool spill(int ant_kroner, int n)  {
  if (n < 0) return false;
  if (ant_kroner == MAAL  ||
      spill(ant_kroner+FLERE, n-1) ||
      (!(ant_kroner % 2) && spill(ant_kroner/2, n-1)))  {
        cout << ant_kroner << "  ";
        return true;
  }
  return false;
}
*/


int main()   {               //  HOVEDPROGRAMMET:
  cout << "For " << INITIAL << " kronerstykker p† max." << N
       << " steg, ble f›lgende l›sning funnet: \n\n\t";

  if (!spill(INITIAL, N))    //  Pr›ver † finne en l›sning.
     cout << "INGEN LSNING !";
  cout << "\n\n";
  return 0;
}
