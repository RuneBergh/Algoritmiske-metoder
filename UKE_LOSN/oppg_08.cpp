//  Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_08.CPP

//       L›sningsforslag til oppgave nr.8  i  Algoritmiske metoder.


//   L›sningen baserer seg p† EKS_06.CPP, der:
//     - Int(-array) er erstattet med char.
//     - Tekst leses inn fra tastaturet.
//     - 'Display' er NOE endret.
//     - 'Perm' har blitt inneholdende tre ekstra (if-)tester.
//     - 'Vokal', 'navnOK', 'allerede' og 'upcase' er nye funksjoner.

//   Programmet permuterer fullstendig en char-array (string/tekst),
//   men den kutter ut (avskj‘rer) n†r:
//     - ett tegn havner i en posisjon der et     ('allerede')
//       identisk tegn allerede har v‘rt.
//     - to LIKE vokaler kommer etter hverandre.        |
//     - tre vokaler kommer etter hverandre.            |
//     - tre LIKE konsonanter kommer etter hverandre.   |  ('navnOK'
//     - fire konsonanter kommer etter hverandre.       |   og 'vokal')
//     - to like bokstaver (vokaler eller konsonanter)  |
//       starter et ord.                                |


#include <iostream>                    //  cout
#include <cstring>                     //  strlen
#include <iomanip>                     //  setw
#include <cctype>                      //  toupper

using namespace std;


const int MAX = 16;                    //  Arrayens max.lengde (inkl '\0').
int N;                                 //  Arrayens aktuelle/n†v‘rende lengde.
int nr = 0;                            //  Permutasjonens fortl›pende nummer.
char arr[MAX];                         //  Global array av char'er (string).



bool vokal(char c)  {                   //  Sjekker om 'c' er en vokal.
  if (c == 'A'  ||  c == 'E'  ||  c == 'I'  ||  c == 'O'  ||  c == 'U'  ||
      c == 'Y'  ||  c == '’'  ||  c == ''  ||  c == '')  return true;
  else return false;
}
				       //  Sjekker om 'a' tilfredstiller
				       //  kravene beskrevet f›rst i filen.
bool navnOK(char a[], int i)  {      //  'i' vil max. v‘re 'N-1'.
  if (i == 1)  {                           //  Eksakt TO tegn lang:
     if (a[0] == a[1])  return false;      //  1e: To f›rste bokstaver er LIKE.
  } else if (i >= 2)  {                    //  MINST TRE tegn lang:
	  if (vokal(a[i]))  {             //  Nr. 'i' er en vokal:
		if (a[i] == a[i-1])  return false; //  1a: To LIKE vokaler
		                                   //  1b: Tre VOKALER:
		if (vokal(a[i-1])  &&  vokal(a[i-2]))  return false;
	  } else {                        //  Nr. 'i' er en konsonant:
                                           //  1c: Tre LIKE konsonanter:
        if (a[i] == a[i-1] &&  a[i] == a[i-2])  return false;
        if (i >= 3)  {                     //  MINST FIRE tegn lang:
			                               //  1d: FIRE konsonanter:
		  if (!vokal(a[i-1])  &&  !vokal(a[i-2])  &&  !vokal(a[i-3]))
			 return false;
		}
	  }
    }
  return true;
}

				       //  Sjekker etter om tegnet 'a[i]'
				       //      ogs† er † finne i arrayens
bool allerede(char a[], int i, int t)  {  //    intervall 'i+1'- 't'.
  for (int j = i+1;  j <= t; j++)
      if (a[i] == a[j])  return true;     //  Duplikater finnes.
  return false;                           //  Alt OK.
}


void upcase(char a[], int len)  {      //  Upcaser 'a' til bare STORE tegn.
  for (int i = 0;  i < len;  i++)
    if (a[i] == '‘')  a[i] =  '’';
    else if (a[i] == '›')  a[i] =  '';
    else if (a[i] == '†')  a[i] =  '';
    else                   a[i] = toupper(a[i]);
}


void display(char a[])  {              //  Viser arrayens innhold.
  char ch;
  cout << setw(3) << ++nr << ": ";     //  ker antall permutasjoner med 1.
  for (int i = 0;  i < N;  i ++)       //  Skriver EN l›sning/permutasjon:
    cout << a[i];
  cout << '\n';
  if (nr % 24 == 0)  {                 //  Stanser n†r skjermen er full:
     cout << "\t\t\t\tSkriv ett tegn .....";   cin >> ch;
  }
}


void bytt(char & a1, char & a2)  {     //  Bytter om to array-elementer.
  char aa = a1;
       a1 = a2;
       a2 = aa;
}


void roterVenstre(char a[], int i)  {  //  Roterer elementer mot venstre.
  char x;
  int k;
  x = a[i];                            //  Tar vare p† f›rste.
  for (k = i+1;  k < N;  k++)          //  Roterer:
    a[k-1] = a[k];
  a[N-1] = x;                          //  Legger f›rst inn bakerst.
}


void perm(int i)  {
  int t;

  if (i == N-1  &&  navnOK(arr, i))    //  N†dd en ny lovlig permutasjon:
     display(arr);                     //  Skriver ut arrayens innhold.
  else {                               //  Skal permutere:
     if (navnOK(arr, i))  perm(i+1);   //  Lovlig navn: Beholder n†v‘rende
				       //    nr.'i'. Permuterer resten.
     for (t = i+1; t < N; t++)  {
	   bytt(arr[i], arr[t]);       //  Bytter nr.'i' etter tur med alle
				                   //    de andre etterf›lgende.
				                   //  Lovlig navn, og den ombyttede har
				                   //    ikke en identisk som allerede
				                   //    har v‘rt p† denne plassen.
				                   //    For hvert av ombyttene: permuter
				                   //    resten av de N etterf›lgende:
	   if (!allerede(arr, i, t)  &&  navnOK(arr, i))
	      perm(i+1);
     }
     roterVenstre(arr, i);            //  Gjenoppretter opprinnelig array.
  }
}


int main()  {
                                       //  Leser inn aktuell tekst/string:
  cout << "Permutasjons-tekst (max.15 tegn):   ";
  cin.getline(arr, MAX);
  N = strlen(arr);                     //  Finner dens aktuelle lengde.
  upcase(arr, N);                      //  Lager om til kun STORE bokstaver.

  perm(0);                             //  Lager/skriver permutasjon av ALLE
 				                       //    tegnene/arrayelementene.
  return 0;
}
