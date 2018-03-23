
//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H95_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     12.desember 1995, oppgave 3.

//     Laget av Frode Haug, HIG, h›sten 1995.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


//     NB: Det er KUN funksjonene "oppgave_a" og "oppgave_b" som
//         er svaret p† eksamensoppgaven. Alt det andre er n›dvendig
//         kode for † kunne teste ut disse to funksjonene.


#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;


const int MAX_NODER = 101;   //  Bruker indeks 1-100.
const int MAX_NABO  = 11;    //  Bruker indeks 1-10.
const int SEEN   = 1;        //  Brukes KUN av "skriv_graf"
const int UNSEEN = 0;        //    og "null_graf".


struct node  {
  int   navn;                //  Nodens navn.
  int   ant_kant;            //  Antall naboer/kanter ut fra node.
  node* neste[MAX_NABO];     //  Pekere til naboene.
  node* kopi;                //  Peker til evnt. duplikat av en selv.
  int   status;              //  Brukes KUN i "skriv/null_graf".
  node(int id, int ant)   {  navn = id;    ant_kant = ant;
			     kopi = NULL;  status = UNSEEN;  }
};


node* noder[MAX_NODER];      //  Global array med peker til hver enkelt node
			     //    i grafen. Brukes kun i "oppgave_a".
int V;                       //  Totalt antall noder i grafen.


void les_graf_fra_fil()  {   //  Leser og oppretter grafen fra fil.
   int i, j, node_id, ant_ka;

   ifstream inn ("EX_H95_3.DTA");

   inn >> V;                       //  Leser antall noder.
   for (i = 1;  i <= V;  i++)  {
      inn >> ant_ka;               //  Leser antall kanter for hver node.
      noder[i] = new node(i, ant_ka);    //  Oppretter nye node.
   }

   for (i = 1;  i <= V;  i++)      //  Fyller nodenes neste-array:
      for (j = 1;  j <= noder[i]->ant_kant;  j++)  {
	 inn >> node_id;           //  Leser inn en nabo-node.
	 noder[i]->neste[j] = noder[node_id];   //  Oppretter peker mellom.
      }
}


void skriv_graf (node* x)  {       //  G†r gjennom og skriver hele grafen.
   int i;
   if ( x->status == UNSEEN )  {   //  Noden er enn† ikke bes›kt:
      x->status = SEEN;
      cout << "\n\tNode nr." << x->navn << ", har naboene:   ";
      for (i = 1;  i <= x->ant_kant;  i++)   cout << x->neste[i]->navn << "  ";
      for (i = 1;  i <= x->ant_kant;  i++)   skriv_graf(x->neste[i]);
   }
}

void null_graf (node* x)  {
   if ( x->status == SEEN )  {     //  Noden er enn† "ikke bes›kt":
      x->status = UNSEEN;
      for (int i=1;  i<=x->ant_kant;  i++)   null_graf(x->neste[i]);
   }
}


void oppgave_a()  {     //  G†r gjennom arrayen TO ganger. En gang for
  int i, j;             //  † lage kopi-node, en gang for † peke til naboene.
  for (i = 1;  i <= V;  i++)
			     // Lager kopi med likt navn og ant.naboer:
			     //   (+10 KUN for † SE at kopi-node.)
      noder[i]->kopi = new node(noder[i]->navn+10, noder[i]->ant_kant);

  for (i = 1;  i <= V;  i++)  {           //  G†r gjennom alle kopi-nodene,
      for (j = 1;  j <= noder[i]->kopi->ant_kant;  j++)     //  og oppretter
      noder[i]->kopi->neste[j] = noder[i]->neste[j]->kopi;  //  pekere til
  }                                                         //  alle naboene.
}


void oppgave_b(node* x)  {
  int j;
     if (x->kopi == NULL)  {              // Noden er enn† ikke kopiert:
					  // +20 KUN for † SE at kopi-node:
	x->kopi = new node(x->navn+20, x->ant_kant);

	for (j = 1;  j <= x->ant_kant;  j++)  {
	    oppgave_b(x->neste[j]);
	    x->kopi->neste[j] = x->neste[j]->kopi;
	}
     }
}


// ---------------------  HOVEDPROGRAM:  ---------------------------------

int main ()  {
   char valg;
   node* S;

   les_graf_fra_fil();
   S = noder[1];
   cout << "Grafen lest fra fil:";
   skriv_graf(noder[1]);   null_graf(noder[1]);
   cout << "\n\n\nVil du teste oppgave A eller B:  ";   cin >> valg;

   if (valg == 'A' ||  valg == 'a')  {
      oppgave_a();
      cout << "\n\nKopi-grafen ved TO gjennomganger vha. for-l›kker:";
      skriv_graf(noder[1]->kopi);   null_graf(noder[1]->kopi);
   }  else  {
      oppgave_b(S);
      cout << "\n\nKopi-grafen ved EN gjennomgang vha. rekursjon:";
      skriv_graf(S->kopi);   null_graf(S->kopi);
   }
   cout << "\n\n";
   return 0;
}
