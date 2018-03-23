//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H09_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     21.desember 2009, oppgave nr.4.

//     Laget av Frode Haug, HiG, desember 2009.


#include <iostream>
using namespace std;

const int N = 20;

int tlf[N] = { 12345675, 12345676, 12345677, 12345678, 12345679,
               12345550, 12345551, 12345552, 12345553, 12345554,
               12345555, 12345556, 12345557, 12345558, 12345559,
               1234556,  1234557,  123456,   1234558,  1234559  };
//  Tredje siste element er prefiks av (flere) andre.


//  Metode 1 - Algoritme: 
//      Tar vekk ett og ett siffer bakfra i hvert tall.
//      Sjekker for hver gang at det "nye" tallet ikke er blant de andre i arrayen.

bool sjekk1()  {
  int i, j, tall;
  for (i = 0;  i < N-1;  i++)  {     //  G†r gjennom alle tallene (unntatt det siste):
      tall = tlf[i];                 //  Henter "orginaltallet".
      while (tall >= 100)  {         //  S† lenge minst tre siffer igjen:
        for (j = i+1;  j < N;  j++)  //  G†r gjennom ALLE de etterf›lgende tallene:
            if (tall == tlf[j]) return false;  //  Er tallene like? Returner da false.
       tall /= 10;                   //  Tar vekk bakerste siffer (dvs. deler med 10).
      }
  }
  return true;                       //  Alt gikk bra (ingen prefikser) - returner true.
}



//  Metode 2 - Algoritme: 
//      Sorterer f›rst (vha. en eller annen sorteringsmetode) alle tallene 
//      (gjort om til tekst) alfabetisk/leksikografisk.
//      Sjekker deretter at ingen tall er starten p† KUN det neste tallet i arrayen.

bool sjekk2() {
/*  NB:  Uferdig kode:

  sorter();     //  Bruker en av l‘reboka "sorteringssnutter", men gj›r
                //     om int'ene til tekst (vha. itoa(...)) f›r de sorteres.
  for (int i = 0;  i < N-1;  i++)
      if (!strncmp("itoa(tlf[i])", "itoa(tlf[i+1])", strlen("itoa(tlf[i])")) ) 
	     return false;
*/
  return true;
}


int main()   {
  cout << (sjekk1()? "": "IKKE ") << "OK\n\n"; 
  cout << (sjekk2()? "": "IKKE ") << "OK\n\n"; 
  return 0;
}
