//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H16_1a.CPP

//  Løsning til eksamen i Alg.met, desember 2016, oppgave nr.1a.
//  Laget av Frode Haug, NTNU


#include <iostream>
using namespace std;

void rekursiv(int n) {
	if (n < 1)  cout << '\n';
	else  {
		cout << ' ' << n % 5;
		rekursiv(n / 4);
	}
}

int main()  {
	rekursiv(100);   
	return 0;
}



//  Utskriften blir:   0 0 1 1
