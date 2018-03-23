//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H03_3.CPP

//     L�sningsforslag til eksamen i
//     "Algoritmiske metoder", oppgave nr.3, 12.desember 2003.

//     Laget av Frode Haug, HiG, desember 2003.


#include <iostream>
using namespace std;


struct node  {
   char key;
   node *mindre, *storre;
   node(char i, node* m, node* s)  {  key = i;  mindre = m;  storre = s;  }
};


node* z;                   //  z-noden som "erstatter" NULL.
node* p[11];               //  Hjelpearray med pekere for � bygge et test-tre.


void bygg_tre()  {
  z = new node('z', NULL, NULL);           //    Bygger test-treet:         //
  p[0]  = new node('A', z, z);             //                               //
  p[2]  = new node('E', z, z);             //                O              //
  p[4]  = new node('K', z, z);             //           /         \         //
  p[8]  = new node('S', z, z);             //         H             U       //
  p[10] = new node('X', z, z);             //       /   \         /   \     //
  p[1]  = new node('C', p[0], p[2]);       //      C     M       P     X    //
  p[5]  = new node('M', p[4], z);          //     / \   /         \         //
  p[7]  = new node('P', z, p[8]);          //    A   E K           S        //
  p[3]  = new node('H', p[1], p[5]);
  p[9]  = new node('U', p[7], p[10]);
  p[6]  = new node('O', p[3], p[9]);
}


void display(node* l)  {
  if (l != z)  {                  //  Listen er IKKE tom:
     node* p = l;                 //  Hjelpepeker for � traversere listen.
     while (p->storre != l)  {    //  Ikke n�dd fram til siste element:
        cout << p->key << ' ';    //  Skriver nodens key/id.
        p = p->storre;            //  Blar til neste node.
     }
     cout << p->key << ' ';       //  Spesialskriver den siste i listen.
  }
}

                        //  OPPGAVE 3A:
                               //  Skj�ter sammen to sirkul�re to-veis lister:
node* skjot_sammen(node* liste1, node* liste2) {
  node *siste1, *siste2;

  if (liste1 == z)  return liste2;  // Ingenting � skj�te, returnerer den ene.
  if (liste2 == z)  return liste1;  // Ingenting � skj�te, returnerer den andre.

  siste1 = liste1->mindre;     //  Setter spesielle pekere til de siste i hver
  siste2 = liste2->mindre;     //    av de to opprinnelige listene:

  siste1->storre = liste2;     //  Skj�ter liste2 til enden p� liste1:
  liste2->mindre = siste1;

  siste2->storre = liste1;     //  Lager sirkul�r liste mellom f�rste og siste
  liste1->mindre = siste2;     //    element i den totale/sammensl�tte listen.

  return liste1;               //  Returnerer peker til den nye totale listen.
}


                        //  OPPGAVE 3B:
node* lag_liste(node* rot)  {
  node *liste1, *liste2;

  if (rot == z)  return z;           //  Treet er tomt, returnerer bare 'z'.

  liste1 = lag_liste(rot->mindre);   //  Lager rekursivt sirkul�re lister av
  liste2 = lag_liste(rot->storre);   //    venstre og h�yre subtre !

  rot->mindre = rot;                 //  Lager sirkul�r liste p� ETT element  
  rot->storre = rot;                 //    av rota selv.

  liste1 = skjot_sammen(liste1, rot);    // Skj�ter rota etter "venstre liste".
  liste1 = skjot_sammen(liste1, liste2); // Skj�ter h�yre etter den venstre.
 
  return liste1;          //  Returnerer peker til konstruert sirkul�r liste.
}


int main()  {
  node* lista;

  bygg_tre();
  lista = lag_liste(p[6]);     //  Sender med rota 'O'. F�r tilbake sirkul�r
                               //    liste der "lista" peker til noden 'A'.
  display(lista);
  cout << "\n\n";
  return 0;
}
