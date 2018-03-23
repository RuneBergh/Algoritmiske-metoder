//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H04_3.CPP

//     Løsningsforslag til eksamen i
//     "Algoritmiske metoder", oppgave nr.3, 3.desember 2004.

//     Laget av Frode Haug, HiG, november 2004.


#include <iostream>
using namespace std;

struct node;
node* z = NULL;
node* root = z;


struct node  {
  int key1, key2;
  bool key2filled;             //  = 'true' om key2 har en reell verdi.
  node *lsub, *msub, *rsub;
  node(int v)  {  key1 = v;  key2filled = false;  lsub = msub = rsub = z;  }
};


                    //  NB: Denne funksjonen kalles KUN når 't' inneholder
                    //      EN key har ingen subtrær (dvs. 't' er bladnode):
void set_key2(node* t, int v)  {      //  OPPGAVE A: 
  if (v < t->key1)  {                 //  Den nye er mindre enn den eksisterende:
     t->key2 = t->key1;               //  Flytter bare key1 til key2,
     t->key1 = v;                     //    og legger inn ny key1.
  } else                              //  Den nye er størst:
     t->key2 = v;                     //  Legger bare inn.
  t->key2filled = true;               //  Setter at key2 er tatt i bruk.
}



void display_sorted(node* t)  {       //  OPPGAVE B:
  if (t != z)  {                      //  't' er en reell node:
     display_sorted(t->lsub);         //  Skriver rekursivt venstre subtre.
     cout << t->key1 << ' ';          //  Skriver egen 1.key.
     display_sorted(t->msub);         //  Skriver rekursivt midtre subtre.
     if (t->key2filled) cout << t->key2 << ' ';  // Skriver evt.egen 2.key.
     display_sorted(t->rsub);         //  Skriver rekursivt høyre subtre.
  }
}


                                      //  OPPGAVE C:
node* find(node* t, int v)  {         //  Returnerer peker til søkt node eller
  if (t == z)  return z;              //    om ikke finner den så returneres 'z'.
  else  {
     if ( v == t->key1  ||                              //  Match/funn:
          (t->key2filled  &&  v == t->key2)) return t;  //    returnerer 't'.
     else if (v < t->key1)  return (find(t->lsub, v));  //  Leter rekursivt
     else if (v < t->key2)  return (find(t->msub, v));  //    videre i aktuelt
     else                   return (find(t->rsub, v));  //    subtre:
  }
/*  ITERATIVT:
  while (t != z  &&  v != t->key1  && (!t->key2filled || v != t->key2))
    if (v < t->key1)  t = t->lsub;
    else if (v < t->key2)  t = t->msub;
    else t = t->rsub;
  return t;	
*/
}


                                      //  OPPGAVE D:
bool insert(node* t, int v)  {        //  Setter inn en ny verdi i en node med
	                                  //    plass (2-node) eller som en helt ny
	                                  //    node nederst (bladnode):
  if (root == z)  root = new node(v);       //  Spesialtilfelle: Tomt tre.
  else  {                                   //  Reelt tre finnes:
    if ( v == t->key1  ||                   //  Duplikater verdier får IKKE forekomme.
         (t->key2filled  &&  v == t->key2))  return false;
    if (!t->key2filled)  set_key2(t, v);    //  Plass til ny i bladnode? Legg inn.
	                                        //  Må opprette ny node med 'v' i:
    else if (v < t->key1)  {                //  Mindre enn 1.key:
       if (t->lsub == z) t->lsub = new node(v); //  Tomt: legges inn som ny node.
       else return(insert(t->lsub, v));     //  Tre:  søker videre for inserting.
    } else if (v < t->key2)  {              //  Mellom 1. og 2.key:
       if (t->msub == z) t->msub = new node(v); //  Tomt: legges inn som ny node.
       else return(insert(t->msub, v));     //  Tre:  søker videre for inserting.
    }  else  {                              //  Større enn 2.key:
       if (t->rsub == z) t->rsub = new node(v); //  Tomt: legges inn som ny node.
       else return(insert(t->rsub, v));     //  Tre:  søker videre for inserting.
    }
  }
  return true;                              //  Verdi lagt inn: returnerer 'true'.
}


int main()  {
  if (!insert(root, 36)) cout << "\nDuplikat av 36"; //  Bygger treet:
  if (!insert(root, 73)) cout << "\nDuplikat av 73"; //
  if (!insert(root, 18)) cout << "\nDuplikat av 18"; //               36      73
  if (!insert(root, 89)) cout << "\nDuplikat av 89"; //           /        |     \      .
  if (!insert(root, 57)) cout << "\nDuplikat av 57"; //          /         |      \     .
  if (!insert(root, 31)) cout << "\nDuplikat av 31"; //     18    31    57  68   80 89
  if (!insert(root, 68)) cout << "\nDuplikat av 68"; //     /   |   \    |   \          .
  if (!insert(root, 80)) cout << "\nDuplikat av 80"; //    /    |    \  41  63 66
  if (!insert(root, 24)) cout << "\nDuplikat av 24"; //  9 14  24  32 34 
  if (!insert(root, 34)) cout << "\nDuplikat av 34";
  if (!insert(root, 32)) cout << "\nDuplikat av 32";
  if (!insert(root, 14)) cout << "\nDuplikat av 14";
  if (!insert(root,  9)) cout << "\nDuplikat av 9"; 
  if (!insert(root, 41)) cout << "\nDuplikat av 41";
  if (!insert(root, 66)) cout << "\nDuplikat av 66";
  if (!insert(root, 63)) cout << "\nDuplikat av 63";
  if (!insert(root, 32)) cout << "\nDuplikat av 32"; //  Duplikat!
  if (!insert(root, 14)) cout << "\nDuplikat av 14"; //  Duplikat!

  cout << "\n\nInorder/sortert traversering av treet:\n  ";
  display_sorted(root);
  cout << '\n';

  cout << "\n68 finnes"; if (find(root, 68) == z)  cout << " IKKE";  // Finnes
  cout << "\n32 finnes"; if (find(root, 32) == z)  cout << " IKKE";  // Finnes
  cout << "\n17 finnes"; if (find(root, 17) == z)  cout << " IKKE";  // Finnes IKKE!
  cout << "\n41 finnes"; if (find(root, 41) == z)  cout << " IKKE";  // Finnes
  cout << "\n28 finnes"; if (find(root, 28) == z)  cout << " IKKE";  // Finnes IKKE!
  cout << "\n50 finnes"; if (find(root, 50) == z)  cout << " IKKE";  // Finnes IKKE!
  cout << "\n\n";
  return 0;
}
