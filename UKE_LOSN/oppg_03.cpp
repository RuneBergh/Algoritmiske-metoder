//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_03.CPP

//   L›sningsforslag til oppgave nr.3  i  Algoritmiske metoder.


#include <iostream>

using namespace std;


struct Node                            //  Node.
  {  char info;  Node* l, * r;  };

typedef Node* itemType;                //  Typedef.

itemType z;                            //  Global 'z'.


class Stack  {                         //  Avskrift av s.26 i l‘reboka.
  private:
    itemType* stack;
    int p;
  public:
    Stack(int max = 100)
      {  stack = new itemType[max];  p = 0;  }
    ~Stack()
      {  delete [] stack;       }
    void push(itemType v)
      {  stack[p++] = v;     }
    itemType pop()
      {  return stack[--p];  }
    int empty()
      { return (!p);         }
};



itemType createTree()  {              //  Avskrift av s.41 i l‘reboka.
  itemType x;
  char c;
  Stack stack(50);

  z = new Node;  z->l = z;  z->r = z;

  while ((c = cin.get()) != '\n')  {
    while (c == ' ')  cin.get(c);
    x = new Node();
    x->info = c;  x->l = z;  x->r = z;
    if (c == '+'  ||  c == '*')  {
       x->r = stack.pop();  x->l = stack.pop();
    }
    stack.push(x);
  }
  return stack.pop();
}


				       //  Rekursiv funksjon som finner
int antNoder(itemType t)  {           //    totalt antall noder i hele treet.
  int antL = 0, antR = 0;
  if (t->l != z)  antL = antNoder(t->l);    //  Finner rekursivt antallet i
  if (t->r != z)  antR = antNoder(t->r);    //    venstre og h›yre subtre.
  return  1 + antL + antR;             //  Returnerer med subtreenes antall
}                                      //    pluss en selv ('1').


int antExtern(itemType t)  {           //  Finner enkelt antall external-noder.
  return  antNoder(t) + 1;             //  Jfr. regel 4.3 s.39
}



int antFulleNoder = 0;                 //  Global variabel, som 'visit1'
				                       //    teller opp.
void visit1(itemType t)  {
  if (t->l != z  &&  t->r != z)        //  TO interne noder (barn) eksisterer.
     ++antFulleNoder;
}
				       //  Rekursiv funksjon som finner antall
				       //    fulle (med TO barn) noder.
				       //    Den kaller 'visit1' som, dersom
				       //    noden har TO barn, teller opp en
				       //    global variabel.
void antFulle(itemType t)  {           //  Avskrift av s.60 i l‘reboka.
  if (t != z)  {
     visit1(t);                        //  Vilk†rlig om 'visit1' forekommer
     antFulle(t->l);                   //    f›r, mellom eller etter de to
     antFulle(t->r);                   //    rekursive kallene.
  }
}



int maxHoyde = 0, y = 0;              //  Globale variable som de to
				                      //    funksjonene under teller opp.
void visit2(itemType t)  {
  if (y > maxHoyde)                   //  Ny max. h›yde er funnet.
     maxHoyde = y;
}

void treetsHoyde(itemType t)  {       //  Avskrift av s.61 i l‘reboka.
  y++;
  if (t != z)  {
     treetsHoyde(t->l);
     treetsHoyde(t->r);                //  Vilk†rlig om 'visit2' forekommer
     visit2(t);                        //    f›r, mellom eller etter de to
  }                                    //    rekursive kallene.
  y--;
}


int main()  {
  itemType root;

  cout << "\n\nARITMETISK POSTFIX-uttrykk:  ";
  root = createTree();

  cout << "\nAntall noder i treet:        " << antNoder(root);
  cout << "\nAntall external-noder i treet:   " << antExtern(root);
  antFulle(root);
  cout << "\nAntall FULLE noder i treet:  " << antFulleNoder;
  treetsHoyde(root);
  cout << "\nTreets maksimale h›yde:      " << maxHoyde << "\n\n";
  return 0;
}
