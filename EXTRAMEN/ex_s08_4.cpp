//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S08_4.TXT

//     L›sningsforslag til kontinuasjonseksamen i "Algoritmiske metoder",
//     13.august 2008, oppgave nr.4.

//     Laget av Frode Haug, HiG, mai 2008.


//     Vi ser at: Tekstene TWO og SQUARE har ingen felles tegn,
//     og at ingen av ordene, hver for seg, inneholder duplikate tegn.
//     Dette medf›rer at dersom kvadratet av tre-sifrede tall ALT sammen
//     inneholder unike sifre, s† har vi en (av flere?) l›sninger.
  
//     L›sningen nedenfor er rimelig rask og brukbart optimal. 
//     Samtidig er den enkel og forst†elig(?).


#include <iostream>
#include <cstring>       //  strlen
#include <cstdlib>       //  itoa
using namespace std;

const int LEN = 20;


bool unike_sifre(int n)  { //  Inneholder 'n' KUN UNIKE sifre eller ei?
  int i, j, len;
  char txt[LEN];

  itoa(n, txt, 10);                  //  Konverterer tall til tekst.
  len = strlen(txt);

  for (i = 0;  i < len-1;  i++)      //  G†r gjennom HELE teksten/tallet:
      for (j = i+1;  j < len;  j++)  //  Sammenligner med etterf›lgende sifre:
          if (txt[i] == txt[j]) return false;  //  Like sifre - IKKE unike.
  return true;                                 //  Sifrene er ALLE UNIKE.
}


int main()   {
  int i, n;                    //  L›kkevariabel og "kvadrat-svar".

//  F›rste aktuelle svar ("SQUARE") er 102345, kvadratroten av dette er ca.320.
//  For-l›kke b›r derfor starte der, men "ikke noe feil" ved † starte p† 102:
  for (i = 320;  i <= 987;  i++)  {  //  ALLE aktuelle tre-sifrede tall:
      n = i * i;                     //  Unikt tre-sifret tall ("TWO") SAMMEN
      if (unike_sifre(i*1000000+n))  //    MED unikt kvadrat ("SQUARE")?
         cout << i << " * " << i << " = " << n << '\n';
  }
  return 0;
}
