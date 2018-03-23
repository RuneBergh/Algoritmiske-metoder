//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S95_5.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     august 1995, oppgave 5.

//     Laget av Frode Haug, HIG, sommeren 1995.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



//  Antall l›sninger maksimalt er:  3**8 = 6561


#include <iostream>          //  cout, cin
using namespace std;


const int LEN = 8;           //  Telefonnummerets lengde.
const int ANT = 3;           //  Antall bokstaver pr.siffer p† tastaturet.

char nummer[LEN+1];          //  Telefonnummeret.
char tekst[LEN+1];           //  Teksten som genereres etterhvert.
			     //  Bokstavene tilkoplet hvert siffer (0-9):
char bokstav[10][ANT+1] = { " ",  "ABC", "DEF", "GHI", "JKL", "MNO",
			    "PQR", "STU", "VWX", "YZ "};

			     //  Rekursiv funksjon som genererer tekster.
void lag_tekst(int n)  {     //  S›rger for at alle aktuelle tegn blir satt
			     //    inn p† plass nr.'n'.
  if (n < LEN)  {            //  Enn† ikke n†dd tekstens slutt:
			     //  'N' settes til antall tegn som skal byttes
			     //    ut p† plassen. Normalt ANT (3) stk,
			     //    men 1 dersom sifferet er '0':
     int N = (nummer[n] == '0')  ?  1  :  ANT;
			     //  G†r gjennom alle tegnene p† plass nr.'n':
     for (int i = 0; i < N;  i++)  {
       tekst[n] = bokstav[nummer[n]-'0'][i];   //  Fyller med aktuelt tegn.
       lag_tekst(n+1);       //  Ber neste tegn falle p† plass.
     }
  } else                     //  Teksten er ferdig generert:
    cout << tekst << '\n';   //  Skriver den ut.
}


int main()  {
   cout << "\n\n" << LEN << "-sifret telefonnummer:  ";
   cin.getline(nummer, LEN+1);    //  Leser tlf.nr. fra bruker.

   lag_tekst(0);                  //  Starter med sifferet med indeks nr.0.
   return 0;
}
