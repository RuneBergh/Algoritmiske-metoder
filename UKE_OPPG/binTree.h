//  ***************************************************************
//  ***************************************************************
//  ***                                                         ***
//  ***                                                         ***
//  ***      NB:  VIRKER KUN NèR CONIO.H KAN BRUKES !!!!!!      ***
//  ***       f                                                  ***
//  ***                                                         ***
//  ***************************************************************
//  ***************************************************************


#if !defined(__BIN_TREE_H)
#define  __BIN_TREE_H


#include <iostream>        //  cout
using namespace std;

const char itemMIN   = char(0);
      char infoNIL[] = "Z-noden";

typedef unsigned char  itemType;
typedef char* infoType;


class BinTree  {                                 //  Jfr.s.204 i lëreboka.
  private:
    struct Node  {
      itemType key;   infoType info;
      Node *l, *r;
      Node(itemType k, infoType i, Node* ll, Node* rr)
	  {  key = k;   info = i;  l = ll;  r = rr;  }
    };
    Node *head, *z;
    void display2(Node* p, int y, int x1, int x2);    //  Selvlaget

  public:
    BinTree()
      {  z = new Node( 0, infoNIL, 0, 0);
	 head = new Node(itemMIN, 0, 0, z);  }
    ~BinTree()  {   /*  Slette hele treet .......  */  }
    infoType search(itemType v);
    void     insert(itemType v, infoType info);
    void     remove(itemType v);
    void     display(int x1, int x2);                        //  Selvlaget
};


infoType BinTree :: search(itemType v)  {        //  Jfr.s.204 i lëreboka.
   Node* x = head->r;
   z->key = v;
   while (v != x->key)
      x =  (v < x->key)  ?  x->l  :  x->r;
   return x->info;
}

						 //  Jfr.s.206 i lëreboka.
void BinTree :: insert(itemType v, infoType info)  {
   Node *p, *x;
   p = head;  x = head->r;
   while (x != z)
     {  p = x;  x = (v < x->key)  ?  x->l  :  x->r;  }
   x = new Node(v, info, z, z);
   if (v < p->key)  p->l = x;
   else             p->r = x;
}


void BinTree :: remove(itemType v)  {            //  Jfr.s.210 i lëreboka.
  Node *c, *p, *x, *t;
  z->key = v;
  p = head;  x = head->r;
  while (v != x->key)
    {  p = x;  x = (v < x->key)  ?  x->l  :  x->r;  }
  if (x != z)  {                  //  Ny kodelinje:  KUN nÜr noden finnes:
     t = x;
     if (t->r == z)  x = x->l;
     else if (t->r->l == z)  {  x = x->r;  x->l = t->l;  }
     else  {
       c = x->r;   while (c->l->l != z)  c = c->l;
       x = c->l;  c->l = x->r;
       x->l = t->l;  x->r = t->r;
     }
     delete t;
     if (v < p->key)  p->l = x;
     else             p->r = x;
  }
}


void BinTree :: display2(Node* p, int y, int x1, int x2)  {
  if (p != z)  {
     int m = (x1+x2)/2;   gotoxy(m, y);   cout << p->key;
     display2(p->l, y+2, x1, m);
     display2(p->r, y+2, m, x2);
  }
}


void BinTree :: display(int x1, int x2)  {
  display2(head->r, 1, x1, x2);
}

#endif
