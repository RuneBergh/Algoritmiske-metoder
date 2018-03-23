//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_V94_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     10.juni 1994, oppgave 3.

//     Laget av Ove Johan Foss, HIG,  v†ren 1994.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>
using namespace std;


class Node  {
public:
   int data;       //  lagrer bare et heltall ( ikke med i oppgaven)
   Node* annen;    //  peker p† en annen node i treet
   Node* v;        //  venstre og h›yre peker i treet
   Node* h;

public:
   Node (int d, Node* a, Node* vv, Node* hh)
   {  data = d;     annen = a;    v = vv;       h = hh; }
   ~Node ()  {  }
};


class BinSTre  {
public:
   Node* hode;      //  implementasjon f›lger s.204 i l‘reboka.
   Node* z;
   Node* kopi;
   int ant_noder;

public:
   BinSTre ()
   {  z = new Node(0, NULL, NULL, NULL);
      z->v = z;  z->h = z;      //  z  settes til † peke p† seg selv
      hode = new Node(0, z, NULL, z); // hode->h›yrepeker peker p† rot i treet
      //  kopi->h›yrepeker peker p† rot i kopitre.
      kopi = new Node(0, z, NULL, z);
   }
   ~BinSTre ()  {  }
   void settInn (int v);
   void utSortert ();   //  bruker  inordertraversering av treet
   void ut ();          //  bruker preordertraversering av treet
   void inorder (Node* t);
   void preorder (Node* t);
		  //  kopierer treet og returnerer en peker til rot i kopitre.
   Node* kopierTre (Node* x);
		  //  lager kopi av treet. Kopi kan n†s gjennom kopipeker.
   void utKopi ();
		  //  utvider tre slik som beskrevet i oppgavetekst.
   void dupliser (Node* x);
   void dupliserTre ();
		  //  oppdaterer tre slik som beskrevet  i oppgavetekst.
   void oppdater (Node* x);
   void oppdaterTre ();
};


//--------------------------------------------------------------------------
void
BinSTre :: settInn (int v)  {   //  setter inn ny node i treet
//--------------------------------------------------------------------------
   Node* p;
   Node* x;
   p = hode;
   x = hode->h;

   while ( x != z )   //  s›ker opp node
   {
      p = x;
      if ( v < x->data )
	 x = x->v;
      else
	 x = x->h;
   }
   x = new Node(v, z, z, z);
   if ( v < p->data )
      p->v = x;
   else
      p->h = x;
}


//--------------------------------------------------------------------------
void
BinSTre :: inorder (Node* t)  {  //  inordertraversering fra s.60 i l‘reboka.
//--------------------------------------------------------------------------
   if ( t != z )
   {
      inorder (t->v);
      cout << t->data << " ";
      inorder (t->h);
   }
}


//--------------------------------------------------------------------------
void
BinSTre :: preorder (Node* t)  {   // preordertraversering fra s.62 i l‘reboka
//--------------------------------------------------------------------------
   if ( t != z )
   {
      cout << t->data << " ";
      preorder (t->v);
      preorder (t->h);
   }
}


//--------------------------------------------------------------------------
void
BinSTre :: ut ()  {
//--------------------------------------------------------------------------
   cout << "\n\nPreorder rekkef›lge : ";
   preorder (hode->h);
}


//--------------------------------------------------------------------------
void
BinSTre :: utSortert ()  {
//--------------------------------------------------------------------------
   cout << "\n\nInorder rekkef›lge : ";
   inorder (hode->h);
}


//--------------------------------------------------------------------------
void
BinSTre :: utKopi ()  {
//--------------------------------------------------------------------------
   kopi->h = kopierTre (hode->h);
   cout << "\n\nKopitre i inorder rekkef›lge : ";
   inorder (kopi->h);
}


//--------------------------------------------------------------------------
Node*
BinSTre :: kopierTre (Node* x)  {
//--------------------------------------------------------------------------
   if ( x != z )
      return new Node(x->data, z, kopierTre (x->v), kopierTre (x->h));
   else
      return z;
}


//--------------------------------------------------------------------------
void
BinSTre :: dupliser (Node* x)  {
//--------------------------------------------------------------------------
   if ( x != z )  {
      dupliser (x->v);
      x->v = new Node (0, z, x->v, z);
      dupliser (x->h);
   }
}


//--------------------------------------------------------------------------
void
BinSTre :: dupliserTre ()  {
//--------------------------------------------------------------------------
   dupliser (hode->h);
}


//--------------------------------------------------------------------------
void
BinSTre :: oppdater (Node* x)  {
//--------------------------------------------------------------------------
   if ( x != z )  {
      oppdater (x->v->v);
      oppdater (x->h);
      if ( x->annen != z )
	    x->v->annen = x->annen->v;
   }
}


//--------------------------------------------------------------------------
void
BinSTre :: oppdaterTre ()  {
//--------------------------------------------------------------------------
   oppdater (hode->h);
}


//*************************  HOVEDPROGRAM:  *********************************

int main ()
{
   int d;

   cout << "\nBin‘rt s›ketre - implementasjon fra s.204 i l‘reboka.\n\n";

   BinSTre oerder;

   for (int i=1; i<=10; i++)  {
      cout << "Gi data : ";
      cin >> d;
      oerder.settInn (d);
   }

   oerder.ut ();
   oerder.utSortert ();

   cout << "\n\n";

   oerder.utKopi ();

   oerder.dupliserTre ();
   oerder.oppdaterTre ();
   cout << "\n\n";
   return 0;

}
