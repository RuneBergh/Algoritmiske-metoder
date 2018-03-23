//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S99_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     19.august 1999, oppgave 3.

//     Laget av Frode Haug, HiG,  august 1999.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


/*
OPPGAVE A:
                8                   8                         8
              /                  /     \                  /       \
            4                  4         10            4            12
          /   \              /   \      /            /   \         /
         2      6           2      6   9           2      6       10
        / \    / \         / \    / \             / \    / \     / \
       1   3  5   7       1   3  5   7           1   3  5   7   9  11




OPPGAVE B:
  Svaret er at INGEN ANDRE NODER ENN "N" kommer til † f† forandret sin h›yde.

  En kort forklaring p† hvorfor, kan v‘re som f›lger:
  Vi kan f›rst observere at om en node er ubalansert, s† vil den alltid v‘re
  h›yest i venstre subtre. N†r vi setter inn en node N under en ubalansert
  node U, slik som angitt av algoritmen, vil opplagt h›yden av U's h›yre
  subtre ›ke med 1. Men, ut fra at U's venstre subtre er h›yest, vil dette
  ikke p†virke U's h›yde, og derved heller ikke h›yden til noen node mellom
  U og roten. Nodene i de gamle subtr‘rne til U f†r opplagt ikke forandret
  sin h›yde.




OPPGAVE C:         */

#include <iostream>       //  cout

using namespace std;


struct node  {            //  Trenode.
    int id;               //  Nodens ID/verdi.
    int hoyde;            //  Nodens h›yde.
    node* left;           //  Peker til venstre subtre.
    node* right;          //  Peker til h›yre subtre.
    node(int v)   {  id = v;   hoyde = 0;   left = right = NULL;  }
};


int ubalansert(node* np)  {   //  Finner ut om node "np" er ubalansert eller ei.
  int lh, rh;             //  H›ydene for np's venstre og h›yre subtre.
  lh = ((np->left)  ?  np->left->hoyde  :  0);
  rh = ((np->right) ?  np->right->hoyde :  0);
  return (lh != rh);      //  Returnerer 1 dersom ubalansert, ellers 0.
}


void settinn(node* & rot, int verdi)  {
  node *N,                //  Den nye noden som skal inn.
       *U = NULL,         //  Den siste ubalanserte vi fant "p† vei nedover".
       *nop;              //  Hjelpepeker for † bla nedover.

  nop = rot;              //  Intitierer til † peke p† rota.

  while (nop)  {          //  S†lenge ikke n†dd ned til en external-node:
    if (ubalansert(nop)) U = nop;   //  Tar vare p† siste ubalanserte.
    nop = nop->right;     //  G†r ALLTID ned til h›yre subtre.
  }
 
  N = new node(verdi);    //  Oppretter ny node som skal hektes inn.
  
  if (!U)  {              //  Ingen ubalanserte funnet:
     N->left = rot;       //  Den nye legges inn som ny rot, med HELE
                          //     det eksisterende treet blir venstre subtre.
     rot = N;             //  Den referanseoverf›rte "rot" oppdateres.
  } else  {
     N->left  = U->right; // Ny nodes venstretre blir ubalansert nodes h›yretre.
     U->right = N;        // Ubalansert nodes h›yretre blir den nye noden.
  }                       // Setter ny nodes h›yde til † v‘re 1 mer enn 
  N->hoyde = ((N->left) ?  N->left->hoyde+1 : 1);  //  venstretreets, da den
}                         //    ALLTID er h›yere eller lik det h›yre treet !


                             //  Skriver ut dataene i aktuelt/n†v‘rende tre.
void traverser(node* r)  {   //  IKKE EN DEL AV EKSAMENSOPPGAVEN.
     if (r->left)   {  cout << "Venstre-";   traverser(r->left); }
     cout <<  "ID: " << r->id << "  hoyde: " << r->hoyde << "   ";
     if (ubalansert(r)) cout << 'u';    cout << "balansert\n";
     if (r->right)  {  cout << "H›yre-";   traverser(r->right); }
}


int main()  {            //  Hovedprogram for † teste "settinn"
  node* root = NULL;      //  IKKE EN DEL AV EKSAMENSOPPGAVEN.
  char ch;
  settinn(root,  1);  traverser(root);  cin >> ch;
  settinn(root,  2);  traverser(root);  cin >> ch;
  settinn(root,  3);  traverser(root);  cin >> ch;
  settinn(root,  4);  traverser(root);  cin >> ch;
  settinn(root,  5);  traverser(root);  cin >> ch;
  settinn(root,  6);  traverser(root);  cin >> ch;
  settinn(root,  7);  traverser(root);  cin >> ch;
  settinn(root,  8);  traverser(root);  cin >> ch;
  settinn(root,  9);  traverser(root);  cin >> ch;
  settinn(root, 10);  traverser(root);  cin >> ch;
  settinn(root, 11);  traverser(root);  cin >> ch;
  settinn(root, 12);  traverser(root);  cin >> ch;
  return 0;
}
