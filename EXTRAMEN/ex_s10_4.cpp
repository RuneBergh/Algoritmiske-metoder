//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S10_4.CPP

//     L›sningsforslag til kontinuasjonseksamen i "Algoritmiske metoder",
//     10.august 2010, oppgave nr.4.

//     Laget av Frode Haug, HiG, mai 2010.


//  Program som permuterer sifrene 1...9 p† alle tenkelige m†ter.
//  Tegnet '+' og '/' settes inn ett sted hver, mellom int'ene som
//  oppst†r, slik at svaret p† regnestykket blir 100.
//  To (av 11) eksempler:  100 = 91 + 5742/638   100 = 3 + 69258/ 714


#include <iostream>
using namespace std;


const int N = 9;                      //  Antall ulike sifre.
int arr[N];                           //  Global array av int'er.


//  To neste funksjoner er hovedsakelig det selvskrevne
//  ifm. l›sning av denne oppgaven:

                                      //  Omgj›r (og returnerer) sifrene mellom
int lag_int(int a[], int m, int n)  { //    indeks m og n til/som en int:
  int tall = 0;
  for (int i = m;  i <= n;  i++)      //  G†r gjennom sifrene, ganger med 10
          tall = tall*10 + a[i];      //    og legger til nytt siffer bakerst.
  return tall;                        //  Returnerer utregnet/omgjort int.
}
                                      //  Sjekker om aktuell permutasjon kan gi
                                      //    rett regnestykke ved † sette inn
void sjekk(int a[])  {                //    '+' og '/' mellom sifrene:
  int b, c, d, j = 5;                 //  3.tall M v‘re p† 3 sifre, da 2 stk.
                                      //    ALLTID er for lite og 4 for mye.
                                      //  1.tallet M v‘re p† 1 eller 2 sifre
  for (int i = 0;  i <= 1;  i++)  {   //    (ellers > 100). Alts† M '+' st†
                                      //    ETTER siffer nr.0 eller 1.
          b = lag_int(a, 0, i);       //  1.int'en (ut fra subarrayen).
          c = lag_int(a, i+1, j);     //  2.int'en (ut fra subarrayen).
          d = lag_int(a, j+1, N-1);   //  3.int'en (ut fra subarrayen).
          if ( b + (float(c)/d) == 100.0F)  //  Regnestykket er EKSAKT lik 100:
             cout << b << " + " << c << " / " << d << " = 100\n";
      }
}


// Tre neste funksjoner og 'main' er s† godt som identisk til EKS_06.CPP:

void bytt(int & a1, int & a2)  {      //  Bytter om to array-elementer.
  int aa = a1;
      a1 = a2;
      a2 = aa;
}


void roter_venstre(int a[], int i)  { //  Roterer elementer mot venstre.
  int x, k;
  x = a[i];                           //  Tar vare p† f›rste.
  for (k = i+1;  k < N;  k++)         //  Roterer:
    a[k-1] = a[k];
  a[N-1] = x;                         //  Legger f›rst inn bakerst.
}


void perm(int i)  {
  int t;
  if (i == N-1)                       //  N†dd en ny permutasjon:
     sjekk(arr);                      //  Mulig † f† 100 "ut av arrayen"?
  else {                              //  Skal permutere:
     perm(i+1);                       //  Beholder n†v‘rende nr.'i'.
                                      //    Permuterer resten.
     for (t = i+1; t < N; t++)  {
             bytt(arr[i], arr[t]);    //  Bytter nr.'i' etter tur med alle
                                      //    de andre etterf›lgende.
             perm(i+1);               //  For hver av ombyttene: permuterer
     }                                //    resten av de N etterf›lgende.
     roter_venstre(arr, i);           //  Gjenoppretter opprinnelig array.
  }
}


int main()  {
  for (int i = 0;  i < N;  i++)       //  Fyller array med: 1, 2, 3, ..., 9
      arr[i] = i+1;
                                      //  Lager/skriver permutasjon av ALLE
  perm(0);                            //     sifrene/arrayelementene.
                                      //  Evt. finner og skriver l›sninger.
  cout << "\n\n";
  return 0;      
}
