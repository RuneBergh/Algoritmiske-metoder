//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H05_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     8.desember 2005, oppgave nr.3.

//     Laget av Frode Haug, HiG,  november 2005.


#include <fstream>         //  ifstream
#include <iostream>        //  cout

using namespace std;

struct node;               //  Pre-deklarasjon.
node* z;                   //  z-noden som avslutter ethvert subtre.

struct node {
   int  ID;                //  Nodens id/navn (et tall).
   node* left;             //  Peker til venstre subtre.
   node* right;            //  Peker til høyre subtre.
   node(int id)  {  ID = id; left = right = z;  }
};


node* root;                //  Peker til treets rot.
int **preinpost;           //  2-dimensjonal array med nodenes navn/id 
                           //     pre-/in-/postorder rekkefølge.
int ant;                   //  Antall noder i treet (fra fil).
int nr;                    //  Kommet til indeks nr.'nr' i pre-/post-array.

void  les_fra_fil();
void  visit(node* t);
void  traverse(node* t);
int   finn(int a[], int n, const int MAX);
node* pre_in (int pre[],  int & n, int in[], int l, int r);    //  OPPGAVE A.
node* post_in(int post[], int & n, int in[], int l, int r);    //  OPPGAVE B.



// ************************   HOVEDPROGAM:   *****************************

int main()  {
  z = new node(0);  

  les_fra_fil();

  nr = -1;
  root = pre_in(preinpost[0], nr, preinpost[1], 0, ant-1);
  cout << "Bygd opp vha. preorder og inorder, traversert preorder:\n";
  traverse(root);

  nr = ant;
  root = post_in(preinpost[2], nr, preinpost[1], 0, ant-1);
  cout << "\nBygd opp vha. inorder og postorder, traversert preorder:\n";
  traverse(root);

  return 0;
}

                                      //  OPPGAVE A:
node* pre_in(int pre[], int & n, int in[], int l, int r)  {
  node* nod;                          //  Peker til generert/laget node.
  int i;                              //  Indeks i inorder-array.
  if (r >= l)  {                      //  Node(r) igjen til subtrær:
	++n;                              //  'n' for preorder-array telles opp.
    nod = new node(pre[n]);           //  Bygger/lager en ny node.   
    i = finn(in, pre[n], ant);        //  Finner dennes indeks i inorder array.
    nod->left  = pre_in(pre, n, in, l, i-1);  //  Hekter på henholdsvis venstre
    nod->right = pre_in(pre, n, in, i+1, r);  //    og høyre subtre:
	return nod;                               //  Returnerer oppbygd (sub)tre.
  } else
    return z;                                 //  Intet tre - returnerer 'z'.
}

                                      //  OPPGAVE B:
node* post_in(int post[], int & n, int in[], int l, int r)  {
  node* nod;                          //  Peker til generert/laget node.
  int i;                              //  Indeks i inorder-array.
  if (r >= l)  {                      //  Node(r) igjen til subtrær:
	--n;                              //  'n' for postorder-array telles ned.
    nod = new node(post[n]);          //  Bygger/lager en ny node.   
    i = finn(in, post[n], ant);       //  Finner dennes indeks i inorder array.
    nod->right = post_in(post, n, in, i+1, r); //  Hekter på henholdsvis høyre  
    nod->left  = post_in(post, n, in, l, i-1); //    og venstre subtre:
	return nod;                                //  Returnerer oppbygd (sub)tre.
  } else
    return z;                                  //  Intet tre - returnerer 'z'.
}


int finn(int a[], int n, const int MAX)  {
  for (int i = 0;  i < MAX;  i++)           //  Returnerer alltid(?!) indeksen
	if (a[i] == n)  return i;               //     for 'n' i arrayen 'a'.
  cout << "\nERROR (denne meldingen skal ikke forekomme)!\n"; // IKKE komme hit!
  return -1;                                //  Ellers returneres dummy -1.
}


void les_fra_fil()  {
  ifstream innfil("ex_h05_3.dta");     //  Filen med ulike order rekkefølger.
  int i, j;                            //  2x løkkevariable.
  if (innfil)  {                       //  Filen finnes:
     innfil >> ant;                    //  Leser antall noder i treet.
     preinpost = new int*[3];          //  Lager 1.dimensjon 3 lang.
	 for (i = 0;  i < 3;  i++)         
		 preinpost[i] = new int[ant];  //  Lager 2.dimensjon 'ant' lang.
     for (i = 0;  i < 3;  i++)         //  Leser ALT fra filen (dvs. pres-/in-
		 for (j = 0;  j < ant;  j++)   //    og postorder rekkefølgen.
			innfil >> preinpost[i][j];
  } else
	cout << "\nFant ikke filen 'EX_H05_3.DTA!'\n";
}


void visit(node* t)  {       //  Viser innholdet i EN node og dets barn:
  cout << t->ID << ": " << t->left->ID <<  "  " <<  t->right->ID << '\n';
}


void traverse(node* t)  {    //  Traverserer treet på pre-, in- eller postorder
  if (t != z)  {             //     måte (se side 60 i læreboka):
     visit(t);
     traverse(t->left);
     traverse(t->right);
  }
}
