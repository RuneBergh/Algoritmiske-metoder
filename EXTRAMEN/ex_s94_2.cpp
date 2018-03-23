//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S94_2.CPP

//     L›sningsforslag til kontinuasjonseksamen i "Algoritmiske metoder",
//     august 1994, oppgave 2.

//     Laget av Ove Johan Foss, HIG,  sommeren 1994.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>
#include <cstdlib>
using namespace std;


class Node  {
public:
   Node* v;
   Node* h;
   int data;

public:
   Node (int k, Node* vv, Node* hh)  {  data = k; v = vv; h = hh;  }
};


class BinTre  {
public:
   Node* head;
   Node* z;
   void postorder (Node* subrot);
   void inorder   (Node* subrot);
   void skriv     (Node* t);

public:
   BinTre ();
   ~BinTre () {}
   void traverser (char type);      //  tatt med type for † angi hva slags
				    //  traversering jeg skal utf›re.
   Node* settInn (Node* t, Node* x);
   void inn ();
   void skrivIntervall (Node* subrot, int lav, int hoy);
   void skrivIntervall2 (Node* subrot, int lav, int hoy);
};


//----------------------------------------------------------------------
BinTre :: BinTre ()  {                     //  Jfr. s.204 i l‘reboka.
//----------------------------------------------------------------------
   z = new Node (0, NULL, NULL);
   z->v = z;     z->h = z;
   head = new Node (0, NULL, z);    //  head->h  holder treet.
}


//----------------------------------------------------------------------
void  BinTre :: traverser (char type)  {
//----------------------------------------------------------------------
   switch (type)  {
      case 'i' :
	 inorder (head->h);
	 break;
      case 'p' :
	 postorder (head->h);
	 break;
      default:
	 cout << "\nTraverseringsmetode er ikke implementert !";
	 break;
   }
}


//----------------------------------------------------------------------
void  BinTre :: inorder (Node* subrot)  {      //  Jfr. s.60 i l‘reboka.
//----------------------------------------------------------------------
   if ( subrot != z )  {
      inorder (subrot->v);
      skriv (subrot);
      inorder (subrot->h);
   }
}


//----------------------------------------------------------------------
void  BinTre :: postorder (Node* subrot)  {    //  Jfr. s.62 i l‘reboka.
//----------------------------------------------------------------------
   if ( subrot != z)  {
      postorder (subrot->v);
      postorder (subrot->h);
      skriv (subrot);
   }
}


//----------------------------------------------------------------------
void  BinTre :: skriv (Node* t)  {
//----------------------------------------------------------------------
   cout << t->data << " ";
}


//----------------------------------------------------------------------
Node*  BinTre :: settInn (Node* subrot, Node* x)  {   // Jfr. oppgaveteksten.
//----------------------------------------------------------------------
   if ( subrot == z )
      return  x;
   else
   if ( x->data <= subrot->data )
      subrot->v = settInn (subrot->v, x);
   else
      subrot->h = settInn (subrot->h, x);
   return subrot;
}


//----------------------------------------------------------------------
void  BinTre :: inn ()  {
//----------------------------------------------------------------------
   Node* ny;
   int v;

   cout << "Gi tall : ";
   cin >> v;
   while ( v != 0 )  {
      ny = new Node(v, z, z);
      head->h = settInn (head->h, ny);
      cout << "Gi tall : ";
      cin >> v;
   }
   cout << "\n\nTraverserer treet : " << flush;
   traverser ('i');
}


					    //  OPPGAVE  B:
//----------------------------------------------------------------------
void  BinTre :: skrivIntervall (Node* subrot, int lav, int hoy)  {
//----------------------------------------------------------------------
   if ( subrot != z )  {
      if ( subrot->data >= lav )     //  G†r ned i venstre subtre
	 skrivIntervall (subrot->v, lav, hoy);
				     //  Noden selv i rett intervall:
      if ( subrot->data >= lav && subrot->data <= hoy )
	 cout << subrot->data << " ";
      if ( subrot->data < hoy )      //  G†r ned i h›yre subtre.
	 skrivIntervall (subrot->h, lav, hoy);
   }
}

int main ()   {
   BinTre tre;
   tre.inn ();
   cout << "\n\nData melom 10 og 100 : ";
   tre.skrivIntervall (tre.head->h, 10, 100);
   cout << "\n\nData melom 5 og 50 : ";
   tre.skrivIntervall (tre.head->h, 5, 50);
   cout << "\n\n";
   return 0;
}
