//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_V94_2.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     10.juni 1994, oppgave 2.

//     Laget av Ove Johan Foss, HIG,  v†ren 1994.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>
using namespace std;


class Node          //  liste-element inneholder bare en int
{                   //  pluss en peker til neste liste-element
public:
   int data;
   Node* neste;

public:
   Node (int d) { data = d; neste = NULL; }
};



class Liste
{
private:
   Node* hode;     //  holder et objekt som er hode til lista
   Node* z;        //  holder et objekt som er enden p† lista,
		   //  peker til seg selv
   int antall;     //  antall elementer i lista

public:
    Liste ();
   ~Liste ();
	     // reverserer lista
   void reverser ();
	     // s›ker etter et element med jump_search
   Node* sok (int v);
	     // setter inn  nn  elementer i lista.
   void settInn (int nn);
	     // sett inn et element i lista. Lista forblir sortert hele tiden.
   void settInnSortert (int d);
	     // setter inn et element mellom node gitt av  p  og  z
   void settVedPos (Node* p, int d);
	     // skriver ut alle elementene
   void utAlle ();
	     // legger sammen de to listene
   void flett (const Liste& L1, const Liste& L2);
};



//----------------------------------------------------------------------
Liste :: Liste ()  {
//----------------------------------------------------------------------
   antall = 0;
   hode = new Node (0);    z = new Node (0);
   hode->neste = z;  //  nestepeker i hode settes lik  z
   z->neste = z;     //  nestepeker i  z  settes til † peke p†  z  selv
}


//----------------------------------------------------------------------
Liste :: ~Liste ()  {
//----------------------------------------------------------------------
   Node* t = hode;

   while ( t!= z )  {
      hode = t;
      t = t->neste;
      delete hode;
   }
   delete z;
}


//----------------------------------------------------------------------
void  Liste :: settInnSortert (int d)  {
//----------------------------------------------------------------------
   Node *ny = new Node (d);

   antall++;
   if ( hode->neste == z || d <= hode->neste->data )  {
      ny->neste = hode->neste;    //  setter inn i start av liste hvis
      hode->neste = ny;           //  lista er tom eller nytt element
      return;                     //  er mindre enn f›rste.
   }

   Node* p;
   for (p=hode->neste; ;p = p->neste)  {
      if (p->neste == z )  {
	 ny->neste = z;         //  setter inn til slutt i lista.
	 p->neste = ny;
	 return;
      }

      if ( p->neste->data >= d )  {  //  setter inn inne i lista.
	 ny->neste = p->neste;
	 p->neste = ny;
	 return;
      }
   }
}


//----------------------------------------------------------------------
void  Liste :: settInn (int nn)  {
//----------------------------------------------------------------------
   int ny;

   cout << endl;
   for (int i=1;i<=nn; i++)  {
      cout << "Gi data : ";
      cin >> ny;
      settInnSortert (ny);
   }
}


//----------------------------------------------------------------------
void  Liste :: reverser ()  {
//----------------------------------------------------------------------
   Node* akt;
   Node* etter;
   Node* foer;

   foer = NULL;
   akt = hode->neste;
   etter = akt->neste;

   while ( etter != z )  {
      akt->neste = foer;
      foer = akt;              //  foer vil hele tiden v‘re starten p†
			       //  ny liste.
      akt = etter;             //  akt og etter flyttes hele tiden utover
      etter = etter->neste;    //  i lista.
   }
   hode->neste->neste = z; //  hode->neste peker p† siste element i den
   akt->neste = foer;      //  nye lista.
   hode->neste = akt;      //  hode settes lik f›rste node i ny liste
}


//----------------------------------------------------------------------
Node*  Liste :: sok (int nokkel)  {
//----------------------------------------------------------------------
   //  returnerer node med data lik  nokkel
   //  bruker metode : jump-search

   Node* akt;
   Node* p = hode->neste;
   int i;

   if ( p == z )   //  lista er tom
      return NULL;
   do  {
      akt = p;      //  evntuell sekvensiell s›k skal starte der  p  startet.
      for (i=1; i<=3; i++)     //  hopper 5 noder ut i liste
	 p = p->neste;
   }
   while (p != z && nokkel > p->data ); // avsluttes n†r vi har kommet til z
					// eller passert data vi leter etter
   if ( p != z && nokkel == p->data )   // funnet node der  p  stoppet
      return p;

   for ( ; akt != p; akt=akt->neste)    // sekvensiell s›k fra  akt  og 5
      if ( nokkel == akt->data )        // noder utover
	 return akt;
   return NULL;         //  fant ingen node med data lik  nokkel
}



//  ***************      Utskrifter     ***************

//----------------------------------------------------------------------
void  Liste :: utAlle ()  {
//----------------------------------------------------------------------
   Node* akt = hode->neste;

   cout << "\nAntall noder er " << antall << " og data er : ";
   while ( akt != z )  {
      cout << akt->data << ' ';
      akt = akt->neste;
   }
}


//----------------------------------------------------------------------
void  Liste :: settVedPos(Node* p, int d)  {
//----------------------------------------------------------------------
   Node* ny = new Node(d);
   antall++;
   ny->neste = z;    //  ny  skal legges inn sist i lista etter
   p->neste = ny;    //  p  og f›r  z.
}




//----------------------------------------------------------------------
void  Liste :: flett (const Liste& L1, const Liste& L2)  {
//----------------------------------------------------------------------
   Node* apos;
   Node* bpos;
   Node* pos;

   apos = L1.hode->neste;   //  start p† L1.
   bpos = L2.hode->neste;   //  start p† L2.
   pos = hode;

   while ( apos != L1.z && bpos != L2.z )  {
      if ( apos->data < bpos->data )  {       //  elementet i L1 er minst og
	 settVedPos (pos, apos->data);        //  settes inn.
	 while ( apos->neste->data == apos->data ) //  hopper til neste
	    apos = apos->neste;                    //  i begge listene.
	 apos = apos->neste;                       //  hopper over like
	 pos = pos->neste;
      }
      else
      if ( apos->data > bpos->data )  {       //  elementet i L2 er minst og
	 settVedPos (pos, bpos->data);        //  settes inn.
	 while ( bpos->neste->data == bpos->data ) //  hopper over like
	    bpos = bpos->neste;                    //  elementer.
	 bpos = bpos->neste;                       //  hopper over like
	 pos = pos->neste;
      }
      else  {
	 settVedPos (pos, apos->data);     //  Like elementer. Setter inn
					   //  element fra L1.
	 pos = pos->neste;
	 while ( apos->neste->data == apos->data ) //  hopper til neste
	    apos = apos->neste;                    //  i begge listene.
	 apos = apos->neste;                       //
						   //
	 while ( bpos->neste->data == bpos->data ) //  hopper over like
	    bpos = bpos->neste;                    //  elementer.
	 bpos = bpos->neste;
      }
   }

   if ( apos == L1.z )
      while ( bpos != L2.z )  {    //  legger inn resten av L2 i lista.
	 settVedPos (pos, bpos->data);
	 bpos = bpos->neste;
      }

   if ( bpos == L2.z )
      while ( apos != L1.z )  {   //  legger inn resten av L1 i lista.
	 settVedPos (pos, apos->data);
	 apos = apos->neste;
      }
}



int main ()  {
   Liste L1, L2;

   cout << "\nF›rste liste:\n";
   L1.settInn (8);
   L1.utAlle ();

   cout << endl;

      L1.reverser ();        //  Reverserer et ›yeblikk for † f†
      L1.utAlle ();          //    se lista i denne tilstanden.
      L1.reverser ();        //    Oppretter opprinnelig liste.

   cout << "\n\n\nAndre liste:\n";
   L2.settInn (10);
   L2.utAlle ();

   cout << endl;

      L2.reverser ();        //  Reverserer et ›yeblikk for † f†
      L2.utAlle ();          //    se lista i denne tilstanden.
      L2.reverser ();        //    Oppretter opprinnelig liste.

   cout << "\n\n\nUnion av listene:";

   Liste L3;

   L3.flett (L1, L2);
   L3.utAlle ();

   cout << "\n\n\nS›ker etter data:";

   int d = 0;
   Node* p;
   while ( d != 99 )  {
      cout << "\n\nGi data (avslutt med '99'): ";
      cin >> d;
      p = L3.sok(d);
      if (p)
	 cout << "Funnet data er : " << p->data;
      else
	 cout << "Noden ikke funnet i L3.";
   }
   cout << "\n\n";
   return 0;
}
