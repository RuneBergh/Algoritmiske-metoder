//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_02.CPP

//  Eksemplene viser forholdsvis enkel bruk av rekursjon.
//  Koden er hentet fra s.52 i l‘reboka.


#include <iostream>
using namespace std;


int factorial(int n)  {               //  Regner ut N!
  if (n == 0)  return 1;
  return  n * factorial(n-1);
}

//                           int ant = 0;
int fibonacci(int n)  {
//                           cout << "\n\t\tN: " << n << "  Ant: " << ++ant;
  if (n <= 1)  return 1;
  return fibonacci(n-1) + fibonacci(n-2);
}


int main()  {
  int n;
  char cc;
  
  cout << "Gi 'N' i 'N!':   ";     cin >> n;
  cout << "\n\t" << n << "! er:  " << factorial(n);

  cout << "\n\nFibonacci-tall nr:   ";     cin >> n;
  cout << "\n\tTallet er:  " << fibonacci(n) << '\n';
//                         float svar = 1.0;
//                         for (int i = 1;  i <= 10;  i++)  {
//                           svar *= 1.61803;
//                           cout << "\n\t\t\t" << svar;
//                         }
  return 0;
}
