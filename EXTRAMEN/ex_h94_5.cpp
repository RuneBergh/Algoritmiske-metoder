//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H94_5.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     desember 1994, oppgave 5.

//     Laget av Frode Haug, HIG, h›sten 1994.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



#include <iostream>                    //  cout
#include <iomanip>                     //  setw
using namespace std;

const int N = 16;                      //  Arrayens max.lengde (indeks 0-15).
int ant = 0;                           //  Antall l›sninger.
int arr[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };


				       //  Sjekker om 'a' tilfredstiller
bool rett_sum(int a[], int n)  {        //  kravene beskrevet i oppgaven.
  if (a[n-3] + a[n-2] + a[n-1] + a[n] != 34)  return false;
  if (n == N-1)  {
	for (int i = 0;  i < 4;  i++)
	    if (a[0+i] + a[4+i] + a[8+i] + a[12+i] != 34)  return false;
	if (a[0] + a[5] + a[10] + a[15] != 34)  return false;
	if (a[3] + a[6] + a[9] + a[12] != 34)   return false;
  }
  return true;
}


void display(int a[])  {               //  Viser arrayens innhold.
  ++ant;
  cout << "\nL›sning nr." << ant << ":";
  for (int i = 0;  i < N;  i++)  {
      if (i % 4 == 0)  cout << '\n';
      cout << setw(5) << a[i];
  }
  cout << '\n';
}


void bytt(int & a1, int & a2)  {       //  Bytter om to array-elementer.
  int aa = a1;    a1 = a2;      a2 = aa;
}


void roter_venstre(int a[], int i)  {  //  Roterer elementer mot venstre.
  int x, k;
  x = a[i];                            //  Tar vare p† f›rste.
  for (k = i+1;  k < N;  k++)          //  Roterer:
    a[k-1] = a[k];
  a[N-1] = x;                          //  Legger f›rst inn bakerst.
}


void perm(int i)  {
  int t;

  if (i == N-1  &&  rett_sum(arr, i))  //  N†dd en ny lovlig permutasjon:
     display(arr);                     //  Skriver ut arrayens innhold.
  else {                               //  Skal permutere:
				       //  Lovlige linjer: Beholder n†v‘rende
				       //    nr.'i'. Permuterer resten.
     if ((i+1) % 4 != 0  ||  rett_sum(arr, i))  perm(i+1);
     for (t = i+1; t < N; t++)  {
	   bytt(arr[i], arr[t]);       //  Bytter nr.'i' etter tur med alle
				       //    de andre etterf›lgende.
				       //  Lovlige linjer og for hvert av
				       //    ombyttene: permuter resten av
				       //    de N etterf›lgende:
	   if ((i+1) % 4 != 0  ||  rett_sum(arr, i))  perm(i+1);
     }
     roter_venstre(arr, i);            //  Gjenoppretter opprinnelig array.
  }
}


int main()  {
  perm(0);                             //  Finner l›sning p† oppgaven.
  return 0;
}
