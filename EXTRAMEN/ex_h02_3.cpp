//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H02_3.CPP

//     L›sningsforslag til eksamen i 
//     "Algoritmiske metoder (I)", oppgave nr.3, 9.desember 2002.

//     Laget av Frode Haug, HiG, november 2002.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003
//     Koden for † generere tr‘r er hentet fra side 204 og 206 i l‘reboka.


#include <iostream>          //  cout
#include <cstring>           //  strlen
using namespace std;

                        //  STRUCT:
struct node  {
  char key;
  node *l, *r;
  node(char k, node* ll, node* rr)
      {  key = k;  l = ll;  r = rr;  }
};

                        //  GLOBALE VARIABLE:
node *head, *z;

                        //  DEFINISJON AV FUNKSJONER:
void display2(node* p, int y, int x1, int x2)  {
  if (p != z)  {
     int m = (x1+x2)/2;   //  gotoxy(m, y);  //  NB: Inaktiv kode !!!
	                      cout << p->key << ' ';
     display2(p->l, y+2, x1, m);
     display2(p->r, y+2, m, x2);
  }
}

void display(int x1, int x2)  {
  display2(head->r, 1, x1, x2);
}


void insert(char v)  {
   node *p, *x;
   p = head;  x = head->r;
   while (x != z)
     {  p = x;  x = (v < x->key)  ?  x->l  :  x->r;  }
   x = new node(v, z, z);
   if (v < p->key)  p->l = x;
   else             p->r = x;
}


                        //  OPPGAVE 3A:
                        //  ===========
bool bst(node* t)  { 
  if (t != z)  {        //  Om venstre/h›yre subtre IKKE er bin‘rt s›ketre
                        //    ELLER at egen key er feil ift. minst ett av
                        //    barna, s† er dette IKKE et bin‘rt s›ketre:

     if (!bst(t->l)  ||  (t->l != z  &&  t->l->key >= t->key)) return false;
     if (!bst(t->r)  ||  (t->r != z  &&  t->r->key <  t->key)) return false;
  }
  return true;          //  Subtreet er hittil et s›ketre.
}


                        //  OPPGAVE 3B:
                        //  ===========
int ft(node* t, bool & futre)  {
  if (t != z)  {
     int al = ft(t->l, futre);           //  Finner venstre tres antall.
     if (futre)  {                       //  Venstre treet er fullt:
        int ar = ft(t->r, futre);        //  Finner h›yre tres antall.
        if (futre)  {                    //  H›yre treet er fullt:
           if (al == ar)                 //  Subtr‘rne har likt antall:
              return (al + ar + 1);      //  Returnerer totalsummen.
           else                          //  Subtr‘rne har ULIKT antall:
              futre = false;             //  Alts† IKKE et fullt tre.
        }
     }
  }
  return 0;                              //  Returnerer alltid 0 om n†r hit.
}


                        //  OPPGAVE 3C:
                        //  ===========
bool komplett_tre = true, nivaa_opp = false;
int hoyde = 0, y = 0;

void kt(node* t)  {
  y++;
  if (t != z)  {
     kt(t->l);                       // Traverserer treet rekursivt.
     if (komplett_tre) kt(t->r);     // Gj›r dette s† lenge at er komplett.
  } else {                           // Har truffet p† z-noden:
                                     // Finner den for f›rste gang: 
    if (hoyde == 0) hoyde = y;       //   oppdaterer med dens niv†.
                                     // N†dd en z-node som ligger p† et for
                                     //   dypt eller lavt/grunnt niv†:
    else if (y > hoyde  ||  y < hoyde-1) komplett_tre = false;
    else if (y == hoyde-1) {         // N†dd en z-node p† niv†et over:
                                     // F›rste gang at dette skje - OK:
       if (!nivaa_opp) {  hoyde = y;  nivaa_opp = true;  }
       else komplett_tre = false;    // 2.gang at skjer - er IKKE komplett.
    }
  }
  y--;
}


                        //  HOVEDPROGRAM:
int main()  {
  int i;
  char ch;
  bool fullt_tre;
  char bokstav[] = "NUGKDXRFBMIWTPZCAEFJH";

  z = new node(0, 0, 0);
  head = new node(char(0), 0, z);

  for (i = 0;  i < strlen(bokstav);  i++)  {
      cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
      insert(bokstav[i]);

      fullt_tre = true;
      ft(head->r, fullt_tre);                                     // Tester 3B
      cout << "\nFullt tre:    " << (fullt_tre ? "Ja" : "Nei");

      komplett_tre = true;    hoyde = y = 0;
      nivaa_opp = false;
      kt(head->r);                                                // Tester 3C
      cout << "\nKomplett tre: " << (komplett_tre ? "Ja" : "Nei");

      cout << "\nS›ketre:      " << (bst(head->r) ? "Ja" : "Nei") << '\n'; // Tester 3A
      display(1, 80);  cin >> ch;
  }

  cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
  cout << "\nBytter om i nedre h›yre hj›rne (subtr‘rne under 'U') ...";
  node* np = head->r->r->l; head->r->r->l = head->r->r->r; head->r->r->r = np;
  cout << "\nS›ketre: "  << (bst(head->r) ? "Ja" : "Nei");        // Tester 3A
  display(1, 80);
  cout << "\n\n";
  return 0;
}
