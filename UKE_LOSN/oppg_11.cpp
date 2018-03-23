//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_11.CPP

//   L›sningsforslag til oppgave nr.11  i  Algoritmiske metoder.


//   Programmet pr›ver † hoppe rundt med en hest p† et NxN sjakkbrett.
//   Hesten skal innom ALLE feltene/rutene EN og BARE EN gang.
//   (En hest hopper ENTEN en frem og to til siden ELLER to frem
//   og en til siden.)


#include <iostream>          //  cout, cin
#include <iomanip>           //  setw

using namespace std;


const int MAX = 8;           //  Max. st›rrelse p† sjakkbrettet.

int N;                       //  N x N  av brettet blir brukt/analysert.
int brett[MAX+1][MAX+1];     //  Sjakkbrettet. Bruker 1-N i begge retninger.
			                 //    Hele brettet blir automatisk satt til '0'.
int ant = 0;                 //  Teller opp antall l›sninger.

void display()  {            //  Skriver ut brettets innhold.
  int i, j;
  char ch;

  cout << "\n\n\nL›sning nr." << ++ant << ":\n\t";

  for (i = 1;  i <= N;  i++)  {
      for (j = 1;  j <= N;  j++)
   	      cout << setw(4) << brett[i][j];
      cout << "\n\t";
  }
  cout << "\t\t\tSkriv ett tegn .....";  //  cin >> ch;
}

			     //  Ved hopp nr.'nr' s† fors›kes det †
			     //    plassere hesten i posisjon [i][j].
void hoppHest(int i, int j, int nr)  {

  if ((i >= 1  &&  i <= N  &&  j >= 1  &&  j <= N)  &&
     brett[i][j] == 0)  {    //  Inne p† brettet og posisjonen er ledig:
       brett[i][j] = nr;     //  Setter ruten opptatt med hopp nr.'nr'.
       if (nr == N*N)        //  Dette var det siste hoppet:
	      display();         //  Viser en l›sning.
       else  {               //  Det m† hoppes til flere ruter/felt:
	      hoppHest(i+1, j+2, nr+1);   //  Pr›ver hopp i alle †tte retninger:
	      hoppHest(i+1, j-2, nr+1);
	      hoppHest(i-1, j+2, nr+1);
	      hoppHest(i-1, j-2, nr+1);
	      hoppHest(i+2, j+1, nr+1);
	      hoppHest(i+2, j-1, nr+1);
	      hoppHest(i-2, j+1, nr+1);
	      hoppHest(i-2, j-1, nr+1);
       }
       brett[i][j] = 0;      //  Frigir ruten igjen.
  }
}


// ************************   HOVEDPROGRAM:   *****************************

int main()  {
  int x, y;

  do  {                      // Leser spillebrettets st›rrelse:
    cout << "Spillets st›rrelse (1-" << MAX << "):  ";
    cin >> N;
  } while (N < 1  ||  N > MAX);

  do  {                      //  Leser startposisjon (x- og y-koordinat):
    cout << "Startposisjon (x og y):  ";
    cin >> x >> y;
  } while (x < 1  ||  x > N  ||  y < 1  ||  y > N);

  hoppHest(x, y, 1);        //  Finner l›sninger ?

  if (ant == 0)              //  Ingen l›sninger funnet.
     cout << "\n\nINGEN LSNINGER !";
  cout << "\n\n";
  return 0;
}
