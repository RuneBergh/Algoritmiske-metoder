
//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H16_4.CPP

//  Løsningforslag til eksamen i Alg.met, desember 2016, oppgave nr.4.
//  Laget av Frode Haug, NTNU


//  Program som permuterer sifrene 1234567890 på alle tenkelige måter
//  (jfr.EKS_06.CPP). Tallet (int'en) som tilsammen utgjøres av de tre første
//  sifrene PLUSS de tre neste skal til sammen være lik det FIREsifrede
//  tallet til slutt i arrayen. (Oppgaven er mye lik EX_S96_5 og  EX_S10_4.)

#include <iostream>
using namespace std;


const int N = 10;				//  Antall ulike sifre.
int   arr[N];					//  Global array av int'er.
int   ant = 0;					//  Totalt antall unike løsninger.

//  ---------------------------------------------------------------------------
//  To neste funksjoner er hovedsakelig det nye ifm. løsning av denne oppgaven:
//  ---------------------------------------------------------------------------
									//  Omgjør (og returnerer) sifrene mellom
int lagInt(int a[], int m, int n) {	//    indeks m og n til/som en int:
	int tall = 0;
	for (int i = m; i <= n; i++)	//  Går gjennom sifrene, ganger med 10
		tall = tall * 10 + a[i];	//    og legger til nytt siffer bakerst.
	return tall;					//  Returnerer utregnet/omgjort int.
}

									//  Sjekker om aktuell permutasjon gir
void sjekk(int a[]) {				//    det rette addisjonsstykket:
	int b = lagInt(a, 0, 2);		//  1.int'en (ut fra subarrayen).
	int c = lagInt(a, 3, 5);		//  2.int'en (ut fra subarrayen).
	int d = lagInt(a, 6, N - 1);		//  3.int'en (ut fra subarrayen).
									//  Regnestykket stemmer, 
	if (b + c == d  &&  b < c)		//    og er IKKE funnet før:
		cout << ++ant << ": " << b << " + " << c << " = " << d << '\n';
}



// Tre neste funksjoner og 'main' er så godt som identisk til EKS_06.CPP,
//   unntatt avskjæringene (2x if-setninger) ifm. å permutere videre:

void bytt(int & a1, int & a2) {		//  Bytter om to array-elementer.
	int aa = a1;   a1 = a2;   a2 = aa;
}


void roterVenstre(int a[], int i) {	//  Roterer elementer mot venstre.
	int x, k;
	x = a[i];						//  Tar vare på første.
	for (k = i + 1; k < N; k++)		//  Roterer:
		a[k - 1] = a[k];
	a[N - 1] = x;					//  Legger først inn bakerst.
}


void perm(int i) {
	int t;
	if (i == N - 1)							// Nådd en ny permutasjon:
		sjekk(arr);							// Rett addisjonsstykke?
	else {									// Permuterer videre:
		if (arr[6] != 0)					// FIREsifret sluttall:
			perm(i + 1);					// Beholder nåværende nr.'i'.
											//   Permuterer resten.
		for (t = i + 1; t < N; t++) {		// Bytter nr.'i' etter tur med alle
			bytt(arr[i], arr[t]);			//   de andre etterfølgende.
			if (arr[6] != 0)				// FIREsifret sluttall:
				perm(i + 1);				// For hver av byttene: permuterer
		}									//   resten av de N etterfølgende.
		roterVenstre(arr, i);				// Gjenoppretter opprinnelig array.
	}
}
//  Unødvendig å sjekke om ett av de to første tallene bare er 2-sifret
//  (dvs. starter med 0). For de kan max. være  987 + 65, hvilket alltid
//  max. blir et svar på 10xx-tallet. Og 0 kan jo ikke være to steder(!)
//  (både i starten av det 2-sifrede tallet, og som 2.siffer i 10xx).


int main() {
	for (int i = 0; i < N - 1; i++)     //  Fyller array med: 1, 2, ..., 9, 0
		arr[i] = i + 1;					//  Legger inn '0' bakerst, da denne 
	arr[N - 1] = 0;						//    uansett ALDRI skal komme først
										//    (for da får vi et 2-sifret tall).
										//  Lager permutasjon av
	perm(0);                            //    sifrene/arrayelementene, og
	cout << "\n\n";						//    evt. finner og skriver løsninger.
	return 0;
}
