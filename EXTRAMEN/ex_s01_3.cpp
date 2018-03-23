//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S01_3.CPP

//     Lõsningsforslag til eksamen i "Algoritmiske metoder I",
//     13.august 2001, oppgave 3.

//     Laget av Frode Haug, HiG, august 2001.
//     Litt endret/modifisert av FrodeH, HiG, hõsten 2003


#include <iostream>       //  cout 
using namespace std;


struct node  {
  int id;                 //  Nodens ID/navn.
  int avstand;            //  Antall mellomliggende kanter til nërmeste Üpning.
  node *left, *right;     //  Pekere til venstre og hõyre subtre/barn.
  node *sti;              //  Retning (node) mot nërmeste Üpning.

  node(node* l, node* r, node* s, int i, int a) 
    { left = l;  right = r;  sti = s;  id = i;  avstand = a; }
};


                          //  OPPGAVE A:
/*
PÜ tegningene er "avstand" angitt i parantes bak hver nodes "id".
Der "avstand" er lik 0, vil "sti" vëre NULL, og er ikke pÜtegnet.
"sti"-pekeren er tegnet som en pil med knekk.


            5(1)---                  -----5(2)
          /   \   |                  |  /   \
         /     \  V                  V /     \
   ----8(1)     7(0)             ----8(1)  ---7(1)
   |  / \        \               |  / \    | / \
   V /   \        \              V /   \   V/   \
   6(0)  4(0)      9(0)         6(0)  4(0) 3(0) 9(0)
        /                            /
       /                            /
      2(0)                         2(0)


*/

                          //  OPPGAVE B:

void skriv_indre(node* rot)  {      //  Skriver rekursivt alle indre noder:
  if (rot)  {                       //  Noden selv finnes:
     if (rot->avstand > 0)          //  Indre node nÜr har avstand til Üpning.
        cout << rot->id << '(' << rot->avstand <<')' << ' ';   // Node-data.
     skriv_indre(rot->left);        //  Skriver de to subtrërne:
     skriv_indre(rot->right);       
  }
}

void skriv_aapne(node* rot)  {      //  Skriver rekursivt alle Üpne noder:
  if (rot)  {                       //  Noden selv finnes:
     if (rot->avstand == 0)         //  èpen node da ingen avstand til Üpning.
        cout << rot->id << '(' << rot->avstand <<')' << ' ';   // Node-data.
     skriv_aapne(rot->left);        //  Skriver de to subtrërne:
     skriv_aapne(rot->right);
  }
}

void skriv_indre_og_aapne(node* rot)  {
  cout << "\n\tIndre noder:  ";   skriv_indre(rot);
  cout << "\n\tèpne noder:   ";   skriv_aapne(rot);
}


                          //  OPPGAVE C:

void oppdater(node* rot)  {                      //  Oppdaterer "rot":
  if (rot->left == NULL  ||  rot->right == NULL)  {   //  Har max. ett barn:
     rot->sti = NULL;  rot->avstand = 0;         //  Nullstiller variable.
  } else {                                       //  Har to barn:
                                 //  Venstre subtre inneholder nërmeste Üpning:
     if (rot->left->avstand <= rot->right->avstand)  {
                                 //  Setter 2x variable:
        rot->sti = rot->left;  rot->avstand = rot->left->avstand + 1;
     } else {                    //  Hõyre subtre inneholder nërmeste Üpning:
                                 //  Setter 2x variable: 
        rot->sti = rot->right;  rot->avstand = rot->right->avstand + 1;
     }
  }
}

void stifinner(node* rot)  {
  if (rot)  {
     stifinner(rot->left);       //  Oppdaterer venstre subtre.
     stifinner(rot->right);      //  Oppdaterer hõyre subtre.
     oppdater(rot);              //  Fõr en selv oppdateres pÜ grunnlag av
  }                              //    verdier allerede rekursivt satt nede
                                 //    hos barna/de to subtrërne.
}


                          //  OPPGAVE D:

void sett_inn(node *rot, int v)  {
  if (rot->sti)                        // Noden er en indre node, mÜ fõlge ned
     sett_inn(rot->sti, v);            //   til nërmeste Üpning (via "sti").

  else if (rot->left == NULL)          //  Intet venstre barn/subtre.
     rot->left = new node(NULL, NULL, NULL, v, 0);   //  Hekter pÜ nytt 
                                                     //    til venstre.
  else                                 //  Intet hõyre barn/subtre.
     rot->right = new node(NULL, NULL, NULL, v, 0);  //  Hekter pÜ nytt 
                                                     //    til hõyre.
  oppdater(rot);                       //  Uansett sÜ oppdateres man selv.

//  Om man pÜ et tidspunkt bakover/oppover i rekursjonen kommer tilbake til
//  en node der "avstand" forblir uendret etter at "oppdater" er kalt,
//  kunne oppdateringen faktisk ha stanset. Dette skjer hvis noden hadde en
//  annen likeverdig nërmeste Üpning enn den som stien pekte ut.
}


                          //  GLOBALE VARIABLE:
node *a, *b, *c, *d, *e, *f, *g, *h, *tre;


                          //  EKSTRA FUNKSJON FOR è INITIERE DATASTRUKTUREN:

                          //  Bygger opp tre som angitt pÜ figuren i oppgave-
void lag_tre()  {         //    teksten og som lõsning pÜ oppgave A
                          //    FùR innsetting av node med "id" lik "3".
  d = new node(NULL, NULL, NULL, 6, 0);
  f = new node(NULL, NULL, NULL, 9, 0);
  g = new node(NULL, NULL, NULL, 2, 0);
  c = new node(NULL,    f, NULL, 7, 0);
  e = new node(   g, NULL, NULL, 4, 0);
  b = new node(   d,    e,    d, 8, 1);
  a = new node(   b,    c,    c, 5, 1);
  tre = a;
}

void lag_soppel_i_treet()  {          //  Fyller "sti" og "avstand" i hver
  a->sti = NULL;   a->avstand = -1;   //    node med irrelevante verdier.
  b->sti = NULL;   b->avstand = -1;
  c->sti = NULL;   c->avstand = -1;
  d->sti = NULL;   d->avstand = -1;
  e->sti = NULL;   e->avstand = -1;
  f->sti = NULL;   f->avstand = -1;
  g->sti = NULL;   g->avstand = -1;
};


int main()   {            //  HOVEDPROGRAMMET:
  lag_tre();

  cout << "\nOppgave B:";
  skriv_indre_og_aapne(tre);     //  Oppgave B

  cout << "\n\nFõr oppgave C:";
  lag_soppel_i_treet();
  skriv_indre_og_aapne(tre);

  cout << "\nOppgave C:";
  stifinner(tre);                //  Oppgave C
  skriv_indre_og_aapne(tre);

  cout << "\n\nOppgave D:";
  sett_inn(tre, 3);              //  Oppgave D
  skriv_indre_og_aapne(tre);

  cout << "\n\nInnsetting av 11-14 etter oppgave D:";
  sett_inn(tre, 11);
  sett_inn(tre, 12);
  sett_inn(tre, 13);
  sett_inn(tre, 14);
  skriv_indre_og_aapne(tre);
  cout << "\n\n";
  return 0;
}
