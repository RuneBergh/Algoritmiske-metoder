//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S96_1.CPP

//     L›sningsforslag til kontinuasjonseksamen i 
//     "Algoritmiske metoder", oppgave nr.1, september 1996.

//     Laget av Frode Haug,  HIG,  september 1996.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>
using namespace std;

void rekursiv(int n)  {
	if (n < 10)  cout << n;
	else  {
		rekursiv(n / 10);
		cout << n % 10;
	}
}

int main()  {   
  rekursiv(123);
  return 0;
}


//  Utskriften blir:   "123"
