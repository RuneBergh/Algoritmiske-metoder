//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H01_4.CPP

//     L›sningsforslag til eksamen i
//     "Algoritmiske metoder I", oppgave nr.4, 11.desember 2001.

//     Laget av Frode Haug, HIG, desember 2001.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>          //  cout
using namespace std;

const int N = 10;            //  Max.lengde p† generert m›nster.

char monster[N];             //  Generert m›nster (med kun '*', '(' og ')' ).
int  pardybde = 0;           //  Antall '(' ift. ')' (dvs. parentesdybden).
int  n;                      //  Aktuell m›nsterlengde ( <= N ).


void display()  {
  for (int i = 0;  i < n;  i++)
      cout << monster[i];
  cout << '\n';
}

	     //  Genererer rekursivt alle mulige og lovlige m›nstre av '*',
	     //   '(' og ')',ved † pr›ve alle disse tegnene i posisjon nr.'i'.
void lag_monster(int i)  {   //  Sett alle mulige/lovlige tegn i monster[i].
  if (i == n)     //  Invariant: pardybde == 0, da har foretatt alle
     display();   //       avskj‘ringer underveis. Kan derfor trygt skrive ut.
  else  {

     if (pardybde < n-i)  {  //  Dersom nok plass til avsluttende ')'er,
        monster[i] = '*';    //    s† kan man sette inn enda en '*'.
        lag_monster(i+1);    //  Plasserer tegn i neste posisjon.
     }

     if (pardybde > 0)  {    //  Har hittil flere '(' enn ')'.
        monster[i] = ')';    //  Setter derfor inn enda en ')'.
        pardybde--;          //  "Parentesforskjellen" avtar med 1.
        lag_monster(i+1);    //  Plasserer tegn i neste posisjon.
        pardybde++;          //  Tilbakestiller "parentesforskjellen".
     }
			     //  Selv om setter inn enda en '(', s† er
     if (pardybde+1 < n-i)  { //   det nok plass til de avsluttende ')'er.
        monster[i] = '(';    //  Setter derfor inn enda en '('.
        pardybde++;          //  "Parentesforskjellen" ›ker med 1.
        lag_monster(i+1);    //  Plasserer tegn i neste posisjon.
        pardybde--;          //  Tilbakestiller "parentesforskjellen".
     }
  }
}


int main()  {
  do  {
    cout << "M›nsterlengde (0-" << N << "):  ";  cin >> n;
  } while (n < 0  ||  n > N);

  lag_monster(0);
  
  cout << '\n';
  return 0;
}
