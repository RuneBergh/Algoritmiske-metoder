//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_10.CPP

//  Eksemplet viser koden fra side 166 i l‘reboka (dvs. mergesort av array).


#include <iostream>
using namespace std;


const int LEN = 16;          //  Tekstens lengde, inkl.'\0'.
char tekst[LEN] = "ASORTINGEXAMPLE";   //  Streng som skal sorteres.
char b[LEN];

typedef char itemType;


void mergesort(itemType a[], int l, int r)  {   //  Jfr. s.166 i l‘reboka.
  int i, j, k, m;
			int p;
			char ch;
  if (r > l)  {
     m = (r+l)/2;
     mergesort(a, l, m);
     mergesort(a, m+1, r);
			cout << "\n\nF›r:\t";
			for (p = l;  p <= r;  p++)  cout << a[p] << ' ';
				                        //  Kopierer venstre del:
     for (i = m+1;  i > l;  i--)  b[i-1] = a[i-1];
				                        //  Kopierer h›yre del BAKLENGS! :
     for (j = m;    j < r;  j++)  b[r+m-j] = a[j+1];
			cout << "\nInni:\t";
			for (p = l;  p <= r;  p++)  cout << b[p] << ' ';
     for (k = l;    k <=r;  k++)        //  Merge sammen delene inn i 'a':
             a[k] =  (b[i] <= b[j]) ? b[i++] : b[j--];
			cout << "\nEtter:\t";
			for (p = l;  p <= r;  p++)  cout << a[p] << ' ';
			cin >> ch;
  }
}


int main()  {
  char ch;
  cout << "\n\nViser bruken av MERGESORT p† array";   cin >> ch;
  mergesort(tekst, 0, LEN-2);
  cout << "\n\nFerdig:  "  << tekst << "\n\n";
  return 0;
}
