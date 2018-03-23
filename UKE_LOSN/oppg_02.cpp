//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_02.CPP

//   L›sningsforslag til oppgave nr.2  i  Algoritmiske metoder.


#include <iostream>

using namespace std;


int factorial(int n)  {
  int fac = 1;

  for (int i = 1;  i <= n;  i++)
      fac *= i;
  return fac;
}



int main()  {
  int n;

  cout << "Gi 'N' i 'N!':  ";   cin >> n;
  cout << "\n\t" << n << "! er:  " << factorial(n) << "\n\n";
  return 0;
}
