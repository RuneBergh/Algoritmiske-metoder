//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S04_4.CPP

//     L�sningsforslag til kontinuasjonseksamen i
//     "Algoritmiske metoder", oppgave nr.4, 13.august 2004.

//     Laget av Frode Haug, HiG, juni 2004.


#include <iostream>     //  cout
using namespace std;


                        //  SELVE OPPGAVEN:
void lengst_sorterte_sekvens(int arr[], const int N, int & start, int & len) {
  int curr = 1;         //  Lengden p� 'n�v�rende' sekvens.
  int currstart = 0;    //  Starten p� 'n�v�rende' sekvens.
  int max = 1;          //  Lengden p� den forel�pig lengste sekvens.
  int maxstart = 0;     //  Starten p� den forel�pig lengste sekvens.
  int i;                //  L�kkevariabel;
  
  for (i = 0;  i < N-1;  i++)         //  G�r gjennom HELE arrayen:
	if (arr[i] <= arr[i+1]) curr++;   //  Sortert stigende - teller opp.
	else  {	                          //  Ikke stigende (lengre):
	   if (curr > max)                //  Ny lengste oppdaget:
	   {  max = curr;   maxstart = currstart;  }  // Oppdaterer med den lengste.
       curr = 1;  currstart = i+1;    //  Tilbakestiller letevariablene.
	}
                        //  M� spesialbehandle at var stigende p� slutten,
  if (curr > max)       //     og dermed kanskje ny lengste sekvens:
	 {  max = curr;   maxstart = currstart;  }
  start = maxstart;  len = max;       //  Oppdaterer referansevariable.
}


const int NN = 21;
int a[NN] = { 1, 3, 5, 2, 7, 9, 3, 8, 1, 10, 5, 2, 5, 7, 9, 11, 4, 5, 5, 10, 15 };


int main()  {
  int s, l, i;
    
  lengst_sorterte_sekvens(a, NN, s, l);

  cout << "\nArrayen:\n\t";
  for (i = 0;  i < NN;  i++)  cout << "  " << a[i];
  cout << "\nhar den lengste sorterte sekvensen startende i " 
	   << s << " og er " << l << " lang:\n\t";
  for (i = s;  i < s+l;  i++)  cout << "  " << a[i];
  cout << "\n\n";
  return 0;
}
