//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_04.CPP

//   L›sningsforslag til oppgave nr.4  i  Algoritmiske metoder.


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



void visit(itemType t)  {              //  Skriver nodens ID/innhold.
  cout << t->info << " ";
}

void traversePreorder(itemType t)  {  //  Avskrift av s.60 i l‘reboka.
  if (t != z)  {
     visit(t);
     traversePreorder(t->l);
     traversePreorder(t->r);
  }
}

void traverseInorder(itemType t)  {  //  Avskrift av s.60 i l‘reboka.
  if (t != z)  {
     traverseInorder(t->l);
     visit(t);
     traverseInorder(t->r);
  }
}

void traversePostorder(itemType t)  {  //  Avskrift av s.60 i l‘reboka.
  if (t != z)  {
     traversePostorder(t->l);
     traversePostorder(t->r);
     visit(t);
  }
}

					                   //  Returnerer med verdien av
				   	                   //    uttrykket som ligger innunder
int verdien(itemType t)  {             //    noden 't' selv.
       if (t->info == '+')  return  verdien(t->l) + verdien(t->r);
  else if (t->info == '*')  return  verdien(t->l) * verdien(t->r);
  else {                                //  Noden inneholder en bokstav:
       cout << "\t" << t->info << ": ";
       int tall;    cin >> tall;   return tall;
  }
}



int main()  {
  itemType root;

  cout << "\n\nARITMETISK POSTFIX-uttrykk:  ";
  root = createTree();

  cout << "\nTreet traversert PREORDER:\n\t";
  traversePreorder(root);
  cout << "\n\nTreet traversert INORDER:\n\t";
  traverseInorder(root);
  cout << "\n\nTreet traversert POSTORDER:\n\t";
  traversePostorder(root);

  cout << "\n\n\n";
  cout << "\nRegner ut uttrykket:  " << verdien(root) << "\n\n";
  return 0;;
}
