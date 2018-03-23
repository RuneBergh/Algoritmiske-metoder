//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_08.CPP

//  Eksemplet viser koden fra side 118 i l�reboka.


//  Utskriftslinjene med 'Slutt: .....' er identiske med de p�
//      figur 9.3 s.119 i l�reboka.
//  Utskriftslinjene med 'Start: .....' viser (sub)arrayen F�R
//      selve partisjoneringen har blitt foretatt inni hver 'Quicksort'.
//  Utskriftslinjene med 'F�r: .....' viser (sub)arrayen idet en
//      rekursiv versjon av 'Quicksort' starter opp, N�r (sub)arrayen
//      best�r av null eller ett element, s� vil ingen partisjonering
//      finne sted. Utskriften 'F�r: .....' gj�r at vi ogs� f�r "se"
//      disse kallene som ikke medf�rer noe som helst.


//  To sm� endringer gj�r at kan utpr�ves for exercise 7 s.131 i l�reboka.

#ifdef _MSC_VER					// For � slippe warnings/errors ifm. strcpy:
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


void swap(itemType a[], int i, int j)  {    //  Jfr. s.95 i l�reboka.
  itemType	t = a[i];
			a[i] = a[j];
			a[j] = t;
}


void quicksort(itemType a[], int l, int r)  {   //  Jfr. s.118 i l�reboka.

  int i, j; itemType v;
            char ch;
		    int k;           //  Hjelpevariabel for tegnutskrift.
		    cout << "\n" << ++lnr << ")\tF�r:\t\t";
		    for (k = l;  k <= r;  k++)  //  Skriver (sub)arrayen.
		        cout << a[k] << ' ';    //  N�r denne er p� null eller
		    cout << "\t\tL: " << l << "\tR: " << r;
		    cin >> ch;       //  ett element, vil if-testen under bli FALSE.
  if (r > l)  {             //  Dersom to eller flere elementer:
     v = a[r];              //  'v' = partisjonselementet (dvs. elementet
			                //        aller lengst til h�yre i subarrayen
			                //        fra a[l] til a[r]).
     i = l-1;  j = r;       //  Initierer begge til rett utenfor grensene
			                //    av det omr�det som skal omflyttes.
			                //  Skriver (sub)arrayen:
		   cout << "\n" << ++lnr << ")\tStart:\t\t";
		   for (k = l;  k <= r;  k++)  cout << a[k] << ' ';  cin >> ch;
     for ( ; ; )  {         //  Looper til break'er ut.
			                //  NB:  'i' og 'j' �kes/minskes F�R bruk.
			                //       Derfor er de initiert utenfor grensene.
			                //       De stopper dessuten p� de aktuelle
			                //       indekser UTEN � "hoppe" en for langt.
	    while (a[++i] < v)  //  Looper til st�rre (eller lik) 'v'.
		          ant++  ;  //  Teller opp for hver TRUE sammenligning.
		          ant++;    //  Teller opp n�r blir FALSE.
	    while (a[--j] > v)  //  Looper til mindre (eller lik) 'v'.
		          ant++  ;  //  Teller opp for hver TRUE sammenligning.
		          ant++;    //  Teller opp n�r blir FALSE.
	    if (i >= j)  break; //  Tellerne har passert hverandre:  break'er.
	    swap(a, i, j);      //  Bytter elementene 'i' og 'j'.
     }
     swap(a, i, r);         //  Smetter inn partisjonselementet p� plass 'i'.
			                //  Skriver (sub)arrayen:
		   cout << "\n" << ++lnr << ")\t\tSlutt:\t";
		   for (k = l;  k <= r;  k++)  cout << a[k] << ' ';   cin >> ch;
     quicksort(a, l, i-1);  //  Gjentar for alt til venstre for 'a[i]'.
     quicksort(a, i+1, r);  //  Gjentar for alt til h�yre for 'a[i]'.
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
