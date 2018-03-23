//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H12_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     18.desember 2012, oppgave nr.4.

//     Laget av Frode Haug, HiG, desember 2012.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
using namespace std;

const int N = 80;                      //  Tekstenes max.lengde.

                                       //  Er 'o2' et anagram av 'o1'?
bool anagram(char* o1, char* o2)  {
  char o22[N], *tt;                    //  Tekstkopi og matchende bokstavpeker.
  int n1 = strlen(o1), n2 = strlen(o2);  //  Tekstenes lengder.

  if (n2 < n1)  return false;          //  'o2' er kortere - anagram umulig.
                                       //  'o2' har lik eller lengre lengde:
  strcpy(o22, o2);                     //  Kopierer 'o2' til hjelpetekst.

  for (int i = 0;  i < n1;  i++)  {    //  G†r gjennom hele 'o1':
                                 //  Bokstav nr.'i' i 'o1' er IKKE i 'o22':
      if ((tt = strchr(o22, o1[i])) == NULL) return false;
      *tt = ' ';                 //  Tar vekk matchende/brukt bokstav (i 'o22').
  }
                    cout << "\n\t\t\t o22 etter:  -" << o22 << "-\n";
  return true;                   //  L›kke ferdig. Alle bokstaver funnet.
}



int main()  {
  char ord1[N], ord2[N], svar;

  do  {
    cout << "Ord nr.1:  ";   cin >> ord1;
    cout << "Ord nr.2:  ";   cin >> ord2;
    cout << '\n' << ((!anagram(ord1, ord2)) ? "IKKE " : "") << "ANAGRAM!";
    cout << "\n\n\nFlere ord (j/N)?  ";  cin >> svar;  cout << "\n\n";
  } while (svar == 'j'); 

  return 0;
}

