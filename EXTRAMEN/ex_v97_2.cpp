//  Fil:  FRODEH \ ALG_METV \ EXTRAMEN \EX_V97_2.CPP

//     Lõsningsforslag til eksamen i "VideregÜende algoritmiske metoder",
//     3.mars 1997, oppgave 2.

//     Laget av Frode Haug, HIG,  mars 1997.
//     Litt endret/modifisert av FrodeH, HiG, hõsten 2003 og 2014.


#include  <iostream>
using namespace std;

const int N = 6;                    //  Antall noder.

struct node  {                      //  Node i grafen.
  node* etterfolger;                //  Nodens eneste etterfõlger (eller NULL).
  int merke;                        //  (UN)SEEN.  Bruker denne ikke !!!
  int id;                           //  Nodens id/navn.
  node()  {  etterfolger = NULL;   /* merke = 0; */  }    //  Constructor.
};

node* graf[N+1];                    //  Direkte peker til alle nodene.


void lag_noder()  {                 //  Lager nodene.
  for (int i = 1;  i <= N;  i++)
      {  graf[i] = new node;   graf[i]->id = i;  }
}

void lag_sirkel()  {                //  Bygger en graf som en sirkel:
  int i;
  node* p;
  graf[1]->etterfolger = graf[4];      //     1  -->  4  -->  5
  graf[4]->etterfolger = graf[5];      //     ^               |
  graf[5]->etterfolger = graf[3];      //     |               V
  graf[3]->etterfolger = graf[6];      //     2  <--  6  <--  3
  graf[6]->etterfolger = graf[2];
  graf[2]->etterfolger = graf[1];
  cout << "\nNodene i sirkelen:   ";
  for (i = 1, p = graf[1];  i <= N+1;  i++, p = p->etterfolger)
      cout <<  p->id << ((i <=N) ? " --> " : "");
}


void lag_rotrettet_tre()  {         //  Bygger en graf som et rotrettet tre:
  graf[3]->etterfolger = NULL;
  graf[6]->etterfolger = graf[3];      //              3
  graf[1]->etterfolger = graf[6];      //           /  |  \
  graf[2]->etterfolger = graf[3];      //          6   2   4
  graf[4]->etterfolger = graf[3];      //         /          \
  graf[5]->etterfolger = graf[4];      //        1            5
}

                //   En graf som er en eneste stor sirkel/sykel/lõkke
		//   har fõlgende karakteristiske egenskaper:
		//      - Alle noder har en etterfõlger
		//      - Starter man pÜ et tilfeldig punkt i sirkelen,
		//        sÜ vil man etter N steg forover vëre tilbake pÜ
		//        start-noden (og ingen noder er besõkt to ganger).
bool er_sirkel()  {
  node* p = graf[1]->etterfolger;   //  Initierer med en tilfeldig node:
  int ant = 1;
				    //  (Se egenskapene ovenfor:)
  while (p != NULL  &&  p != graf[1]  &&  ant < N)
	{  ant++;   p = p->etterfolger;  }
				    //  NÜdd akkurat tilbake pÜ N steg:
  return  (p == graf[1]   &&  ant == N);
}

                //   En graf som er et rotrettet tre har fõlgende
		//   karakteristiske egenskaper:
		//      - En og bare en node har en etterfõlger som er NULL.
		//      - Alle stier ender opp i denne noden.
		//        Dvs. det finnes ingen lõkker.
		//   (Merk at om det ikke finnes noen lõkker, sÜ Mè det
		//    vëre minst EN node med etterfõlger lik NULL.)
bool er_rotrettet_tre()  {
  node* p;
  int i, ant;
  bool rotsett = false;

  for (i = 1;  i <= N;  i++)  {     //  Kun EN node med etterfõlger lik NULL?
     p = graf[i];
     if (p->etterfolger == NULL)           //  Node med etterfõlger lik NULL:
	if (!rotsett)  rotsett = true;     //  FùRSTE noden som er slik.
	else return false;                 //  ANDRE noden som er slik: feil!
  }

  for (i = 1;  i <= N;  i++)  {     //  Prõver Ü finne lõkker, som etter
     p = graf[i];  ant = 1;         //    N steg IKKE har endt i rota:
     while (p->etterfolger != NULL)  {    //  Blar gjennom EN "kjede":
       if (ant == N)  return false;       //  N steg, UTEN Ü finne rota: feil!
       p = p->etterfolger;  ant++;        //  Blar evnt. videre i kjeden.
     }
  }
  return true;
}


int main()  {
  lag_noder();

  lag_sirkel();
  cout << "\n\nGrafen er ";
  if (!er_sirkel())  cout << "IKKE ";
  cout << "en eneste STOR sirkel/cykel/lõkke.";

  lag_rotrettet_tre();
  cout << "\n\n\n\nGrafen er ";
  if (!er_rotrettet_tre())  cout << "IKKE ";
  cout << "et rotrettet tre.\n\n\n";

  return 0;
}
