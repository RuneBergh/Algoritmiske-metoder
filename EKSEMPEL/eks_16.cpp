//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_16.CPP

//  Eksemplet viser to ulike Union-Find algoritmer.
//  Dette er en ren avskrift av koden s.444 og 447 i l‘reboka.
//  Utskriften fra programmet blir figurene  30.6  og  30.9.


#include <iostream>          //  cout
#include <fstream>           //  ifstream
#include <iomanip>           //  setw

using namespace std;


const int  MAX = 14;         //  Nodene har "ID" lik  'A'-'M'  (1-13).


class EQ  {                  //  Klassen "Equivalence".
 private:
   int* dad;                 //  Faren ('dad') til hver node.
   int len;                  //  Antall noder i grafen.

 public:
   EQ(int size)  {           //  Initierer 'dad':
     len = size;  dad = new int[size];
     for (int i = 0;  i < size;  i++)   dad[i] = 0;
   }
   int  find(int x, int y, int doit);
   int  find2(int x, int y, int doit);
   void display();
};


int EQ ::  find(int x, int y, int doit)  {     //  Jfr.s.444 i l‘reboka.
  int i = x,  j = y;
  while (dad[i] > 0)  i = dad[i];              //  Finner i's rot.
  while (dad[j] > 0)  j = dad[j];              //  Finner j's rot.
  if (doit  &&  (i != j))  dad[j] = i;         //  Hekter sammen.
  return (i != j);                             //  Returnerer 0, dersom i
}                                              //     samme komponent.


int EQ ::  find2(int x, int y, int doit)  {    //  Jfr.s.447 i l‘reboka.
  int t, i = x,  j = y;
  while (dad[i] > 0)  i = dad[i];	           //  Finner i's rot.
  while (dad[j] > 0)  j = dad[j];	           //  Finner j's rot.
  while (dad[x] > 0)                           //  G†r opp gjennom treet fra
    {  t = x;  x = dad[x];  dad[t] = i;  }     //    i og j en gang til og
  while (dad[y] > 0)                           //    setter alle p† veien opp
    {  t = y;  y = dad[y];  dad[t] = j;  }     //    til † referere rota.
  if (doit  &&  (i != j))                          //  Skal hekte sammen:
     if (dad[j] < dad[i])                          //  J's tre er st›rst:
	    {  dad[j] += dad[i] - 1;  dad[i] = j;  }   //  Hekter i under j.
     else                                          //  I's tre er st›rst:
	    {  dad[i] += dad[j] - 1;  dad[j] = i;  }   //  Hekter j under i.
  return (i != j);
}


void EQ :: display()  {                //  Skriver ut dad's innhold:
  int i;
  cout << '\n';  for (i = 1;  i < len;  i++)   //  Lager linje med bokstaver
                     cout << setw(3) << char(i+'A'-1);
  cout << '\n';  for (i = 1;  i < len;  i++)
		  if (dad[i] > 0   )           //  Inneholder bokstav:
			cout << setw(3) << char(dad[i]+'A'-1);
		  else if (dad[i] == 0)        //  Hittil ubrukt:
			cout << "  -";
		  else                         //  Er rot for -(dad[i]) noder:
			cout << setw(3) << (-dad[i]);
}


int main()  {
  char type;                         //  Teste teste find eller find2.
  char cxx, cyy;                     //  Bokstavene lest fra fil (A-Z).
  char ch;
  int  xx, yy;                       //  Bokstavens nummer i alfabetet (1-26).
  ifstream innfil("EKS_16.DTA");     //  Tilknytter og †pner fil.
  EQ eq(MAX);                        //  Equivalence-objekt.

  cout << "Teste Enkel eller Avansert 'find' (E, A):  ";  cin >> type;

  innfil >> cxx;                     //  Leser (om mulig) ett tegn (fra-node).
  while (innfil)  {
     innfil >> cyy;                  //  Leser neste tegn (til-node).
     xx = cxx-'A'+1;   yy = cyy-'A'+1;     //  = "index": fra char til tall.
     if (type == 'E')                //  Teste "enkel" s.444 i l‘reboka:
        eq.find(xx, yy, 1);
     else                            //  Teste "avansert" s.447 i l‘reboka:
	    eq.find2(xx, yy, 1);

     cout << "\n\n" << cxx << ' ' << cyy << ':';    // Skriver nodenes navn.
     eq.display();   cin >> ch;      //  Skriver ut 'dad's innhold.

     innfil >> cxx;                  //  Leser (om mulig) ett tegn (fra-node).
  }
  return 0;
}
