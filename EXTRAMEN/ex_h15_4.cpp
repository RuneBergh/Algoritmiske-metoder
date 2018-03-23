//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H15_4.CPP

//     Løsningsforslag til eksamen i "Algoritmiske metoder",
//     14.desember 2015, oppgave nr.4.

//     Laget av Frode Haug, HiG, november 2015.


//  Funksjonen "bool OK(.....)" er hovedsvaret på oppgaven.
//  Resten er så godt som bare en kopi av koden i EKS_06.CPP (permutering),
//  med avskjæringer som i OPPG_07.CPP (og OPPG_08.CPP).


#include <iostream>					//  cout, cin
using namespace std;

const int N = 9;					//  Arrayens lengde.
int arr[N];							//  Global array av int'er.


//  Sjekker at summen av alle verdiene i en nodes naboer
//    er heltallig delelig med verdien inni noden selv.
//    Gjør bare de høyst nødvendige sjekker (ift. nodenr):

bool OK(int a[], int n)  {
  if (n >= 2)  {					// Minst node As naboer:
	 if ((a[1] + a[2]) % a[0]) return false;
	 if (n >= 4)  {					// Minst node Bs naboer:
	    if ((a[0] + a[2] + a[3] + a[4]) % a[1]) return false;
	    if (n >= 5) {				// Minst node Cs naboer:
		   if ((a[0] + a[1] + a[4] + a[5]) % a[2]) return false;
		   if (n >= 6) {			// Minst node Ds naboer:
			  if ((a[1] + a[4] + a[6]) % a[3]) return false;
			  if (n >= 7) {			// Minst node E og Fs naboer:
				 if ((a[1] + a[2] + a[3] + a[5] + a[6] + a[7]) % a[4]) return false;
				 if ((a[2] + a[4] + a[7]) % a[5]) return false;
				 if (n == 8) {		// Nodene G, H og Is naboer:
				    if ((a[3] + a[4] + a[7] + a[8]) % a[6]) return false;
					if ((a[4] + a[5] + a[6] + a[8]) % a[7]) return false;
					if ((a[6] + a[7]) % a[8]) return false;
				 }
			  }
		   }
		}
	 }
  }
  return true;
}


void display(int a[])  {			//  Viser arrayens innhold.
  cout << "\n";
  for (int i = 0; i < N; i++)
	  cout << a[i] << ' ';
}


void bytt(int & a1, int & a2)  {	//  Bytter om to array-elementer.
	int aa = a1;
	a1 = a2;
	a2 = aa;
}


void roter_venstre(int a[], int i)  {	//  Roterer elementer mot venstre.
	int x, k;
	x = a[i];							//  Tar vare på første.
	for (k = i + 1; k < N; k++)			//  Roterer:
		a[k - 1] = a[k];
	a[N - 1] = x;						//  Legger først inn bakerst.
}


void perm(int i)  {
	int t;
	if (i == N - 1)  {					 //  Nådd fullstendig ny permutasjon,
		if (OK(arr, N-1))			     //    OG LØSNING:
		   display(arr);				 //  Skriver ut arrayens innhold.
	} else {							 //  Skal permutere:
		if (OK(arr, i))					 //  Lovlig permutasjon hittil:
		   perm(i + 1);					 //  Beholder nåværende nr.'i'.
		for (t = i + 1; t < N; t++)  {	 //    Permuterer resten:
			bytt(arr[i], arr[t]);		 //  Bytter nr.'i' etter tur med alle
										 //    de andre etterfølgende.
			if (OK(arr, i))				 //  Fortsatt lovlig permutasjon:
			   perm(i + 1); 			 //  For hver av ombyttene: permuterer
		}								 //    resten av de N etterfølgende.
		roter_venstre(arr, i);			 //  Gjenoppretter opprinnelig array.
	}
}


int main()  {
	for (int i = 0; i < N; i++)		//  Fyller array med: 1, 2, ..., 8, 9
		arr[i] = i + 1;
	perm(0);						//  Lager permutasjoner. Skriver løsninger.
	cout << "\n\n";						
	return 0;
}


/*

Svar:
=====
Luk vekk speilinger omkring vertikal akse (gjennom nodene D, E og F) og 
horisontal akse (gjennom nodene A, E og I) som UTGJØR EN STØRRE INT FØR,
ENN ETTER AT DE ER SPEILET. (Er int'en ETTER speiling mindre enn FØR,
er denne permutasjonen/løsningen funnet før!)



Begrunnelse/forklaring:
=======================
De fire løsningene som dette programmet genererer/lager/viser er:
	1:	4 1 7 9 6 3 2 8 5
	2:	4 7 1 3 6 9 8 2 5
	3:	5 2 8 9 6 3 1 7 4
	4:	5 8 2 3 6 9 7 1 4

Nr.4 er nr.1 baklengs. 
Altså bare en speiling omkring den vertikale aksen.
Dvs. leser man nr.1 som en eneste sammenhengende int, 
og nr.4 baklengs på samme måte, får vi det samme tallet.
Så lenge nr.4 lest forlengs er en større int enn nr.4 lest baklengs,
har vi altså funnet nr.4 før (som nr.1)!

Nr.3 er nr.2 baklengs. 
Derfor er, av samme grunn som ovenfor, også nr.3 funnet før.

Nr.2 derimot er en speiling av nr.1 omkring den horisontale aksen.
Dvs. B og C har byttet plass, D og F har byttet, og G og H det samme.
int'en som nr.2 utgjør er større enn nr.1, derfor er også nr.2 funnet fra før.

Så oppsummert: 
Det finnes bare EN ENESTE UNIK løsning på denne problemstillingen, 
og det er nr.1.

*/