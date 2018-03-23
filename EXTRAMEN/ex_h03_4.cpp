//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H03_4.CPP

//     Løsningsforslag til eksamen i
//     "Algoritmiske metoder", oppgave nr.4, 12.desember 2003.

//     Laget av Frode Haug, HiG, desember 2003.


#include <iostream>     //  cout, cin
#include <cstring>      //  strlen
#include <cctype>       //  isalpha, toupper

using namespace std;


                        //  SELVE OPPGAVEN:
bool palindrom(char txt[], int start, int slutt)  {
                                        //  Suksessfullt "halveis" - palindrom:
  if (start >= slutt)           return true;
                                        //  Tegnet i 'start' skal hoppes over:
  if (!isalpha(txt[start]))     return palindrom(txt, start+1, slutt);
                                        //  Tegnet i 'slutt' skal hoppes over:
  if (!isalpha(txt[slutt]))     return palindrom(txt, start, slutt-1);
                                        //  Tegnene er ulike - IKKE palindrom:
  if (toupper(txt[start]) != toupper(txt[slutt])) return false;
                                        //  Sjekker bare neste par av tegn:
  return palindrom(txt, start+1, slutt-1);
}


int main()  {
  char tekst[80];
  cout << "Tekst:  ";  cin.getline(tekst, 80);

  cout << "\n\nDette er "
 	   << (!palindrom(tekst, 0, strlen(tekst)-1) ? "IKKE " : "")
       << "et palindrom!\n\n\n";
  return 0;
}
