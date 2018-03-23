//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H98_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     15.desember 1998, oppgave 3.

//     Laget av Frode Haug, HIG,  desember 1998.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



//  Grafen p†  EX_H98_3.DTA  ser ut som f›lger:
//           
//           
//     A ----------> F      
//     |  \         ^ \
//     |    \      /   \
//     |      v  /      v
//     v       C -----> E
//     B -----^|       ^ ^
//     | \     |     /   |
//     |   \   v  /      |
//     |     > D         |
//     |      ^          |
//     |    /            |
//     v  /              |
//     G -----------------


#include <iostream>      //  cin, cout
#include <fstream>       //  ifstream
#include <cstdlib>       //  exit

using namespace std;


const int N = 7;

struct Kant;       //  Predeklarasjon (da structene nedenfor refererer hverandre).


struct Node  {
    Kant* forste;   //  Den f›rste i en liste av utg†ende kanter.
    int   ant;      //  Hjelpe-variabel.
    char  ID;       //  Nodens id/navn  (en bokstav).
    Node(char id)  { ID = id; }
};


struct Kant  {
    Kant* neste;    //  Neste utg†ende kant. Er NULL om selv er siste kanten.
    Node* noden;    //  Noden som denne kanten g†r til.
    Kant(Node* nod, Kant* nes)  { noden = nod;  neste = nes;  }
};

  
Node* G[N+1];     //  Bruker indeks nr.1-N som peker til hver av de N nodene.
Node* S;


void opprett_graf();
void skriv_antallet();
void oppgave_3a();
void settant(Node* np);
    

int main()  {
  int i;
  char ch;

  opprett_graf();
  cout << "\nF›r oppgave 3a:\n";
  skriv_antallet();

  oppgave_3a();                                    //  Oppgave 3a
  cout << "\nEtter oppgave 3a:\n";
  skriv_antallet();
  cin >> ch;

  for (i = 1;  i <= N;  i++)      //  Nullstiller "ant" i alle nodene igjen.
      G[i]->ant = 0;
  cout << "\nF›r oppgave 3b:\n";
  skriv_antallet();
  S = G[1];      // Fra 'A' kan ALLE de andre n†s!
  settant(S);                                      //  Oppgave 3b
  cout << "\nEtter oppgave 3b:\n";
  skriv_antallet();
  cout << "\n\n";
  return 0;
}


void oppgave_3a()  {               //  OPPGAVE  3A
  int   i;
  Kant* kp;

  for (i = 1;  i <= N;  i++)      //  Nullstiller "ant" i alle nodene.
      G[i]->ant = 0;

  for (i = 1;  i <= N;  i++)      //  G†r gjennom alle noder. For hver av dem
                                  //    telles alle naboenes "ant" opp med 1.
     for ( kp = G[i]->forste;  kp != NULL;  kp = kp->neste )
         kp->noden->ant++;
}


                                   //  OPPGAVE  3B
void settant(Node* np)  {          //  Denne koden forutsetter (selvsagt)
  Kant * kp;                       //    at grafen er uten l›kker/sykler.

  for ( kp = np->forste;  kp != NULL;  kp = kp->neste )  {
      if (kp->noden->ant == 0)     //  For UNSEEN brukes: "ant" == 0. 
         settant(kp->noden);       //  Dybde-f›rst-s›k (rekursivt kall)
      kp->noden->ant++;            //  Teller opp nabonodens "ant".
  }
}
//  En annen variant, som vil virke selv om det er l›kker, til og med om
//  "S" er med i en l›kke, ville v‘re identisk til koden ovenfor, bare at
//  for-l›kkens innmat byttes med:
//
//      kp->noden->ant++;        //  Teller opp nabonodens "ant".
//                               //  Dersom 'jeg' er den f›rste som bes›ker
//                               //    denne naboen (dvs. "ant" ble NETTOPP
//                               //    telt opp til 1, og naboen IKKE er
//                               //    start-noden, DA bes›ker vi denne naboen:
//      if (kp->noden->ant == 1  &&  kp->noden != S) 
//         settant(kp->noden);


void opprett_graf()  {
  char id,                       //  En nodes ID.
       nabo;                     //  ID'en til "id"s naboer.
  int  i,                        //  L›kkevariabel.
       n,                        //  Antall utg†ende kanter fra noden "id".
       nr;                       //  En nodes ("id" eller "nabo") indeks i "G".
  Kant* kp;                      //  Hjelpepeker for † bygge opp kante-liste.
  ifstream inn("EX_H98_3.DTA");

  if (inn)  {
     for (i = 1;  i <= N;  i++)   //  G† gjennom og oppretter N tomme noder:
         G[i] = new Node(char('A'+i-1));

     inn >> id;                   //  Leser (om mulig) node-id (bokstav)
     while (!inn.eof()) {
       inn >> n;                  //  Leser antall kanter ut (naboer)
       kp = NULL;
       for (i = 1;  i <= n;  i++)  {    //  G†r gjennom alle naboene:
           inn >> nabo;                 //  Leser naboens id (bokstav)
           nr = int(nabo - 'A' + 1);    //  Finner naboens indeks/nr.
           kp = new Kant(G[nr], kp);    //  Ny kant forrest i kanteliste.
       }
       nr = int(id - 'A' + 1);    //  Finner nodens indeks/nr.
       G[nr]->forste = kp;         //  Hekter inn lista med utg†ende kanter.
                                  //  NB: G[nr].ant inneholder "s›ppel".
       inn >> id;                 //  Leser (om mulig) node-id (bokstav)
     }
  } else  {
     cout << "\n\nKlarer ikke † finne filen 'EX_H98_3.DTA'\n\n";
     exit(0);
  }

}


void skriv_antallet()  {
  Kant* kp;
  for (int i = 1;  i <= N;  i++)  {
     cout  <<  G[i]->ID  <<  ":  "  <<  G[i]->ant  <<  '\t';
     for ( kp = G[i]->forste;  kp != NULL;  kp = kp->neste )
         cout << "  " << kp->noden->ID;
     cout << '\n';
  }
}
