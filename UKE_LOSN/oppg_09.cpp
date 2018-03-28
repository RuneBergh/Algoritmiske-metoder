//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_09.CPP

//   L�sningsforslag til oppgave nr.9  i  Algoritmiske metoder.


//   Programmet pr�ver � plassere N sjakk-dronninger p� et NxN brett.
//   Dvs. to dronninger kan hverken st� p� samme linje (i), kolonne (j)
//   eller diagonal, ellers "sl�r/tar" de hverandre.
//
//   Programmet siler IKKE vekk l�sninger som egentlig er funnet 
//   tidligere, n�r det som synes � v�re en "ny" l�sning egentlig er en:
//      - speiling om horisontal/vertikal midtlinje   og/eller
//      - speiling om hoved-/bidiagonal (mellom motsatte hj�rner)   og/eller
//      - rotasjon (f.eks. MED klokka) p� 90, 180 eller 270 grader
//   av den allerede fundne l�sningen.
//   Dette medf�rer at for et 8x8 brett s� vil programmet angi 92 l�sninger,
//   n�r det egentlig bare er 12 UNIKE l�sninger. (For f�lgende NxN brett
//   blir det X ikke-unike l�sninger:  4: 2,   5: 10,   6: 4,   7: 40.)
//
//
//
//  ALTERNATIV L�SNING:
//     Problemet kunne ogs� ha v�rt l�st ved permutasjon av sifrene 1 til N.
//     Indeksen/elementnummeret vil dermed angi kolonnenummer, mens sifferet
//     som st�r p� den aktuelle plassen vil angi linjenummeret. Dermed 
//     slipper man � teste p� om to dronninger st�r p� samme linje (s� lenge
//     alle sifrene i utgangspunktet er unike). 
//     Avskj�ringene ovenfor (speilinger/rotasjoner) kunne ha v�rt ivaretatt 
//     ved � utf�re ulike transformasjoner p� den permuterte arrayen. Dersom
//     en ny array som s�ledes fremkommer totalt utgj�r et tall som er mindre
//     enn den permuterte arrayens tall, s� har man allerede funnet (og 
//     skrevet ut) denne l�sningen tidligere.



#include <iostream>          //  cout, cin

using namespace std;


const int MAX = 8;           //  Max. st�rrelse p� sjakkbrettet. 

int N;                       //  N x N  av brettet blir brukt/analysert. 
int brett[MAX+1][MAX+1];     //  Sjakkbrettet. Bruker 1-N i begge retninger.
			                 //    Hele brettet blir automatisk satt til '0'. 
int ant = 0;                 //  Teller opp antallet l�sninger.



void display()  {            //  Skriver ut brettets innhold.
  int i, j;
  char ch;

  cout << "\n\n\nLsning nr." << ++ant << ":\n\t";

  for (i = 1;  i <= N;  i++)  {
      for (j = 1;  j <= N;  j++)
	  cout << brett[i][j] << "  ";
      cout << "\n\t";
  }
  cout << "\t\t\tSkriv ett tegn .....";   cin >> ch;
}

			     //  Sjekker om en dronning kan plasseres i
			     //    posisjon [linje][kolonne]. Dette gj�res
			     //    ved � teste om det allerede st�r et '1'-
			     //    tall p� vedkommende linje eller en av
			     //    diagonalene til venstre.
bool lovligPos(int linje, int kolonne)  {
  int i;                                 

  for (i = 1;  i < kolonne;  i++)           //  Sjekker om noen annen brikke:
      if (brett[linje][i] == 1)  return false;  //    - p� samme linje:

  for (i = kolonne-1;  i >= 1;  i--)  {     //    - p� en av diagonalene:
      if (linje - (kolonne-i) >= 1)         //  Dersom inne p� brettet:
	     if (brett[linje-(kolonne-i)][i] == 1)  //  Opptatt p� diagonal
	        return false;                       //    OPP til venstre.
      if (linje + (kolonne-i) <= N)         //  Dersom inne p� brettet:
	     if (brett[linje+(kolonne-i)][i] == 1)  //  Opptatt p� diagonal
	        return false;                       //    NED til venstre.
  }
  return true;                              //  Alt OK.
}

			     //  Pr�ver � plassere en dronning etter tur i
			     //    ALLE lovlige posisjoner p� kolonne 'j'.
void settDronning(int j)  {
  int i;
  if (j == N+1)              //  Brettet er fullt, dvs. n�dd en l�sning.
     display();              //  Skriver/tegner l�sningen.
  else
     for (i = 1;  i <= N;  i++)    // G�r gjennom alle linjene p� kolonnen:
				                          //  1.kolonne eller lov � plassere:
	 if (j == 1  ||  lovligPos(i, j))  {
	    brett[i][j] = 1;       //  Setter posisjonen som opptatt.
	    settDronning(j+1);     //  Plasserer dronning p� neste kolonne.
	    brett[i][j] = 0;       //  Frigir posisjonen.
	 }
}


// ************************   HOVEDPROGRAM:   *****************************

int main()  {
  do  {                            // Leser spillebrettets st�rrelse:
    cout << "Spillets strrelse (1-" << MAX << "):  ";
    cin >> N;
  } while (N < 1  ||  N > MAX);

  settDronning(1);                //  Finner l�sninger ?

  if (ant == 0)                    //  Ingen l�sninger funnet.
     cout << "\n\nINGEN LSNINGER !";
  cout << "\n\n";
  return 0;
}
