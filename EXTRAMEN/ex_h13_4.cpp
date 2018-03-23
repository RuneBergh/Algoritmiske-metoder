//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H13_4.CPP

//     Løsningsforslag til eksamen i "Algoritmiske metoder",
//     18.desember 2013, oppgave nr.4.

//     Laget av Frode Haug, HiG, desember 2013.


#include <iostream>
#include <cstring>
using namespace std;

const int LEN = 9;
const int N   = 8;

//  Brukes for å teste  prefixA:
char txt0[N][LEN] =  { "0403", "05043", "05047",  "113", "1143", "11612345", "11812345", "62529903" };
char txt1[N][LEN] =  { "0403", "05043", "05047",  "113", "1134", "11612345", "11812345", "62529903" };
char txt2[N][LEN] =  { "0403", "05043", "050437", "113", "1143", "11612345", "11812345", "62529903" };

//  Brukes for å teste  prefixB:
int  num[][N] =  {{ 113, 403, 1143, 5043, 5047,  11612345, 11812345, 62529903 },
                  { 113, 403, 1134, 5043, 5047,  11612345, 11812345, 62529903 },
                  { 113, 403, 1143, 5043, 50437, 11612345, 11812345, 62529903 }};

//  Brukes for å teste  prefixC:
char txt3[N][LEN] =  { "113", "0403", "1143", "05043", "05047",  "11612345", "11812345", "62529903" };
char txt4[N][LEN] =  { "113", "0403", "1134", "05043", "05047",  "11612345", "11812345", "62529903" };
char txt5[N][LEN] =  { "113", "0403", "1143", "05043", "050437", "11612345", "11812345", "62529903" };



// *************************************************************************************
//  Alternativ A:
//     Datatype:    char'er (tekster/strenger)
//     Sortering:   Lexicografisk/alfabetisk sortert (som tekst)
//     Metode:      Sjekk om nr.'i' er et prefiks av nr.'i+1'
// *************************************************************************************

bool prefixA(char t[N][LEN])  {
  for (int i = 0;  i < N-1;  i++)  {                //  Går gjennom arrayen:
      if (!strncmp(t[i], t[i+1], strlen(t[i]))) {   //  Er prefiks av NESTE verdi?
         cout << "\t\t" << t[i] << " er et prefiks av " << t[i+1] << '\n';
         return true;                               //  "Ja" - returner true.
      }
  }        
  return false;     //  Loop gått ferdig. Ingen prefikser funnet. Returner false.
}



// *************************************************************************************
//  Alternativ B:
//     Mer "selvsagt" metode(?) enn A, men litt mer kode/tuklete.
//     Datatype:    int'er
//     Sortering:   Numerisk 
//     Metode:      Ta vekk ett og ett siffer bakfra i nr.'i'. For hver gang,
//                  sjekke om "det nye tallet" forekommer i intervallet 'i-1' ned til 1.
// *************************************************************************************

bool prefixB(int n[N])  {
  int i, j, tall;                    //  Løkkevariable og sammenligningstall.
  for (i = N-1; i > 0;  i--)  {      //  Går fra største/lengste og ned til minste/kortest.
      tall = n[i];                   //  Initierer med orginalt tall.
      while (tall > 0)  {            //  Sålenge sifre igjen i tallet:
        for (j = i-1; j >= 0;  j--)  //  Går gjennom alle tall FØR i arrayen:
            if (tall == n[j])  {     //  Er prefiks av tallet?
               cout << "\t\t" << n[j] << " er et prefiks av " << n[i] << '\n';
               return true;          //  "Ja" - returner true.
             }
        tall /= 10;                  //  Tar bort bakerste/siste siffer.
      }
  }  
  return false;           //  Loop gått ferdig. Ingen prefikser funnet. Returner false.
}



// *************************************************************************************
//  Alternativ C:
//     Datatype:    char'er (tekster/strenger)
//     Sortering:   Primært sortert etter stigende tekstlengde. Sekundært er de med samme
//                  lengde innbyrdes alfabetisk/lexicografisk/numerisk sortert stigende.
//     Metode:      Sjekk om nr.'i' er et prefiks av nr.'i+1' til 'N-1'.
// *************************************************************************************

bool prefixC(char t[N][LEN])  {
  int i, j;
  for (i = 0;  i < N-1;  i++)  {                    //  Går gjennom arrayen:
	  for (j = i+1;  j <= N-1;  j++)
      if (!strncmp(t[i], t[j], strlen(t[i])))  {    //  Er prefiks av en av ALLE de neste?
         cout << "\t\t" << t[i] << " er et prefiks av " << t[j] << '\n';
         return true;                               //  "Ja" - returner true.
      }
  }        
  return false;     //  Loop gått ferdig. Ingen prefikser funnet. Returner false.
}





int main()  {
  cout << "txt0 er " << ((prefixA(txt0)) ? "IKKE " : "") << "OK\n\n";
  cout << "txt1 er " << ((prefixA(txt1)) ? "IKKE " : "") << "OK\n\n";
  cout << "txt2 er " << ((prefixA(txt2)) ? "IKKE " : "") << "OK\n\n";
  cout << "\n\n";
  cout << "num[0] er " << ((prefixB(num[0])) ? "IKKE " : "") << "OK\n\n";
  cout << "num[1] er " << ((prefixB(num[1])) ? "IKKE " : "") << "OK\n\n";
  cout << "num[2] er " << ((prefixB(num[2])) ? "IKKE " : "") << "OK\n\n";
  cout << "\n\n";
  cout << "txt3 er " << ((prefixC(txt3)) ? "IKKE " : "") << "OK\n\n";
  cout << "txt4 er " << ((prefixC(txt4)) ? "IKKE " : "") << "OK\n\n";
  cout << "txt5 er " << ((prefixC(txt5)) ? "IKKE " : "") << "OK\n\n";
  cout << "\n\n";
  return 0;
}
