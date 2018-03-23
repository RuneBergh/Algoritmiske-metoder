//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_07.CPP

//  Eksemplet viser koden fra sidene 95 og 109 i læreboka.
//  NB:  Har lagt inn ' ' (blank) i element nr.0.
//  Fire små endringer gjør at kan utprøves for exercise 6 s.114 i læreboka.

#ifdef _MSC_VER					// For å slippe warnings/errors ifm. strcpy:
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>          //  strcpy

using namespace std;


const int LEN = 17;  // Ex.6 s.114:   14   //  Tekstens max.lengde, inkl.'\0'.
char tekst[LEN];             //  Streng med bokstavene som skal sorteres.

typedef char itemType;


void fyllArray()  {
  strcpy(tekst, " AEORTINGEXAMPLS");
// Ex.6 s.114:  strcpy(tekst, " EASYQUESTION");
}



void shellsort(itemType a[], int N)  {      //  Jfr. s.109 i læreboka.
  int i, j, h;   itemType v;

  for (h = 1;  h <= N/9;  h = 3*h + 1)   ;  //   16/9 = 1,  dvs: h = 4
					                        // Ex.6 s.114:   h = 7;
			     int nr = 0;
				 char ch;
  for (  ;  h > 0;  h /= 3)  {              // Ex.6 s.114:   /= 2

      for (i = h+1;  i < N;  i++)  {

	    v = a[i];  j = i;
			     cout << "\nF›r:\t\tH: " << h
				  << "\tI: " << i << "\tJ: " << j
				  << "\tJ-H: " << j-h
				  << "\t\ta[" << j-h << "]: " << a[j-h]
				  << "  >  V: " << v << "   ?";
			     cin >> ch;

	    while ( j > h  &&  a[j-h] > v)  {
			     cout << "\nInni:\t" << ++nr << ":\tH: " << h
				  << "\tI: " << i << "\tJ: " << j
				  << "\tJ-H: " << j-h
				  << "\t\ta[" << j-h << "]: " << a[j-h]
				   << "  >  V: " << v << "   !!!";
			     cin >> ch;

		    a[j] = a[j-h];
		    j -= h;
			     cout << "\nInni:\t\tH: " << h
				  << "\tI: " << i << "\tJ: " << j
				  << "\tJ-H: " << j-h << "\t" << a;
			     cin >> ch;
		}
	    a[j] = v;
		    cout << "\nEtter:\t" << ++nr << ":\tSammenligning utf›rt,";
		    if (j <= h) cout << "\tJ <= H";
		    else       cout << "\t" << a[j-h] << " <= " << v;
		    cout << "\t" << a;
		    cin >> ch;
	  }
			     cout << "\n\nH = " << h << " er ferdig !!\n\n";
			     cin >> ch;
  }
}


int main()  {
  char ch;
  cout << "\n\nViser bruken av SHELLSORT";   cin >> ch;
  fyllArray();
  shellsort(tekst, LEN-1);
  return 0;
}
