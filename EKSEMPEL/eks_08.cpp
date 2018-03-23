//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_08.CPP

//  Eksemplet viser koden fra side 118 i læreboka.


//  Utskriftslinjene med 'Slutt: .....' er identiske med de på
//      figur 9.3 s.119 i læreboka.
//  Utskriftslinjene med 'Start: .....' viser (sub)arrayen FR
//      selve partisjoneringen har blitt foretatt inni hver 'Quicksort'.
//  Utskriftslinjene med 'Før: .....' viser (sub)arrayen idet en
//      rekursiv versjon av 'Quicksort' starter opp, Når (sub)arrayen
//      består av null eller ett element, så vil ingen partisjonering
//      finne sted. Utskriften 'Før: .....' gjør at vi også får "se"
//      disse kallene som ikke medfører noe som helst.


//  To små endringer gjør at kan utprøves for exercise 7 s.131 i læreboka.

#ifdef _MSC_VER					// For å slippe warnings/errors ifm. strcpy:
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>        //  strcpy

using namespace std;


const int LEN = 16;  // Ex.7 s.131:   13   //  Tekstens max.lengde, inkl.'\0'.
char tekst[LEN];          //  Streng med bokstavene som skal sorteres.

		   int lnr = 0;   //  Teller opp linjenummer.
		   int ant = 0;   //  Global variabel som teller opp
 				          //    antall sammenligninger i 'Quicksort'.
typedef char itemType;


void fyllArray()  {
  strcpy(tekst, "ASORTINGEXAMPLE");
// Ex.7 s.131:  strcpy(tekst, "EASYQUESTION");
}


void swap(itemType a[], int i, int j)  {    //  Jfr. s.95 i læreboka.
  itemType	t = a[i];
			a[i] = a[j];
			a[j] = t;
}


void quicksort(itemType a[], int l, int r)  {   //  Jfr. s.118 i læreboka.

  int i, j; itemType v;
            char ch;
		    int k;           //  Hjelpevariabel for tegnutskrift.
		    cout << "\n" << ++lnr << ")\tF›r:\t\t";
		    for (k = l;  k <= r;  k++)  //  Skriver (sub)arrayen.
		        cout << a[k] << ' ';    //  Når denne er på null eller
		    cout << "\t\tL: " << l << "\tR: " << r;
		    cin >> ch;       //  ett element, vil if-testen under bli FALSE.
  if (r > l)  {             //  Dersom to eller flere elementer:
     v = a[r];              //  'v' = partisjonselementet (dvs. elementet
			                //        aller lengst til høyre i subarrayen
			                //        fra a[l] til a[r]).
     i = l-1;  j = r;       //  Initierer begge til rett utenfor grensene
			                //    av det området som skal omflyttes.
			                //  Skriver (sub)arrayen:
		   cout << "\n" << ++lnr << ")\tStart:\t\t";
		   for (k = l;  k <= r;  k++)  cout << a[k] << ' ';  cin >> ch;
     for ( ; ; )  {         //  Looper til break'er ut.
			                //  NB:  'i' og 'j' økes/minskes FR bruk.
			                //       Derfor er de initiert utenfor grensene.
			                //       De stopper dessuten på de aktuelle
			                //       indekser UTEN å "hoppe" en for langt.
	    while (a[++i] < v)  //  Looper til større (eller lik) 'v'.
		          ant++  ;  //  Teller opp for hver TRUE sammenligning.
		          ant++;    //  Teller opp når blir FALSE.
	    while (a[--j] > v)  //  Looper til mindre (eller lik) 'v'.
		          ant++  ;  //  Teller opp for hver TRUE sammenligning.
		          ant++;    //  Teller opp når blir FALSE.
	    if (i >= j)  break; //  Tellerne har passert hverandre:  break'er.
	    swap(a, i, j);      //  Bytter elementene 'i' og 'j'.
     }
     swap(a, i, r);         //  Smetter inn partisjonselementet på plass 'i'.
			                //  Skriver (sub)arrayen:
		   cout << "\n" << ++lnr << ")\t\tSlutt:\t";
		   for (k = l;  k <= r;  k++)  cout << a[k] << ' ';   cin >> ch;
     quicksort(a, l, i-1);  //  Gjentar for alt til venstre for 'a[i]'.
     quicksort(a, i+1, r);  //  Gjentar for alt til høyre for 'a[i]'.
  }
}



int main()  {
  char ch;
  cout << "\n\nViser bruken av QUICKSORT";   cin >> ch;
  fyllArray();
  quicksort(tekst, 0, LEN-2);
  cout << "\n\nAntall sammenligninger av elementer i 'Quicksort':  " << ant << '\n';
  return 0;
}
