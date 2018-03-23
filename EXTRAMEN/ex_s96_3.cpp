//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S96_3.CPP

//     L›sningsforslag til kontinuasjonseksamen i
//     "Algoritmiske metoder", oppgave nr.3, september 1996.

//     Laget av Frode Haug,  HIG,  september 1996.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


//  A)        Koden fra sidene 95 og 109 i l‘reboka.
//            NB:  Har lagt inn ' ' (blank) i element nr.0.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 


#include <iostream>          //  cout
#include <cstring>           //  strcpy

using namespace std;


const int LEN = 16;          //  Tekstens max.lengde, inkl.'\0'.
char tekst[LEN];             //  Streng med bokstavene som skal sorteres.

typedef char itemType;


void fyll_array()
  {  strcpy(tekst, " TANNREGULERING");  }


void swap(itemType a[], int i, int j)  {    //  Jfr. s.95 i l‘reboka.
  itemType    t = a[i];
	   a[i] = a[j];
	   a[j] = t;
}


void shellsort(itemType a[], int N)  {      //  Jfr. s.109 i l‘reboka.
  int i, j, h;   itemType v;
  char ch;

  for (h = 1;  h <= N/9;  h = 3*h + 1)   ;  //   15/9 = 1,  dvs: h = 4
  for (  ;  h > 0;  h /= 3)                       {
      for (i = h+1;  i < N;  i++)  {
	  v = a[i];  j = i;
	  while ( j > h  &&  a[j-h] > v)  {
		a[j] = a[j-h];
		j -= h;
	  }
	  a[j] = v;
			    cout << "\nH: " << h << "  I: " << i << '\t' << a;
			    cin >> ch;
      }
			    cout << "\n\nH = " << h << " er ferdig !!\n\n";
			    cin >> ch;
						  }
}


int main()  {
  char ch;
  cout << "\n\nKontinuasjonseksamen september 1996, oppgave 3a:";   cin >> ch;
  fyll_array();
  shellsort(tekst, LEN-1);
  return 0;
}


/*
  B)  Insert 'T':     T 
	  Insert 'A':     T A 
	  Insert 'N':     T A N 
	  Insert 'N':     T N N A 
	  Insert 'R':     T R N A N 
	  Insert 'E':     T R N A N E 
	  Insert 'G':     T R N A N E G 
	  Insert 'U':     U T N R N E G A 
	  Insert 'L':     U T N R N E G A L 
	  Insert 'E':     U T N R N E G A L E 
	  Insert 'R':     U T N R R E G A L E N 
	  Insert 'I':     U T N R R I G A L E N E 
	  Insert 'N':     U T N R R N G A L E N E I 
	  Insert 'G':     U T N R R N G A L E N E I G 



  C)  Vha. "EKS_14.CPP", der filen "EKS_1415.DTA" inneholder:
		A D 7
		A E 6
		A F 4
		B C 6
		B D 4
		B F 6
		C E 4
		C F 7
		D F 7
		E F 6

	f†r vi f›lgende innhold i prioritetsk›en etterhvert:

                     B6
		      F4     E6     D4
		      E6     C7     C6     C6
	   A*     D7     D7     E6     E6     E4


	Minimums-spenntre blir:      A
	                               \      E
                                     F    |
							    D    |    C
                                 \-- B --/
*/
