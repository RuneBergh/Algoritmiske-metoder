//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_07.CPP

//   L›sningsforslag til oppgave nr.7  i  Algoritmiske metoder.

//   Programmet er "identisk" til EKS_06.CPP, bare at det i 'perm'
//   er lagt inn tre avskj‘ringer for † ikke skrive ut permutasjoner
//   der to fortl›pende tall st†r ved siden av hverandre.


#include <iostream>
#include <cmath>                       //  abs

using namespace std;


const int N = 8;                       //  Arrayens lengde.

int arr[N];                            //  Global array av int'er.


void display(int a[])  {               //  Viser arrayens innhold.
  char ch;
  cout << "\n";
  for (int i = 0;  i < N;  i ++)
    cout << a[i] << ' ';
  cout << "\t\tTrykk CTRL+C for † avslutte";
  cin >> ch;
}


void bytt(int & a1, int & a2)  {       //  Bytter om to array-elementer.
  int aa = a1;
      a1 = a2;
      a2 = aa;
}


void roterVenstre(int a[], int i)  {   //  Roterer elementer mot venstre.
  int x, k;
  x = a[i];                            //  Tar vare p† f›rste.
  for (k = i+1;  k < N;  k++)          //  Roterer:
    a[k-1] = a[k];
  a[N-1] = x;                          //  Legger f›rst inn bakerst.
}


void perm(int i)  {
  int t;                           //  N†dd en ny lovlig permutasjon:
  if (i == N-1  &&  abs(arr[i]-arr[i-1]) != 1)  
     display(arr);                 //  Skriver ut arrayens innhold.
  else {                           //  Skal permutere:
     if (i==0  ||  abs(arr[i]-arr[i-1]) != 1)     //  Kun "lovlige" naboer:
	    perm(i+1);                     //  Beholder n†v‘rende nr.'i'.
		   		                       //    Permuterer resten.
     for (t = i+1; t < N; t++)  {
	     bytt(arr[i], arr[t]);         //  Bytter nr.'i' etter tur med alle
				                       //    de andre etterf›lgende.
	     if (i==0  ||  abs(arr[i]-arr[i-1]) != 1)  //  Kun "lovlige" naboer:
	        perm(i+1);                 //  For hver av ombyttene: permuterer
     }                                 //    resten av de N etterf›lgende.
     roterVenstre(arr, i);             //  Gjenoppretter opprinnelig array.
  }
}


int main()  {
  for (int i = 0;  i < N;  i++)        //  Fyller array med: 1, 2, 3, ..., N
      arr[i] = i+1;

  perm(0);                             //  Lager/skriver permutasjon av ALLE
				                       //    sifrene/arrayelementene.
  display(arr);                        //  Skriver array etter at ferdig (for
  return 0;                            //   † se om orginal er gjenopprettet).
}
