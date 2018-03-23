//  ***************************************************************
//  ***************************************************************
//  ***                                                         ***
//  ***                                                         ***
//  ***      NB:  VIRKER KUN NèR CONIO.H KAN BRUKES !!!!!!      ***
//  ***                                                         ***
//  ***                                                         ***
//  ***************************************************************
//  ***************************************************************


#if !defined(__BAL_TREE_H)
#define  __BAL_TREE_H


#include <iostream>        //  cout
using namespace std;


const char itemMIN   = char(0);
      char infoNIL[] = "Z-noden";

typedef unsigned char  itemType;
typedef char* infoType;
enum Color { BLACK, RED };


struct Node  {
	itemType key;   infoType info;   Color b;     //  NYTT:  'b'.
	Node *l, *r;
	Node(itemType k, infoType i, Color rb, Node* ll, Node* rr)  {
		key = k;   info = i;   b = rb;   l = ll;  r = rr;
	}
};


class BalTree  {                                  //  Jfr.s.204 i lëreboka.
  private:
	int antRot, minSti, maxSti, antSti, y;        //  NYTT: Oppgave C.
	int totSti;
	Node *x, *p, *g, *gg;                         //  NYTT:  Fire variable.
	Node *head, *z;

	Node* rotate(itemType v, Node* y);
	void split(itemType v);
	void display2(Node* p, int y, int x1, int x2);      //  Selvlaget
	void traverse(Node* t);                             //  NYTT: Oppgave C.

public:
	BalTree()  {                                        //  NYTT:  Jfr.s.226.
		z = new Node(0, infoNIL, BLACK, 0, 0);
		z->l = z;   z->r = z;  
		antRot = 0;                                     //  NYTT:  Oppgave C.
		head = new Node(itemMIN, 0, BLACK, 0, z);
	}
	~BalTree()  {   /*  Slette hele treet .......  */  }
    void insert(itemType v, infoType info);
    void display(int x1, int x2);                       //  Selvlaget
    void status();                                      //  Selvlaget
};


						                                //  NYTT:  Jfr.s.221.
void BalTree :: insert(itemType v, infoType info)  {
  x = head;  p = head;  g = head;
  while (x != z)  {
    gg = g;  g = p;  p = x;
    x =  (v < x->key)  ?  x->l  :  x->r;
    if (x->l->b  &&  x->r->b)  split(v);
  }
  x = new Node(v, info, RED, z, z);
  if (v < p->key)  p->l = x;   else  p->r = x;
  split(v);  head->r->b = BLACK;
}


void BalTree :: split(itemType v)  {                    //  NYTT:  Jfr.s.226.
  x->b = RED;  x->l->b = BLACK;  x->r->b = BLACK;
  if (p->b)  {
     g->b = RED;
     if (v < g->key  !=  v < p->key)  {
	    ++antRot;                                       //  NYTT:  Oppgave C.
	    p = rotate(v, g);
     }
     ++antRot;                                          //  NYTT:  Oppgave C.
     x = rotate(v, gg);
     x->b = BLACK;
  }
}

						                                //  NYTT:  Jfr.s.225.
Node* BalTree :: rotate(itemType v, Node* y)  {
  Node *c, *gc;
  c =  (v < y->key)  ?  y->l  :  y->r;
  if (v < c->key)
    {  gc = c->l;  c->l = gc->r;  gc->r = c;  }
  else
    {  gc = c->r;  c->r = gc->l;  gc->l = c;  }
  if (v < y->key)  y->l = gc;  else y->r = gc;
  return gc;
}


void BalTree :: display2(Node* p, int y, int x1, int x2)  {
  if (p != z)  {
     int m = (x1+x2)/2;   gotoxy(m, y);
     cout << p->key << '(' << p->b << ')';
     display2(p->l, y+2, x1, m);
     display2(p->r, y+2, m, x2);
  }
}


void BalTree :: display(int x1, int x2)  {
  display2(head->r, 1, x1, x2);
}



// ***************************  OPPGAVE C:  *******************************

void BalTree :: traverse(Node* t)  {      //  Jfr. s.61 i lëreboka.
  if (t != z)  {
     y++;
     traverse(t->l);
     traverse(t->r);
     y--;
  } else  {
    totSti += y;  ++antSti;
    if (y < minSti)  minSti = y;
    if (y > maxSti)  maxSti = y;
  }
}


void BalTree :: status()  {                      //  Selvlaget.
  cout << "\n\nAntall rotasjoner:  " << antRot;
  minSti = 1000;   maxSti = 0;   totSti = 0;   antSti = 0;  y = 0;
  traverse(head->r);
  cout << "  \nKorteste sti:       " << minSti;
  cout << "  \nLengste sti:        " << maxSti;
  cout << "  \nGj.snittlig sti:    " << totSti/antSti;
}

#endif
