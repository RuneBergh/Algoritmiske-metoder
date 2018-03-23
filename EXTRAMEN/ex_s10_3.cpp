//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S10_3.CPP

//     L›sningsforslag til kontinuasjonseksamen i "Algoritmiske metoder",
//     10.august 2010, oppgave nr.3.

//     Laget av Frode Haug, HiG, mai 2010.


#include <iostream>
using namespace std;


struct Node  {
  int   ID;     //  Nodens ID/key/n›kkel/navn (et tall).
  Node* left;	//  Peker til venstre subtre, evt. z-noden om det er tomt.
  Node* right;  //  Peker til h›yre subtre. Om tomt, peker den til 
                //     etterf›lgende node/ID (i inorder rekkef›lge) 
                //     evt. z-noden om noden selv er den aller siste.
  bool  harHoyreBarn;  //  'true' om har EKTE h›yrebarn.
  Node (int id, Node* l, Node* r, bool hHB) 
	   { ID = id;  left = l;  right = r;  harHoyreBarn = hHB;  }
};

                   //  Globale variable:
Node* z   = new Node(0, NULL, NULL, false);  //  z-noden.
Node* rot = z;                               //  Rot-peker.


//  OPPGAVE 3A2:   Finner og returnerer (om mulig) den sekvensielt f›rste noden
//                   (med minst verdi - den lengst til venstre) under 'p'.
Node* forste(Node* p)  {
  if (p != z)
     while (p->left != z) p = p->left;    //  Blar ALLER nederst til venstre.
  return p;                               //  Returnerer noden kommet fram til.
}


//  OPPGAVE 3B:    Returnerer (true/false) til om noden 'v' finnes 
//                   (nedover et sted) i treet tilpekt av 'rot'.
bool finn(int v)  {
  Node* p = rot;
  while (p != z)  {         //  S† lenge ikke n†dd bladnode (z) eller match:
    if (v <  p->ID)      p = p->left;        //  G†r til venstre.
    else if (v == p->ID)      return true;   //  Treff/funn/match!
    else if (p->harHoyreBarn) p = p->right;  //  Ekte h›yre: G†r til h›yre.
    else p = z;                            //  Slutt/"tomt" (uekte h›yre barn).
  }
  return false;                              //  Ingen funn/match.
}


//  OPPGAVE 3C:   G†r gjennom og skriver 'p's verdi og ALLE verdier st›rre
//                  enn 'v' i HELE (resten av) treet - UTEN † bruke rekursjon.
void traverser(Node* p)  {
  if (p != z)  {
     do  {
       cout << p->ID << ' ';
       p = (p->harHoyreBarn) ? forste(p->right) : p->right;
     } while (p != z);
  }
}


//  OPPGAVE 3D:   Legger inn verdien 'v' i treet tilpekt av 'rot', og 
//                   etter de "regler" beskrevet i oppgaveteksten.
void legginn(int v)  {
  Node *p = rot, *q = z;    //  Initierer pekere. 'q' er "mor-peker" til 'p'.
                            //  Ny node skal ALLTID inn ALLER nederst:
  while (p != z)  {         //  Blar nedover til plassen er funnet:
    q = p;                  //  'q' flytter etter 'p'.
         if (v < p->ID)       p = p->left;    //  G†r til venstre.
    else if (p->harHoyreBarn) p = p->right;   //  G†r til h›yre.
    else p = z;                         //  Slutt (n†dd 'z' eller uekte h›yre).
  }                          
  if (q == z)                 //  Treet var tomt - ny rot:
     rot = new Node(v, z, z, false);
  else if (v < q->ID)  {      //  Ny mindre - skal inn til venstre:
     q->left = new Node(v, z, q, false);
  } else  {                   //  Ny st›rre eller lik - inn til h›yre:
     q->harHoyreBarn = true;  //  "Mor" f†r derfor nytt ekte h›yrebarn.
     q->right = new Node(v, z, q->right, false);  //  Overtar "mors neste".
  }
}


int main()  {
                           //  Bygger treet tegnet nedenfor:
  legginn(13);  legginn(21);  legginn(15);  legginn(5);
  legginn(11);  legginn(8);   legginn(26);  legginn(14);
  legginn(18);  legginn(20);  legginn(3);

  cout << "Node med ID lik 14 finnes" << ((!finn(14))? " IKKE" : "") << '\n';
  cout << "Node med ID lik 19 finnes" << ((!finn(19))? " IKKE" : "") << '\n';
  cout << "\n\n";
                                              //  Utskrift:
  traverser(rot);               cout << '\n'; //  13 14 15 18 20 21 26
  traverser(rot->left);         cout << '\n'; //  5 8 11 13 14 15 18 20 21 26
  traverser(rot->left->right);  cout << '\n'; //  11 13 14 15 18 20 21 26
  traverser(rot->left->left->left);     cout << '\n'; //  (ingen utskrift)
  traverser(rot->right);        cout << '\n'; //  21 26
  traverser(rot->right->left);  cout << '\n'; //  15 18 20 21 26
  traverser(rot->right->right->right);  cout << '\n'; //  (ingen utskrift)
  traverser(rot->right->right); cout << '\n'; //  26
  cout << "\n\n";
  return 0;      
}


/*  OPPGAVE 3A1:   Verdiene 13, 21, 15, 5, 11, 8, 26, 14, 18, 20, 3
                   innsatt i et bin‘rt s›ketre etter gjeldende regler:
                   (prikket linje har ALLTID retning mot h›yre og opp)

                       13
                  /     :     \
                 /      :      \
               5        :        21        z
             / : \      :     /   :  \     :
            /  :  \     :    /    :   \    :
           3...:  11....:  15     :   26...:
                 / :      /: \    :
                /  :     / :  \   :
               8...:    14.:  18  :
                                \ :
                                 \:
                                 20
*/
