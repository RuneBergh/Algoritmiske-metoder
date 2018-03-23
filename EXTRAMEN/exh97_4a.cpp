//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EXH97_4A.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     18.desember 1997, oppgave 4A.

//     Laget av Frode Haug, HIG,  desember 1997.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


			//  INCLUDE:
#include <iostream>          //  cout, cin
using namespace std;

			//  CONST:
const int  ANT_TEGN    = 4;   //  Antall ulike aritmetiske tegn:  +, -, *, /
const int  ANT_POS     = 4;   //  Antall ulike posisjoner † plassere tegn i.
const int  TOT_TEGN    = 5;   //  Tegn i ETT uttrykk (3 operander, 2 operatorer)
const int  TOT_UTTRYKK = 4;   //  Antall ulike vann-/loddrette regneuttrykk.
const int  plass[TOT_UTTRYKK][ANT_POS/2]  = { {0,1}, {2,3}, {0,2}, {1,3} };
const char tegn[ANT_TEGN]                 = { '+', '-', '*', '/' };

			//  GLOBAL VARIABEL:
char uttrykk[TOT_UTTRYKK][TOT_TEGN] =	 { { '6', ' ', '4', ' ', '2'},
					   { '9', ' ', '2', ' ', '5'},
					   { '7', ' ', '3', ' ', '9'},
					   { '8', ' ', '2', ' ', '8'} };
int sum[TOT_UTTRYKK];         // Verdien til hvert enkelt uttrykk.

int losning()  {
  int i, j;
  for (i = 0; i < TOT_UTTRYKK;  i++)  {   //  G†r gjennom alle regneuttrykkene:
      sum[i] = 0;                         //  Nullstiller svaret/summen.
      for (j = 0; j < TOT_TEGN;  j++)     //  For hvert tegn i uttrykket:
	  if (j == 0)  sum[i] = uttrykk[i][j] - '0';  //  1.tallet.
	  else if (j == 2  ||  j == 4)  {             //  2. og 3.tallet:
	     switch (uttrykk[i][j-1])  {    //  Ut fra FORRIGE operator ("j-1"):
	       case '+': sum[i] += (uttrykk[i][j] - '0');  break;
	       case '-': sum[i] -= (uttrykk[i][j] - '0');  break;
	       case '*': sum[i] *= (uttrykk[i][j] - '0');  break;
	       case '/': sum[i] /= (uttrykk[i][j] - '0');  break;
	     }
	  }
  }		       //  LSNING FUNNET:
  return (sum[0] == sum[1]  &&  sum[1] == sum[2]  &&  sum[2] == sum[3]);
}


void display()  {      //  Skriver ut n†v‘rende innhold i alle regneuttrykkene.
  int k, l;
  char ch;
  cout << "\n\n";
  for (k = 0; k < TOT_UTTRYKK;  k++)  {
      cout << "\n\t";
      for (l = 0; l < TOT_TEGN;  l++)
	  cout << uttrykk[k][l] << "  ";
      cout << "=  " << sum[k];
  }
  cin >> ch;
}

			  // Setter etter tur inn alle mulige aritmetiske
void generer(int n)   {   //   tegn (fire stk.) i posisjon nr."n".
  int i, j;
  for (i = 0;  i < ANT_TEGN;  i++)  {        // G†r gjennom alle tegn:
      for (j = 0;  j < TOT_UTTRYKK;  j++)  { // Finner uttrykkene der "n" er:
	  if      (plass[j][0] == n)  uttrykk[j][1] = tegn[i];
	  else if (plass[j][1] == n)  uttrykk[j][3] = tegn[i];
      }
      if (n < ANT_POS-1)  generer(n+1);      //  Om flere tegn plasseres: kall.
      else if (losning()) display();         //  Dersom l›sning: skriv ut.
  }
}

			//  HOVEDPROGRAM:
int main()  {
  generer(0);
  cout << "\n\n";
  return 0;
}

