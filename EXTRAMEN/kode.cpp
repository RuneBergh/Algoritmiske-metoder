//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H02_3.CPP

//     L›sningsforslag til eksamen i 
//     "Algoritmiske metoder (I)", oppgave nr.3, 9.desember 2002.

//     Laget av Frode Haug, HiG, november 2002.
//     Koden for † generere tr‘r er hentet fra side 204 og 206 i l‘reboka.


#include <iostream>        //  cout

using namespace std;

                        //  STRUCT:
struct node
{
char key;
node *l, *r;
node(char k, node* ll, node* rr)
{
key = k;  l = ll;  r = rr;
}
};

                        //  GLOBALE VARIABLE:
node *head, *z;

                        //  DEFINISJON AV FUNKSJONER:
void display2(node* p, int y, int x1, int x2)
{
if (p != z)
{
int m = (x1+x2)/2;   gotoxy(m, y);   cout << p->key;
display2(p->l, y+2, x1, m);
display2(p->r, y+2, m, x2);
}
}

void display(int x1, int x2)
{
display2(head->r, 1, x1, x2);
}


void insert(char v)
{
node *p, *x;
p = head;  x = head->r;
while (x != z)
{
p = x;  x = (v < x->key)  ?  x->l  :  x->r;
}
x = new node(v, z, z);
if (v < p->key)  p->l = x;
else             p->r = x;
}

                        //  OPPGAVE 3A:
boolean bst(node* t)
{
if (t != z)         //  Om venste/h›yre subtre IKKE er bin‘rt s›ketre
                    //    ELLER at egen key er feil ift. minst ett av
{           
                    //    barna, s† er dette IKKE et bin‘rt s›ketre:

if (!bst(t->l)  ||  (t->l != z  &&  t->l->key >= t->key)) return false;
if (!bst(t->r)  ||  (t->r != z  &&  t->r->key <  t->key)) return false;
}
return true;          //  Ellers† er subtreet hittil det.
}

                        //  OPPGAVE 3B:
                        //  ===========
int ft(node* t, boolean & fullttre)
{
if (t != z)
{
int hl = ft(t->l, fullttre);         //  Finner venstre tres h›yde.
if (fullttre)                       //  Venstre treet er fullt.
{
int hr = ft(t->r, fullttre);     //  Finner h›yre tres h›yde.
if (hl != hr) fullttre = false;  //  Subtr‘rne har ulik h›yde,
}                                    //    dvs. treet er IKKE fullt!
return (hl + 1);                     //  Returnerer venstre tres h›yde
}
else                                  //    + 1 (medregnet 't' selv).
return 0;                             //  Tomt tre, h›yden er 0.
}

                        //  HOVEDPROGRAM:
int main()
{
cout << "\nS›ketre: "  << bst(head->r);
display(1, 80);
return 0;
}
