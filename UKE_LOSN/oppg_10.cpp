//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_10.CPP

//   L›sningsforslag til oppgave nr.10  i  Algoritmiske metoder.


//  Programmet viser koden fra side 118 i l‘reboka, modifisert med:
//     - 'Insertion' sortering foretas n†r subarrayen blir mindre enn M.
//     - at partisjonselementet bestemmes vha. 'median-of-three' metoden.


#include <iostream>         //  cout
#include <cstring>          //  strlen

using namespace std;


const int M   = 5;           //  N†r subarray <= M, s† foretas Insertion-sort.
int LEN;                     //  Tekstens aktuelle lengde.

char tekst[] =               //  Streng med bokstavene som skal sorteres.
  " Dette er en lengre setning som blir sortert etter beste evne";


		   int lnr = 0;      //  Teller opp linjenummer.
typedef char itemType;


void swap(itemType a[], int i, int j)  {        //  Jfr.s.95 i l‘reboka.
  itemType    t = a[i];
	   a[i] = a[j];
	   a[j] = t;
}


void insertion(itemType a[], int l, int r)  {   //  Jfr.s.100 i l‘reboka.
  int i, j;  itemType v;

  itemType sk = a[l-1];      //  Lagrer unna elementet utenfor til venstre.
  a[l-1] = char(1);          //  Legger inn 'sentinel key' p† dens plass.
  for (i = l+1;  i <= r;  i++)  {    // G†r kun gjennom subarrayen:
      v = a[i];  j = i;                  //   |
      while (a[j-1] > v)                 //   |  Identisk med koden s.100.
	     {  a[j] = a[j-1];  j--;  }      //   |
      a[j] = v;                          //   |
  }                                      //   |
  a[l-1] = sk;                //  Legger tilbake opprinnelig element.
}

			     //  Jfr.s.95 og 2.avsnitt under "Median-of-Three
			     //    Partitioning" s.126 i l‘reboka.
void medianOfThree(itemType a[], int l, int r)  {
   int m = (l+r)/2;                     //  Finner midtposisjonen.
   if (a[l] > a[m])  swap(a, l, m);     //  |
   if (a[l] > a[r])  swap(a, l, r);     //  |  Sorterer de tre elementene:
   if (a[m] > a[r])  swap(a, m, r);     //  |
   swap(a, m, r-1);                     //  Legger det midtre inn NEST SIST.
}


void quicksort(itemType a[], int l, int r)  {   //  Jfr.s.118 i l‘reboka.
  
  int i, j;   itemType v;
           char ch;
		   int k;                      //  Hjelpevariabel for tegnutskrift.
		   cout << "\n\n" << ++lnr << ")\tF›r:\t";
		   for (k = l;  k <= r;  k++)  //  Skriver (sub)arrayen.
		       cout << a[k];
		   cout << "\t\tL: " << l << "\tR: " << r;
  if (r-l <= M)              //  Har en subarray av lengde mindre eller lik M.
     insertion(a, l, r);     //  Kj›rer insertion p† denne delen.
  else  {                    //  Subarrayen er st›rre enn M:
     medianOfThree(a, l, r); //  Soterer f›rste, midtre og siste element.
		   cout << "\n" << ++lnr << ")\tM-o-T:\t";
		   for (k = l;  k <= r;  k++)  cout << a[k];
     v = a[r-1];             //  'v' = partisjonselementet. Dvs. det midle
			                 //        elementet av det lengst til venstre,
			                 //        h›yre og midten (n†r disse er sortert).
			                 //        Dette ligger NEST SIST i (sub)arrayen.
     i = l;  j = r-1;        //  Initierer begge til grensene av det omr†det
			                 //       som skal omflyttes.
     for ( ; ; )  {          //  Looper til break'er ut.
			                 //  NB:  'i' og 'j' ›kes/minskes FR bruk.
			                 //       Derfor er de initiert utenfor grensene.
			                 //       De stopper dessuten p† de aktuelle
			                 //       indekser UTEN † "hoppe" en for langt.
	    while (a[++i] < v)  ;   //  Looper til st›rre (eller lik) 'v'.
	    while (a[--j] > v)  ;   //  Looper til mindre (eller lik) 'v'.
	    if (i >= j)  break;     //  Tellerne har passert hverandre:  break'er.
	    swap(a, i, j);          //  Bytter elementene 'i' og 'j'.
     }
     swap(a, i, r-1);        //  Smetter inn partisjonselementet p† plass 'i'.
			                 //  Skriver (sub)arrayen:
		   cout << "\n" << ++lnr << ")\tSlutt:\t";
		   for (k = l;  k <= r;  k++)  cout << a[k];   cin >> ch;
     quicksort(a, l, i-1);   //  Gjentar for alt til venstre for 'a[i]'.
     quicksort(a, i+1, r);   //  Gjentar for alt til h›yre for 'a[i]'.
  }
}



int main()  {
  char ch;
  cout << "\n\nViser en modifisert QUICKSORT";  cin >> ch;  cout << "\n\n\n";
  tekst[0] = char(1);          //  Legger inn venstre 'sentinel key'.
  LEN = strlen(tekst);
  quicksort(tekst, 1, LEN-1);  //  Sorterer.
  cout << "\n\n-" << tekst+1 << "-\n\n";   //  Skriver slutt-resultat.
  return 0;  
}
