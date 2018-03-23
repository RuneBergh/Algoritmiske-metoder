#include <iostream>
using namespace std;

struct Node  {char info;  Node *l,*r;bool visited;
    Node(){visited = false;}};


typedef Node* itemType;

itemType z;

class Stack
{
    private:
     itemType *stack;
     int p;
    public:
        Stack(int max=100)
            { stack = new itemType[max]; p=0; }
        ~Stack()
            {delete [] stack; }
         void push(itemType v)
            {stack[p++] = v;}
         itemType pop()
            {return stack[--p];}
         int empty()
            {return (!p);}
};



itemType createTree()
{

 char c; Stack stack(50);
 itemType x;
 z = new Node; z->l = z; z->r = z;
    while ((c = cin.get()) != '\n')
    {
        while(c==' ') cin.get(c);
        x = new Node;
        x->info = c; x->l=z; x->r=z;
        if (c=='+' || '*')
            {
                x->r =stack.pop();x->l =stack.pop();
            };
        stack.push(x);
    }
    return stack.pop();
};


void visit(itemType t)
{
  cout << t->info << ' '; t->visited=false;
};


void traverse(itemType t)
{
    Stack stack(50);
    stack.push(t);
    while (!stack.empty())
    {
        t = stack.pop(); visit(t);
        if (t->r != z) stack.push(t->r);
        if (t->l != z) stack.push(t->l);
    };
};



int main()
{
    cout << "\nPOSTFIX-uttrykk (bokstaver og operatorer, jfr.s.40-41):\n\t";
    itemType root;
    root=createTree();
    traverse(root);
    return 0 ;
}

