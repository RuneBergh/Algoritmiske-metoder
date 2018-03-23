//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H00_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     11.desember 2000, oppgave 3.

//     Laget av Frode Haug, HiG, desember 2000.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



#include <iostream>          //  cout
using namespace std;

const int N = 5;             //  Antall noder i grafen.

struct tre_node;             //  Pre-deklarasjon.
tre_node*  z;                //  z-noden - nederst p† hver gren.


struct node {                // En "node" i grafen.
  int ant_naboer;            // Antall naboer, 0 <= ant_naboer <= 10
  int nabo[10];              // Nodenummere for alle direkte naboer.
  int vekt[10];              // Kantvekter.
};


struct tre_node {            // En "node" i s›ketreet.
  int vekt;                  // Kantvekt.
  int til, fra;              // Nodenummere i grafen for de to nodene som
			     //   er knyttet til hverandre med denne kanten.
  tre_node *l,*r;            // Pekere til venstre og h›yre barn i treet.
  tre_node(int v, int f, int t)   // Constructor:
    { vekt = v;  fra = f;  til = t;  l = r = z;  }
};


node* graf[N];               // Direktepekere til alle nodene i grafen.


void initier_graf()  {       // Initierer/setter opp hele grafen:
  graf[0] = new node;  graf[0]->ant_naboer = 2;  // Lager graf-noder og
  graf[1] = new node;  graf[1]->ant_naboer = 3;  //   setter opp antall naboer:
  graf[2] = new node;  graf[2]->ant_naboer = 1;
  graf[3] = new node;  graf[3]->ant_naboer = 2;
  graf[4] = new node;  graf[4]->ant_naboer = 1;  // Setter nabo-pekere og vekt:
  graf[0]->nabo[0] = 1;   graf[0]->vekt[0] = 4;   //  0 --> 1 : 4
  graf[0]->nabo[1] = 3;   graf[0]->vekt[1] = 5;   //  0 --> 3 : 5
  graf[1]->nabo[0] = 0;   graf[1]->vekt[0] = 3;   //  1 --> 0 : 3
  graf[1]->nabo[1] = 2;   graf[1]->vekt[1] = 5;   //  1 --> 2 : 5
  graf[1]->nabo[2] = 4;   graf[1]->vekt[2] = 7;   //  1 --> 2 : 7
  graf[2]->nabo[0] = 3;   graf[2]->vekt[0] = 6;   //  2 --> 3 : 6
  graf[3]->nabo[0] = 0;   graf[3]->vekt[0] = 5;   //  3 --> 0 : 5
  graf[3]->nabo[1] = 4;   graf[3]->vekt[1] = 6;   //  3 --> 4 : 6
  graf[4]->nabo[0] = 1;   graf[4]->vekt[0] = 8;   //  4 --> 1 : 8
}



// **********************  LSNING NR.1:  ***********************

		     //  En liten modifisering av koden side 206 i l‘reboka:
void settinn1(tre_node* hode, int vekt, int fra, int til)  {
  tre_node* p, *x;
  p = hode;  x = hode->r;
  while (x != z) {
    p = x;    x = (vekt < x->vekt) ? x->l : x->r;
  }
  x = new tre_node(vekt, fra, til);
  if (vekt < p->vekt)  p->l = x;   else  p->r = x;
}


tre_node* kant_tre1()  {          //  F†r lagt inn ALLE kanter i s›ketreet:
  tre_node* head = new tre_node(0, 0, 0);   head->r = z;   // Lager tomt tre.

  for (int i = 0; i < N; i++)     //  G†r gjennom alle nodene i grafen:
    for (int j = 0; j < graf[i]->ant_naboer; j++)    // Hver nodes naboer:
      settinn1(head, graf[i]->vekt[j], i, graf[i]->nabo[j]);  // Legger inn.

  return head->r;                 //  Returnerer rota i treet.
}



// **********************  LSNING NR.2:  ***********************
				  //  En mer "snerten" m†te † legge inn
				  //    noe i et tre p† (rekursivt):
				  //  NB: Referanseoverf›ring av peker!
void settinn2(tre_node* & rot, int vekt, int fra, int til)  {
  if (rot == z)                   //  Kommet til en bladnode. Legger inn ny:
    rot = new tre_node(vekt, fra, til);
  else {                          //  Blar enn† nedover:
    if (rot->vekt > vekt)         //  Skal til venstre:
       settinn2(rot->l, vekt, fra, til);
    else                          //  Skal til h›yre:
       settinn2(rot->r, vekt, fra, til);
  }
}


tre_node* kant_tre2()  {          //  F†r lagt inn ALLE kanter i s›ketreet:
  tre_node* rot = z;              //  Lager tomt tre.

  for (int i = 0; i < N; i++)     //  G†r gjennom alle nodene i grafen:
    for (int j = 0; j < graf[i]->ant_naboer; j++)    // Hver nodes naboer:
      settinn2(rot, graf[i]->vekt[j], i, graf[i]->nabo[j]);   // Legger inn.

  return rot;                     //  Returnerer rota i treet.
}


// **********************  ANNET:  ***********************

void traverse(tre_node* t)  {     //  Jfr. side 60 i l‘reboka.
  if (t != z) {
     traverse(t->l);              //  Bes›ker/skriver noden:
     cout << "Fra: " << t->fra << "\tTil: " << t->til
	  << "\tVekt: " << t->vekt << '\n';
     traverse(t->r);
  }
}


int main()   {
  z = new tre_node(0, 0, 0);      //  Initierer 'z'.
  initier_graf();                 //  Setter opp grafen.

  cout << "\nL›sningsm†te nr.1\n";
  traverse(kant_tre1());          //  L›ser oppgaven p† den 1.m†ten.

  cout << "\nL›sningsm†te nr.2\n";
  traverse(kant_tre2());          //  L›ser oppgaven p† den 2.m†ten.

  return 0;
}
