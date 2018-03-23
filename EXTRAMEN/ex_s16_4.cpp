
//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S16_4.CPP

//  Løsningforslag til kontinuasjonseksamen i Alg.met, august 2016, oppgave nr.4.
//  Laget av Frode Haug, NTNU


#include <iostream>		//  cout, cin
using namespace std;

const int N = 20;	//  Arrayenes lengde.
					//  Max. snømengde (i cm) målt de 20 aktuelle årene:
int mengde[N] = { 50, 32, 74, 29, 61, 42, 53, 29, 78, 39, 
                  51, 18, 27, 64, 25, 42, 48, 37, 44, 48 };
int sist[N];        //  Antall år siden det sist var minst like mye snømengde.

// 'sist' vil til slutt inneholde:  
//                -1  1  -1  1  2  1  2  1  -1  1  2  1  2  5  1  2  3  1  2  3


int main()  {
	int i, j;

	for (i = 0;  i < N;  i++)  {	//  For hvert år:
		j = i - 1;					//  Initierer til det forrige året.
									//  Så lenge år igjen og mengden mindre:
		while (j >= 0  &&  mengde[j] < mengde[i])  
			j--;					//  Teller til året før det igjen.
		if (j < 0) sist[i] = -1;	//  Ingen tidligere med like mye snømengde.
		else       sist[i] = i - j; //  Antall år siden minst like mye.
	}

	for (i = 0;  i < N;  i++)		//  Skriver ut 'siste'-arrayens innhold:
		cout << "  " << sist[i];

	cout << "\n\n";						
	return 0;
}
