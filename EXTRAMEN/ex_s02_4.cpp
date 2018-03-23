//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S02_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     15.august 2002, oppgave 4.

//     Laget av Frode Haug, HiG, august 2002.
//     Litt endret/modifisert i ettertid av FrodeH, HiG.


/*
   OPPGAVE A - Del 2:
   ==================
     Tidsforbruket (se koden for "visit" og "skriv_TAK"):
         F›rst g†r vi gjennom og setter alle merker ( O(V) ).
         Deretter gj›r vi et dybde-f›rst-s›k fra denne noden (max. antall
         kanter: O(E) ). Alt dette gj›res for hver av de V nodene.
         Helt korrekt vil tiden da bli:  O(V * (E + V)).
                                         --------------
         Vanligvis vil E v‘re s†pass mye st›rre enn V at dette kan
         avrundes til:  O(V * E)
                        --------



   OPPGAVE B:
   ==========
     A er med i BÅDE TA-kjernen og FA-kjernen:
         Dette betyr at det finnes en vei fra hver node til A og fra A til
         hver av de andre nodene. Dermed er det ogs† slik at det (via A)
         finnes en vei mellom ALLE par av noder i grafen.
         Dermed skj›nner vi at b†de TA-kjernen og FA-kjernen vil omfatte
         ALLE nodene i grafen!

     Grafen er l›kkefri/uten cykler:
         For en slik graf vil TA-kjernen inneholde maksimalt ETT element
         (men kan ogs† v‘re tom). Om vi antar at det var TO noder (X og Y)
         i TA-kjernen, ville det ha g†tt en rettet vei fra X til Y, og en
         rettet vei fra Y til X. Dermed ville grafen ha inneholdt en l›kke!
         Et helt tilsvarende resonnement kan f›res for at FA-kjernen kan ha
         maksimalt ETT element i en rettet l›kkefri graf.

*/

			//  INCLUDE:
#include <iostream>          //  cout, cin
using namespace std;


const int  UNSEEN = 0;
const int  SEEN   = 1;


struct node  {
  char id;         //  Nodens ID/navn.
  int  ant_naboer; //  Antall reelle naboer (et tall mellom 0 og 10 stk.).
  node* nabo[11];  //  Peker til naboene. Vi antar at 10 stk. holder!
  int  merke;      //  1 eller 0, alt ettersom om noden er SEEN/UNSEEN.
  node (char i, int a)  {  id = i;  ant_naboer = a;  }
};

node* G[101];      //  Direkte peker til alle nodene i grafen.
int V;             //  Aktuelt antall noder i grafen.

void lag_graf1();  //  Deklarasjon av to funksjoner som
void lag_graf2();  //    bygger opp to ulike grafer.



//                        OPPGAVE A - Del 1:
//                        ==================
int antsett;                  //  Antall noder sett i dybde-f›rst-s›ket.

void visit(node* x)  {   //  Modifisert kode fra side 424 (midt p†) i l‘reboka:
  int i;
  antsett++;                        //  Teller opp antall bes›kt/sett.
  x->merke = SEEN;                  //  Noden selv er herved bes›kt/sett.
  for (i = 1;  i <= x->ant_naboer;  i++)   //  G†r til alle naboer som ikke
      if (x->nabo[i]->merke == UNSEEN)  visit(x->nabo[i]);  // er bes›kt/sett.

}

void skriv_TAK()  {      //  Modifisert kode fra side 474 (›verst) i l‘reboka:
  int i, j;                         //  L›kkevariable.
  for (i = 1;  i <= V;  i++)  {     //  Starter etter tur i hver av nodene.
      for (j = 1;  j <= V;  j++)  G[j]->merke = UNSEEN;  //  Nullstiller.
      antsett = 0;                  //  Nullstiller antall man bes›ker.
      visit(G[i]);                  //  Hvor mange n†r man fra node nr.i ?
      if (antsett == V)  cout << G[i]->id << "  ";       // Alle ble n†dd!
  }
}


//                   OPPGAVE C - Effektiv versjon:
//                   =============================
bool visit2a(node* t, node* x)  {
  if (t == x ||		//  Har n†dd frem eller bes›kt noden (og evnt.
     t->merke == SEEN)  return true;     //  dens etterf›lgere) allerede.
  else {				//  "t" er ikke bes›kt og kan pr›ve dens etterf›lgere:
     t->merke = SEEN;   //  Noden er herved bes›kt.
     for (int i = 1;  i <= t->ant_naboer;  i++)  //  Bes›ker alle naboene:
						//  Fra MINST EN er det mulig † komme frem:
         if (visit2a(t->nabo[i], x)) return true;
     t->merke = UNSEEN;	//  Setter UNSEEN, slik at senere kan oppdage 
  }						//    om n†r frem (eller ei) fra annen node/sti.
  return false;		   	//  Ikke mulig † komme frem.
}


//                   OPPGAVE C - Enkel versjon - litt mindre effektiv:
//                   =================================================
bool visit2b(node* t, node* x)  {
  if (t == x)  return true;	//  Har n†dd frem:
  else {					//  Pr›ver "t" sine etterf›lgere:
 	 for (int i = 1; i <= t->ant_naboer; i++)	//  Bes›ker naboer:
							//  Fra MINST EN er det mulig † komme frem:
	     if (visit2b(t->nabo[i], x)) return true;
  }
  return false;				//  Ikke mulig † komme frem.
}


bool er_i_FAKa(node* x)  {   //  Modifisert kode fra side 424 (›verst) i l‘reboka:
	int i;
	for (i = 1; i <= V; i++)  G[i]->merke = UNSEEN;  //  Nullstiller.
	for (i = 1; i <= V; i++)                 //  G†r gjennom alle nodene:
		if (!visit2a(G[i], x)) return false; //  Kommer ikke frem til "x" fra G[i].
	return true;                             //  Kom frem fra ALLE nodene til "x"!
}

bool er_i_FAKb(node* x)  {   //  Modifisert kode fra side 424 (›verst) i l‘reboka:
	int i;
	for (i = 1; i <= V; i++)                 //  G†r gjennom alle nodene:
		if (!visit2b(G[i], x)) return false; //  Kommer ikke frem til "x" fra G[i].
	return true;                             //  Kom frem fra ALLE nodene til "x"!
}


/*  NB: Det finnes faktisk et enda enklere svar p† OPPGAVE C:
        Ser man n›yere p† problemstillingen s† viser det seg at det er
        nok † sjekke at:
          (1) noden "x" ikke har noen etterf›lgere  og at
          (2) alle andre noder har minst EN etterf›lger.
        (Egentlig f›lger 1 av 2 siden vi VET at grafen er l›kkefri.)

        At 2 er et NØDVENDIG krav for at "x" er i FA-kjernen er opplagt.
        At det er TILSTREKKELIG ser vi av:
           Anta at vi starter i en tilfeldig node "t", som er ulik "x".
           Vi velger s† en tilfeldig kant ut av "t" og kommer til en ny node.
           Herfra velger vi igjen en tilfeldig kant ut osv. Denne prosessen
           MÅ ende opp i "x" (den eneste uten ut-kanter), ellers ville vi f†
           en l›kke senest etter † ha g†tt N steg. Alts† finnes en vei fra 
           "t" til "x", og siden "t" var tilfeldig valgt g†r det vei fra
           alle til "x".
        Programmet for dette er ikke angitt her, men det blir selvf›lgelig
        bare en enkel l›kke, der det er nok † teste krav 2.
        Se evnt. eksamen 3.mars 1997 nr.2b.
*/


			//  HOVEDPROGRAM:
int main()  {
  int i;
  lag_graf1();
  cout << "\n\nNoder som er med i TA-kjernen:\n\t";
  skriv_TAK();                                   //  Bruker OPPGAVE A.

  lag_graf2();
  cout << "\n\nNoder som er med i FA-kjernen (NB: Max. ett stk. ved l›kkefri graf!):";
  for (i = 1; i <= V; i++)
	  cout << "\n\t\t" << G[i]->id << ":  "
	  << ((er_i_FAKa(G[i])) ? "Ja !" : "Nei");   //  Bruker OPPGAVE C - 2a.
  cout << '\n';
  for (i = 1; i <= V; i++)
	  cout << "\n\t\t" << G[i]->id << ":  "
	  << ((er_i_FAKb(G[i])) ? "Ja !" : "Nei");   //  Bruker OPPGAVE C - 2b.
  cout << "\n\n";
  return 0;
}


void lag_graf1()  {
  V = 5;                        //  Setter antall noder i grafen.
  G[1] = new node('A', 3);      //  Bygger grafen:
  G[2] = new node('B', 0);      //
  G[3] = new node('C', 3);      //       A---------------->B
  G[4] = new node('D', 2);      //       ^\          ----> ^
  G[5] = new node('E', 2);      //       | \         |     |
  G[1]->nabo[1] = G[2];         //       |  \        |     |
  G[1]->nabo[2] = G[3];         //       |   \       |     |
  G[1]->nabo[3] = G[5];         //       V    \      |     |
  G[3]->nabo[1] = G[1];         //       C-----\-----|---->D
  G[3]->nabo[2] = G[4];         //       |      \    |     ^
  G[3]->nabo[3] = G[5];         //       |       \   /     |
  G[4]->nabo[1] = G[2];         //       |        \ /      |
  G[4]->nabo[2] = G[5];         //       |        V/       |
  G[5]->nabo[1] = G[2];         //       -------->E<--------
  G[5]->nabo[2] = G[4];         //  
}                               //   Der A og C er i TA-kjernen.


void lag_graf2()  {
  int i;
  for (i = 1; i <= V;  i++)  delete G[i];   //  Sletter tidligere graf.
  V = 8;                      //  Setter antall noder i den nye grafen.
  G[1]  = new node('A', 3);   //  Bygger graf lik med EX_S00 nr.2b (side 70),
  G[2]  = new node('B', 2);   //     bare uten vekter p† kantene.
  G[3]  = new node('C', 2);   //  
  G[4]  = new node('D', 3);   //  'H' er der kummen og dermed den eneste som
  G[5]  = new node('E', 1);   //     er med i FA-kjernen.
  G[6]  = new node('F', 1);
  G[7]  = new node('G', 2);
  G[8]  = new node('H', 0);
  G[1]->nabo[1]  = G[4];  G[1]->nabo[2]  = G[3];  G[1]->nabo[3]  = G[2];
  G[2]->nabo[1]  = G[5];  G[2]->nabo[2]  = G[6];
  G[3]->nabo[1]  = G[6];  G[3]->nabo[2]  = G[2]; 
  G[4]->nabo[1]  = G[6];  G[4]->nabo[2]  = G[7];  G[4]->nabo[3]  = G[3];
  G[5]->nabo[1]  = G[8];
  G[6]->nabo[1]  = G[5];
  G[7]->nabo[1]  = G[8];  G[7]->nabo[2]  = G[6];
}   
