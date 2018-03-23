//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H11_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     20.desember 2011, oppgave nr.4.

//     Laget av Frode Haug, HiG, desember 2011.


#include <iostream>
using namespace std;

const int N = 10;                      //  Arrayens lengde.

                                       //  NYTT: Initierer global array:
int arr[N] = { 23, 17, 4, 3, 32, 9, 8, 12, 21, 37 };

float maks_svar = -1.0F;               //  NYTT: Maks.svar/resultat (hittil).


void display(int a[])  {               //  Viser arrayens innhold.
  cout << "\n";
  for (int i = 0;  i < N;  i ++)
    cout << a[i] << ' ';
}


void bytt(int & a1, int & a2)  {       //  Bytter om to array-elementer.
  int aa = a1;
      a1 = a2;
      a2 = aa;
}


void roter_venstre(int a[], int i)  {  //  Roterer elementer mot venstre.
  int x, k;
  x = a[i];                            //  Tar vare p† f›rste.
  for (k = i+1;  k < N;  k++)          //  Roterer:
    a[k-1] = a[k];
  a[N-1] = x;                          //  Legger f›rst inn bakerst.
}


void regn_ut()  {             //  OPPGAVE 4A:
  float svar = arr[0];
  for (int i = 1;  i < N;  i++)
      svar = (svar + arr[i]) * 2.0F;
  if (svar > maks_svar)  maks_svar = svar;
}
//  if (svar > maks_svar)
//     { maks_svar = svar; display(arr);  cout << svar << '\n';  }


void perm(int i)  {
  int t;
  if (i == N-1)                        //  N†dd en ny permutasjon:

     regn_ut();                        //  NYTT:  Oppgave 4A.

  else {                               //  Skal permutere:
     perm(i+1);                        //  Beholder n†v‘rende nr.'i'.
				       //    Permuterer resten.
     for (t = i+1; t < N; t++)  {
	bytt(arr[i], arr[t]);          //  Bytter nr.'i' etter tur med alle
				       //    de andre etterf›lgende.
	perm(i+1);                     //  For hver av ombyttene: permuterer
     }                                 //    resten av de N etterf›lgende.
     roter_venstre(arr, i);            //  Gjenoppretter opprinnelig array.
  }
}


int main()  {
  perm(0);                             //  Lager/skriver permutasjon av ALLE
				       //    sifrene/arrayelementene.

  cout << "\nMaks svar/resultat:  " << maks_svar << "\n\n";


/*  OPPGAVE 4B:
    Svaret p† dette er jo "selvsagt" † hele tiden velge ut de to st›rste
    tallene i mengden (s† summeres disse og deretter multipliseres med 2).

    Det enkleste er da bare † sortere arrayen, med det st›rste tallet f›rst.
    Spiller egentlig ikke s† mye rolle hvilken av sorteringsmetodene som
    velges, for i praksis er det snakk om sv‘rt f† elementer.
    Kan alts† like gjerne velge f.eks. 'insertion sort'.
    S† utf›res koden i'regn_ut' (jfr. oppgave 4A) bare EN gang.

    Alternativet er † bruke en heap. Der to og to tall hentes ut, og svaret
    legges hele tiden tilbake igjen. N†r det bare er ett tall p† heapen,
    er det maksimale svaret gitt/regnet ut. Men, dette blir en litt mer
    ineffektiv og kodingsmessige un›dvendig "komplisert og tuklete" metode
    enn det ovenfor f›rst skisserte.
*/

  return 0;
}

