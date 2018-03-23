//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \ EX_S03_3.CPP

//     L›sningsforslag til eksamen i 
//     "Algoritmiske metoder (I)", oppgave nr.3, 8.august 2003.

//     Laget av Frode Haug, HiG, august 2003.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>             //  cout
using namespace std;

                        //  STRUCT:
struct node  {
  node *l, *r;                  //  Pekere til venstre og h›yre subtre/barn.
  //  + andre data (som ID/key), 
  //    men disse er i denne oppgaven irrelevante.
};
                        //  TYPEDEF:
typedef node* itemType;

                        //  GLOBALE VARIABLE:
itemType z;

                        //  KLASSE:
class Stack  {                  //  Avskrift av s.26 i l‘reboka.
  private:
    itemType* stack;
    int p;
  public:
    Stack(int max = 100)
      {  stack = new itemType[max];  p = 0;  }
    ~Stack()
      {  delete [] stack;    }
    void push(itemType v)
      {  stack[p++] = v;     }
    itemType pop()
      {  return stack[--p];  }
    int empty()
      { return !p;           }
};


void traverser(itemType t)  {   //  Veldig lik s.60 i l‘reboka.
  if (t != z) {
     traverser(t->l);
     traverser(t->r);
     cout << 'N';
  } else
     cout << 'T';
}

                                //  SELVE OPPGAVEN:
itemType gentre(const int NN, char SS[])  {
  Stack stack(NN+1);            //  Lager en stakk.
  int i;                        //  L›kkevariabel.
  itemType rn;                  //  Hjelpepeker.
                                //  G†r gjennom HELE SS-arrayen:
  for (i = 0;  i < 2*NN+1;  i++)  {
      if (SS[i] == 'N')  {      //  Tegnet er 'N':
         rn = new node;         //  Lager ny node.
         rn->r = stack.pop();   //  Henter dens to subtr‘r
         rn->l = stack.pop();   //    ›verst fra stakken.
         stack.push(rn);        //  Legger noden p† stakken.
      } else if (SS[i] == 'T')  //  Tegnet er 'T':
         stack.push(z);         //  Legger en z-node ›verst p† stakken.
      else
         cout << "\n\nFEIL: Ikke bare N'er og T'er i S-arrayen!\n";
  }                             //  Den siste/›verste p† stakken er rota
  return stack.pop();           //     for HELE det genererte treet. 
}                               //     Returnerer denne.
                               

                        //  HOVEDPROGRAM:
int main()  {
  itemType root;                //  Peker til treets rot.
  char S[] = "TTTNNTTNN";       //  Utvidet postfix form for et tre.
  const int N = 4;              //  Antall reelle noder i dette treet.

  z = new node;                 //  Lager/setter z-noden.
  root = (N > 0) ? gentre(N, S) : z;  //  Lar 'root' peke til generert tre.
  traverser(root);              //  G†r gjennom dette treet og lager en
  cout << "\n\n";               //    "kontrollutskrift".
  return 0;         
}          
