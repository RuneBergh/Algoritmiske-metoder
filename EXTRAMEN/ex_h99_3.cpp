//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H99_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     13.desember 1999, oppgave 3.

//     Laget av Frode Haug, HIG,  desember 1999.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>          //  cout
#include <cstdlib>           //  (s)rand

using namespace std;


struct node {
   char ID;                  //  Nodens id/navn (en bokstav).
   int  nivaa;               //  Nodens niv† i treet ift. rotnoden.
   node* left;               //  Peker til venstre subtre.
   node* right;              //  Peker til h›yre subtre.
};


node* z;                     //  z-noden som avslutter ethvert subtre.
node* root;                  //  Peker til treets rot.
int number = 65;             //  F›rste node er 'A' (ASCII-tegn nr.65).


void  sett_nivaa(node* p);                                     //  OPPGAVE A.
void  sett_verdier(node* p, int & sum_nivaa, int & antall);    //  OPPGAVE B.
void  skriv_forfedre(node* p);                                 //  OPPGAVE C.
void  blad_til_rot(node* p, node* blad);           //  Ekstra ifm. oppgave C.
void  visit(node* t);
void  traverse(node* t);
node* generate2(int depth, int probability);
node* generate(int depth, int probability);



// ************************   HOVEDPROGAM:   *****************************

int main()  {
  int sum_niva, ant;
  char ch;

  srand(0);

  cout << "\nNodene i starttreet:\n";
                             //  Genererer hele treet (max. 6 niv†er,
  root = generate(5, 80);    //      80% sjanse for † lage et subtre)
  traverse(root);            //  Traverserer (og viser) treet.
  cin >> ch;

  cout << "\n\n\nOPPGAVE A:  Nodene etter at 'nivaa' er satt:\n";
  root->nivaa = 0;           //  Initierer rotas niv†.
  sett_nivaa(root);          //  Setter ALLE nodenes niv† (OPPGAVE A).
  traverse(root);            //  Traverserer (og viser) treet.
  cin >> ch;

  cout << "\n\n\nOPPGAVE B:  ";
  sum_niva = ant = 0;        //  Nullstiller to referansevariable.
  sett_verdier(root, sum_niva, ant);  //  Finner summen av nodenes niv†
                                      //      og antall noder (OPPGAVE B).
  cout << "Gjennomsnittsniv†et i treet:  " << float(sum_niva)/ant;
  cin >> ch;

  cout << "\n\n\nOPPGAVE C:  Alle bladnodenes forfedre:\n";
  skriv_forfedre(root);      //  Skriver forgjengere til bladnodene (OPPGAVE C).
  cout << "\n\n";
  return 0;
}


void sett_nivaa(node * p)  { //  OPPGAVE A.
                             //  NB: Vet at 'p' ALLTID er ulikt 'z'  !!!!
  if (p->left != z)  {                //  Har et venstre barn som er ulikt 'z'.
     p->left->nivaa = p->nivaa + 1;   //  Setter barnets niv†.
     sett_nivaa(p->left);             //  Det samme rekursivt for venstre barn.
  }

  if (p->right != z)  {               //  Har et h›yre barn som er ulikt 'z'.
     p->right->nivaa = p->nivaa + 1;  //  Setter barnets niv†.
     sett_nivaa(p->right);            //  Det samme rekursivt for h›yre barn.
  }
}


void sett_verdier(node* p, int & sum_nivaa, int & antall)  {    //  OPPGAVE B.
  if (p != z)  {                      //  Noden er IKKE en external-node.
     sum_nivaa += p->nivaa;           //  Summerer opp nodenes totale niv†
     antall++;                        //      og teller opp deres totale antall.
                                      //  NB: Overst†ende to injer st†r her
                                      //      preorder, men de kunne like gjerne
                                      //      st† inorder eller postorder !!!
     sett_verdier(p->left,  sum_nivaa, antall);   //  Bes›ker venstre subtre.
     sett_verdier(p->right, sum_nivaa, antall);   //  Bes›ker h›yre subtre.
  }
}


void skriv_forfedre(node * p)  {      //  OPPGAVE C.
  if (p != z)  {                              //  Noden er ikke 'z'.
     if (p->left == z  &&  p->right == z)  {  //  Noden er en bladnode:
                             //  G†r fra roten og skriver ut nodene p† veien
                             //     ned til bladnoden. Finner veien dit da
                             //     treet er et bin‘rt s›ketre, og kjenner 
                             //     bladnodens ID:
         cout << "\n\t";
         node* q = root;                          //  Starter i rota.
         while (1)  {                             //  "Evig" l›kke til 'break'.
           cout << q->ID << ' ';                  //  Skriver forfedres ID.
           if (p->ID < q->ID) q = q->left;        //  Bladnoden er mindre.
           else if (p->ID > q->ID) q = q->right;  //  Bladnoden er st›rre.
           else break;                            //  Funnet bladnoden.
         }

//  Istedet for while-l›kka over KUNNE vi ha laget en rekursiv funksjon som
//  starter i rota og leter seg ned til bladnoden vha. treets bin‘re sortering.
//  Den skriver ut nodenes navn BAKLENGS (FRA bladnode og OPP TIL rota) n†r
//  den trekker seg tilbake/terminerer.

//        blad_til_rot(root, p);

     }
     skriv_forfedre(p->left);                 //  Skriv forfedre for bladnoder 
     skriv_forfedre(p->right);                //    i venstre og h›yre subtree.
  }
}


void  blad_til_rot(node* p, node* blad)  {   //  Ekstra ifm. oppgave C.
  if (p != blad)  {                          //  Har IKKE n†dd fram.
     if (blad->ID < p->ID)  blad_til_rot(p->left, blad);  // Bladnode er mindre.
     else blad_til_rot(p->right, blad);                   // Bladnode er st›rre. 
  }
  cout << p->ID << ' ';                      //  Skriver nodens ID.
}


void visit(node* t)  {       //  Viser innholdet i EN node.
  cout << t->ID << ": " << t->nivaa << "  ";
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
     if ((rand() % 100) < probability)  {   //  Trukket tall i rett intervall:
        rot = new node;                  //  Lager en ny node.
        rot->left =  generate2(depth-1, probability);  // Lager venstre subtre.
        rot->ID = char(number++);        //  Legger inn egen ID.
        rot->right = generate2(depth-1, probability);  // Lager h›yre subtre.
     }
  }
  return rot;                            //  Returnerer resultatet.
}

                             //  Funksjon kallet fra 'main'. Initierer f›rst 
                             //    noen verdier og kaller deretter 'generate2'.
node* generate(int depth, int probability)  {
  node* rot;                             //  Peker til det som returneres.
  rot = z = new node;  z->left = z;  z->right = z;  //  Initierer 'z' og 'rot'.
  rot = generate2(depth, probability);   //  F†r bygd opp treet rekursivt.
  return rot;                            //  Returnerer resultatet.
}
