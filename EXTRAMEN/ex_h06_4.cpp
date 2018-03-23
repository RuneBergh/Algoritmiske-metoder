//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H06_4.CPP

//     L�sningsforslag til eksamen i "Algoritmiske metoder",
//     4.desember 2006, oppgave nr.4.

//     Laget av Frode Haug, HiG, november 2006.


//  Oppgaven kan l�ses ved � bruke noe av den samme tankegangen/algoritmen
//  som i modifiserte utgaver av "visit"-funksjonene i l�rebokas kap.29
//  eller ved � endre en del p� EKS_12.
//  Men, den kan ogs� (og enda enklere) l�ses ved � permutere sifrene 0-9,
//  inntil den rette summen for hver av nodenes naboer oppst�r. 
//  Dette siste er valgt/kodet i dette l�sningsforslaget:


#include <iostream>
using namespace std;

const int N = 10;
         // Node nr:  0  1  2  3  4  5  6  7  8  9       Node nr:
int adj[N][N] =  {  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0 },    //  0
                    { 1, 0, 0, 0, 1, 0, 1, 0, 0, 0 },    //  1
                    { 1, 0, 0, 0, 1, 1, 1, 0, 0, 0 },    //  2
                    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },    //  3
                    { 0, 1, 1, 1, 0, 0, 1, 1, 1, 1 },    //  4
                    { 0, 0, 1, 0, 0, 0, 1, 1, 0, 0 },    //  5
                    { 0, 1, 1, 0, 1, 1, 0, 1, 1, 1 },    //  6
                    { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1 },    //  7
                    { 1, 0, 0, 0, 1, 0, 1, 0, 0, 1 },    //  8
                    { 0, 0, 0, 0, 1, 0, 1, 1, 1, 0 } };  //  9


//  OPPGAVEL�SNINGEN BEST�R HOVEDSAKELIG AV DE TO NEDENFOR 
//  DEFINERTE ARRAYENE "SUM" OG "ARR" PLUSS FUNKSJONEN "SJEKK":

int sum[N]  = { 21, 33, 14, 27, 1, 14, 20, 12, 28, 20 };

int arr[N] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };


bool sjekk(int a[])  {                    //  Sjekker om en lovlig l�sning:
  int i, j, tot;                          //  L�kkevariable og totalsum.

  for (i = 0;  i < N;  i++)  {            //  G�r gjennom alle nodene:
      tot = 0;                            //  Nullstiller totalsummen.
      for (j = 0;  j < N;  j++)           //  G�r gjennom nodens naboer:
          if (adj[i][j])  tot += a[j];    //  Naboer? Summerer opp.
      if (tot != sum[a[i]]) return false; //  Feil totalsum? Avbryter.
  }
                                          //  Har funnet en l�sning:
  for (i = 0;  i < N;  i++)  cout << "\nIndeks nr." << i << ": " << a[i];
  cout << "\n\n";
  return true;
}


// DE TRE NESTE FUNKSJONENE ER HENTET RETT FRA/KOMPLETT IDENTISKE TIL EKS_06:

void bytt(int & a1, int & a2)  {       //  Bytter om to array-elementer.
  int aa = a1;  a1 = a2;    a2 = aa;
}

void roter_venstre(int a[], int i)  {  //  Roterer elementer mot venstre.
  int x, k;
  x = a[i];                            //  Tar vare p� f�rste.
  for (k = i+1;  k < N;  k++)          //  Roterer:
    a[k-1] = a[k];
  a[N-1] = x;                          //  Legger f�rst inn bakerst.
}

void perm(int i)  {
  int t;
  if (i == N-1)                        //  N�dd en ny permutasjon:
     sjekk(arr);                       //  Skriver ut arrayens innhold.
  else {                               //  Skal permutere:
     perm(i+1);                        //  Beholder n�v�rende nr.'i'.
                                       //    Permuterer resten.
     for (t = i+1; t < N; t++)  {
        bytt(arr[i], arr[t]);          //  Bytter nr.'i' etter tur med alle
                                       //    de andre etterf�lgende.
        perm(i+1);                     //  For hver av ombyttene: permuterer
     }                                 //    resten av de N� etterf�lgende.
     roter_venstre(arr, i);            //  Gjenoppretter opprinnelig array.
  }
}


int main()  {
  perm(0);	
  cout << "\n\n";
  return 0;
}
