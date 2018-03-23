//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S00_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     17.august 2000, oppgave 3.

//     Laget av Frode Haug, HiG,  august 2000.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



#include <iostream>          //  cout
#include <iomanip>           //  setw
#include <cstdlib>           //  (s)rand

using namespace std;

struct node  {
   char id;                  //  Nodens id/navn (en bokstav).
   int verdi;                //  Nodens verdi.
   int sum;                  //  Summen av alle barnas verdi.
   node* left;               //  Peker til venstre subtre.
   node* right;              //  Peker til h›yre subtre.
   node* forelder;           //  Peker til nodens "mor"/forelder.
};


node* z;                     //  z-noden som avslutter ethvert subtre.
node* root;                  //  Peker til treets rot.
int number = 0;              //  F›rste node har verdi=1 og id='A'.


void  sett_sum(node* p);                       //  OPPGAVE A.
void  sett_forelder(node* p);                  //  OPPGAVE B.
void  visit(node* t);                          //     Ekstra-kode kun
void  traverse(node* t);                       //       for † vise/displaye
node* generate2(int depth, int probability);   //       at oppgavens funksjoner
node* generate(int depth, int probability);    //       fungerer korrekt.



// ************************   HOVEDPROGAM:   *****************************

int main()  {
  char ch;

  srand(0);

  cout << "\nNodene i starttreet:\n";
                             //  Genererer hele treet (max. 6 niv†er,
  root = generate(5, 80);    //      80% sjanse for † lage et subtre)
  traverse(root);            //  Traverserer (og viser) treet.
  cin >> ch;

  cout << "\nOPPGAVE A:  Nodene etter at 'sum' er satt:\n";
  sett_sum(root);            //  Setter ALLE nodenes sum  (OPPGAVE A).
  traverse(root);            //  Traverserer (og viser) treet.
  cin >> ch;

  cout << "\n\nOPPGAVE B:  Nodene etter at 'forelder' er satt:\n";
  sett_forelder(root);       //  Setter ALLE nodenes foreldre  (OPPGAVE B).
  traverse(root);
  cout << "\n\n";
  return 0;
}


void sett_sum(node * p)  {              //  OPPGAVE A.
  if (p != z)  {                                  // Noden/roten er ikke tom:
     sett_sum(p->left);                           // Rekursiv setting av summen
     sett_sum(p->right);                          //   i hvert av subtr‘rne.
     p->sum = p->verdi;                           // Initierer egen sum.
     if (p->left != z)   p->sum += p->left->sum;  // Legger til summen for 
     if (p->right != z)  p->sum += p->right->sum; //   hvert av barna.
  }
}


void sett_forelder(node * p)  {        //  OPPGAVE B.
  if (p != z)  {                                  // Noden/roten er ikke tom:
     sett_forelder(p->left);                      // Rekursiv setting av foreldre
     sett_forelder(p->right);                     //   i hvert av subtr‘rne.
     p->forelder = z;                             // Initierer egen forelder.
     if (p->left != z)   p->left->forelder  = p;  // Setter hvert av barnas
     if (p->right != z)  p->right->forelder = p;  //   forelder til † v‘re 
  }                                               //   en selv.
}


void visit(node* t)  {       //  Viser innholdet i EN node.
  cout << setw(3) << t->verdi << ", " << t->id << ": " <<  setw(6) << t->sum;
  if (t->forelder != z)  cout << '\t' << t->forelder->id;
  cout << '\n';
}


void traverse(node* t)  {    //  Traverserer treet p† en INORDER m†te
  if (t != z)  {             //     (se side 60 i l‘reboka).
     traverse(t->left);
     visit(t);
     traverse(t->right);
  }
}
                             //  Rekursiv funksjon som (om mulig) genererer en
                             //    node og KANSKJE dets venstre og h›yre subtre.
                             //    Kalles av funksjonen 'generate'.
node* generate2(int depth, int probability)  {
  node* rot = z;                         //  Peker til det som returneres.
                                         //     NB: Initieres til 'z' !!
  if (depth > 0)  {                      //  Kan fortsatt legge til et niv†:
     if (rand() % 100 < probability)  {   //  Trukket tall i rett intervall:
        rot = new node;                  //  Lager en ny node.
        rot->left =  generate2(depth-1, probability);  //  Lager venstre subtre.
        rot->verdi = ++number;                         //  Legger inn egen verdi.
        rot->id = char('A' - 1 + number);              //  Legger inn egen ID.
        rot->sum = 0;                                  //  Nullstiller egen sum.
        rot->forelder = z;                             //  Nullstiller (ikke p†krevet).
        rot->right = generate2(depth-1, probability);  //  Lager h›yre subtre.
     }
  }
  return rot;                            //  Returnerer resultatet.
}

                             //  Funksjon kallet fra 'main'. Initierer f›rst 
                             //    noen verdier og kaller deretter 'generate2'.
node* generate(int depth, int probability)  {
  z = new node;  z->left = z;  z->right = z;  //  Initierer 'z'.
  return  generate2(depth, probability); //  F†r bygd opp treet rekursivt.
}                                        //   og returnerer dette.
