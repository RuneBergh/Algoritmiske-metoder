//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S96_5.CPP

//     L›sningsforslag til kontinuasjonseksamen i
//     "Algoritmiske metoder", oppgave nr.5, september 1996.

//     Laget av Frode Haug,  HIG,  september 1996.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


//   L›sningen baserer seg p† EKS_06.CPP, men noe endret.

//   Programmet permuterer fullstendig en int-array, men den avskj‘rer n†r:
//       -


#include <iostream>                    //  cout
using namespace std;

const int N = 9;                               //  Arrayens max.lengde.
int arr[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9  };   //  Global array av int'er.


void kanskje_losning(int a[])  {      //  Viser muligens arrayens innhold.
   int ab, c, de, f, ghi;
   ab  = a[0]*10 + a[1];              //  Regner ut regneutrykkets elementer:
   c   = a[2];
   de  = a[3]*10 + a[4];
   f   = a[5];
   ghi = (a[6]*100) + a[7]*10+ a[8];

   if ((ab*c == de*f)  &&  (ab*c == ghi))  {  // Beregner HELE uttrykket:
      cout << "\n\t" << ab << " * " << c << "  =  " << de << " * " << f
	   << "  =  "  << ghi;
   }
}


bool tall_ok(int a[], int n)  {
   int ab, c, de, f;
   if (n == 4)  {                  //  5 f›rste tall er generert:
      ab  = a[0]*10 + a[1];
      de  = a[3]*10 + a[4];
      if (ab > de)   return false; //  Funnet l›sningen f›r ?
      c  = a[2];
      if (ab*c < de) return false; //  Kan ALDRI bli like ?
   }
   if (n == 5)  {                  //  6 f›rste tall er generert:
      ab  = a[0]*10 + a[1];   c  = a[2];
      de  = a[3]*10 + a[4];   f  = a[5];
      if (ab*c  !=  de*f)  return false;    //  To f›rste produkt ikke like ?
   }
   return true;
}


void bytt(int & a1, int & a2)  {     //  Bytter om to array-elementer.
  int  aa = a1;
       a1 = a2;
       a2 = aa;
}


void roter_venstre(int a[], int i)  { //  Roterer elementer mot venstre.
  int x, k;
  x = a[i];                            //  Tar vare p† f›rste.
  for (k = i+1;  k < N;  k++)          //  Roterer:
    a[k-1] = a[k];
  a[N-1] = x;                          //  Legger f›rst inn bakerst.
}


void perm(int i)  {
  int t;

  if (i == N-1) kanskje_losning(arr);  //  N†dd en ny lovlig permutasjon ?
  else {                               //  Skal permutere:
     if (tall_ok(arr, i))  perm(i+1);  //  Lovlig stykke: Beholder n†v‘rende
				       //    nr.'i'. Permuterer resten.
     for (t = i+1; t < N; t++)  {
	   bytt(arr[i], arr[t]);       //  Bytter nr.'i' etter tur med alle
				       //    de andre etterf›lgende.
				       //  Lovlig regnestykke hittil.
				       //    For hvert av ombyttene: permuter
				       //    resten av de N etterf›lgende:
	   if (tall_ok(arr, i))  perm(i+1);
     }
     roter_venstre(arr, i);            //  Gjenoppretter opprinnelig array.
  }
}


int main()  {
  perm(0);                             //  Lager/skriver l›sninger.
  cout << "\n\nFerdig!\n\n";
  return 0;
}
