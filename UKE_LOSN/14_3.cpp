//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ 14_3.CPP

//   L›sningsforslag til oppgave nr. 3
//   i kap.14 s.213 i l‘reboka "Algorithms in C++".


//  Programmet leser 5000 usorterte tall fra fila OPPG_14.DTA. Disse
//  sorteres vha. quicksort (dvs. kode fra OPPG_14.CPP er gjenbrukt.)
//  En rekursiv og omskrevet versjon av koden s.198 i l‘reboka er brukt
//  for † s›ke etter et tall som brukeren angir.

                             //  INCLUDE:
#include <iostream>
#include <fstream>

using namespace std;


typedef int itemType;
const int MAX = 5000;        //  Tallene legges i indeks 1-5000.
itemType tall[MAX+1];
int indeks = 0;              //  Indeksen for det s›kte tallet.

			                 //  Leser tall fra fil inn i 'a':
void lesFraFil(int a[], int n)  {
  ifstream innfil("OPPG_14.DTA");
  for (int i = 1;  i <= n;  i++)
      innfil >> a[i];
  a[0] = -1;                 //  Setter 'sentinel key'.
}


void swap(itemType a[], int i, int j)  {    //  Jfr. s.95 i l‘reboka.
  itemType    t = a[i];
	       a[i] = a[j];
	       a[j] = t;
}

void quicksort(itemType a[], int l, int r)  {   //  Jfr. s.118 i l‘reboka.
  int i, j;   itemType v;
  if (r > l)  {
     v = a[r];
     i = l-1;  j = r;
     for ( ; ; )  {
	    while (a[++i] < v)  ;
	    while (a[--j] > v)  ;
	    if (i >= j)  break;
	    swap(a, i, j);
     }
     swap(a, i, r);
     quicksort(a, l, i-1);
     quicksort(a, i+1, r);
  }
}

			     //  S.198 i l‘reboka, STERKT omskrevet.
void search(itemType a[], int l, int r, itemType ta)  {
  if (r >= l)  {             //  Noe fortsatt † lete p†:
     int m = (l+r)/2;        //  Finner midten av s›keomr†det.
     if (a[m] == ta)         //  Ligger den s›kte p† midten ?
	    indeks = m;          //  Is†fall: oppdater hvor funnet
     else                    //  Enn† ikke funnet den s›kte.
	if (ta < a[m])  search(a, l, m-1, ta);    //  I venstre halvdel ?
	          else  search(a, m+1, r, ta);    //  I h›yre halvdel ?
  }
}


int main()  {
  itemType tallet;

  cout << "\n\nLeser 'OPPG_14.DTA' og sorterer vha. Quicksort.\n";
  lesFraFil(tall, MAX);
  quicksort(tall, 1, MAX);

  cout << "\nS›ke etter tallet:  ";   cin >> tallet;

  search(tall, 1, MAX, tallet);

  if (indeks != 0)
     cout << "\n\nTallet har indeks nr." << indeks << "\n\n";
  else
     cout << "\n\nTallet er ikke † finne.\n\n";
  return 0;
}
