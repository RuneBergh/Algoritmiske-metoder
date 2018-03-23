
//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H95_1.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     12.desember 1995, oppgave 1.

//     Laget av Frode Haug, HIG, h›sten 1995.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>
using namespace std;

int g(int n, int a, int b)  {
  if ( n == 0)
     return a;
  else
     return g(n-1, b, a+b);
}

int f(int n)  {    //     Funksjonen returnerer fibonacci-tall nr.'n-1'.
  return g(n, 0, 1);
}

int main()  {
  cout << "\n\n";
  for (int i = 0;  i <= 5; i++)
    cout << '\n' << f(i);
  return 0;
}
