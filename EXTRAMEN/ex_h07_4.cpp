//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H07_4.CPP

//     Lõsningsforslag til eksamen i "Algoritmiske metoder",
//     4.desember 2007, oppgave nr.4.

//     Laget av Frode Haug, HiG, november 2007.


//  Oppgaven lõses enklest ved Ü permutere sifrene 1-9,
//  der indeks nr.0 er A; nr.1 er B, ......, nr.8 er I.
//  Dette gjõres inntil alle de Ütte regnestykkene stemmer.

//  Lõsningen er IKKE effektiv ved at den avskjërer permuteringen
//  nÜr tidlige indekser allerede ikke stemmer med stykkene
//  (f.eks. stykke nr.2 (A-B=1):  arr[0] - arr[1]  =/=  1).


#include <iostream>
using namespace std;

const int   N = 9;
const int ANT = 8;


//  OPPGAVELùSNINGEN BESTèR HOVEDSAKELIG AV DE TRE NEDENFOR 
//  DEFINERTE ARRAYENE OG FUNKSJONEN "SJEKK" (+ "SKRIV").


//             A  B  C  D  E  F  G  H  I
int arr[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

char oper[]         = "+--++-++";
int  stykke[ANT][3] = {{8, 9, 8}, {1, 2, 1}, {5, 8,  1}, {3, 5, 14},
                       {6, 1, 7}, {2, 4, 1}, {7, 6, 11}, {9, 3,  7}};



void skriv(int a[])  {
  cout  << "\nLùSNING:\n";
  for (int i = 0;  i < N;  i++)
      cout << '\t' << char(i + 'A') << " = " << a[i] << '\n';
}


bool sjekk(int a[])  {                    //  Sjekker om en lovlig lõsning:
   for (int i = 0;  i < ANT;  i++) {
       if (oper[i] == '+')  {              //  Addisjon (+):
          if (a[stykke[i][0]-1] + a[stykke[i][1]-1] != stykke[i][2]) return false;
       } else                              //  Subtraksjon (-):
          if (a[stykke[i][0]-1] - a[stykke[i][1]-1] != stykke[i][2]) return false;
    }
  skriv(a);
  return true;
}


/*
//  Alternativt (trenger da IKKE Ü bruke arrayene "oper" og "stykke"):

bool sjekk(int a[])  {
  if (a[7] + a[8] !=  8)  return false;
  if (a[0] - a[1] !=  1)  return false;
  if (a[4] - a[7] !=  1)  return false;
  if (a[2] + a[4] != 14)  return false;
  if (a[5] + a[0] !=  7)  return false;
  if (a[1] - a[3] !=  1)  return false;
  if (a[6] + a[5] != 11)  return false;
  if (a[8] + a[2] !=  7)  return false;
  skriv(a);
  return true;
}
*/


// DE TRE NESTE FUNKSJONENE ER HENTET RETT FRA/KOMPLETT IDENTISKE TIL EKS_06:

void bytt(int & a1, int & a2)  {       //  Bytter om to array-elementer.
  int aa = a1;  a1 = a2;    a2 = aa;
}

void roter_venstre(int a[], int i)  {  //  Roterer elementer mot venstre.
  int x, k;
  x = a[i];                            //  Tar vare pÜ fõrste.
  for (k = i+1;  k < N;  k++)          //  Roterer:
    a[k-1] = a[k];
  a[N-1] = x;                          //  Legger fõrst inn bakerst.
}

void perm(int i)  {
  int t;
  if (i == N-1)                        //  NÜdd en ny permutasjon:
     sjekk(arr);                      //  Skriver ut arrayens innhold.
  else {                               //  Skal permutere:
     perm(i+1);                        //  Beholder nÜvërende nr.'i'.
                                       //    Permuterer resten.
     for (t = i+1; t < N; t++)  {
        bytt(arr[i], arr[t]);          //  Bytter nr.'i' etter tur med alle
                                       //    de andre etterfõlgende.
        perm(i+1);                     //  For hver av ombyttene: permuterer
     }                                 //    resten av de Nè etterfõlgende.
     roter_venstre(arr, i);            //  Gjenoppretter opprinnelig array.
  }
}


int main()  {
  perm(0);	
  cout << "\n\n";
  return 0;
}
