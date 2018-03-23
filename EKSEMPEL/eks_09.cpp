//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_09.CPP

//  Eksemplet viser koden fra side 122 (og 26) i l�reboka.


//  Utskriftslinjene med 'Slutt: .....' er identiske med de p�
//      figur 9.4 s.123 i l�reboka.
//  Utskriftslinjene med 'Start: .....' viser (sub)arrayen F�R
//      selve partisjoneringen har blitt foretatt inni 'Quicksort'.


#include <iostream>

using namespace std;


const int LEN = 16;                    //  Tekstens max.lengde, inkl.'\0'.
char tekst[LEN] = "ASORTINGEXAMPLE";   //  Strengen som skal sorteres.

typedef int itemType;


class Stack  {               //  Avskrift av s.26 i l�reboka.
  private:
    itemType* stack;
    int p;
  public:
    Stack(int max = 100)
      {  stack = new itemType[max];  p = 0;  }
    ~Stack()
      {  delete [] stack;       }
    void push(itemType v)
      {  stack[p++] = v;     }
    itemType pop()
      {  return stack[--p];  }
    int empty()
      { return !p;           }
};


void swap(char a[], int i, int j)  {   //  Jfr. s.95 i l�reboka.
  char t = a[i];
       a[i] = a[j];
       a[j] = t;
}


void quicksort(char a[], int l, int r)  {   //  Jfr. s.122 i l�reboka.

  int i, j;  Stack sf(50);
  char v;
		   int k;         //  Hjelpevariabel for tegnutskrift.
		   int lnr = 0;   //  Teller opp linjenummer.
		   char ch;

  for ( ; ; )  {             //  Looper til breaker, fordi stack er tom:
      while (r > l)  {       //  Indeksene ikke passert hverandre:
	    v = a[r];            //  'v' = partisjonselementet.
	    i = l-1;  j = r;     //  Initierer begge til rett utenfor grensene
			                 //    av det omr�det som skal omflyttes.
			                 //  Skriver (sub)arrayen:
		   cout << "\n" << ++lnr << ")\tStart:\t\t";
		   for (k = l;  k <= r;  k++)  cout << a[k] << ' ';  cin >> ch;
	    for ( ; ; )  {       //  Looper til break'er ut.
		                 	 //  NB:  'i' og 'j' �kes/minskes F�R bruk.
			                 //       Derfor er de initiert utenfor grensene.
			                 //       De stopper dessuten p� de aktuelle
			                 //       indekser UTEN � "hoppe" en for langt.
		    while (a[++i] < v)  ; //  Looper til st�rre (eller lik) 'v'.
		    while (a[--j] > v)  ; //  Looper til mindre (eller lik) 'v'.
		    if (i >= j)  break;   //  Har passert hverandre:  break'er.
		    swap(a, i, j);        //  Bytter elementene 'i' og 'j'.
	    }
	    swap(a, i, r);       //  Smetter inn partisjonselementet p� plass 'i'.
			                 //  Skriver (sub)arrayen:
		   cout << "\n" << ++lnr << ")\t\tSlutt:\t";
		   for (k = l;  k <= r;  k++)  cout << a[k] << ' ';   cin >> ch;
			                 //  Lengste del/subarray legges p� stacken,
			                 //    omdefinerer grensene for det korteste:
	    if (i-l > r-i)       //  Venstre del er lengst:
	       {  sf.push(l);  sf.push(i-1);  l = i+1;  }
	    else                 //  H�yre del er lengst:
	       {  sf.push(i+1);  sf.push(r);  r = i-1;  }
      }
      if (sf.empty())  break;       //  Enn� noe igjen p� stacken ?
      r = sf.pop();  l = sf.pop();  //  Henter neste subarray fra stacken.
  }
}



int main()  {
  char ch;
  cout << "\n\nViser bruken av QUICKSORT (stack-versjon)";  cin >> ch;
  quicksort(tekst, 0, LEN-2);
  return 0;
}
