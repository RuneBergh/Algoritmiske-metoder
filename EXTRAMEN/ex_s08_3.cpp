//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S08_3.TXT

//     L›sningsforslag til kontinuasjonseksamen i "Algoritmiske metoder",
//     13.august 2008, oppgave nr.3.

//     Laget av Frode Haug, HiG, mai 2008.


/*  OPPGAVE 3A:  
    
	  Vanlig bin‘rt s›ketre:
                                 Marita
                             /             \
                        Mari                Ola
                    /        \                  \ 
              Frode           Marit              Olav
                /           /                       \
               Frank     Marianne                   Ole
                  \
                  Frida


     Bin‘rt s›ketre etter nye kriterier/regler:
                                 Marita
                             /             \
                        Mari                Marianne
                     /        \   
                  Ola         Marit
                    \        /
                    Ole    Olav
                             \ 
                              Frode
                              /
                           Frank
                              \
                             Frida
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>     //  strcpy, strlen, strcmp
using namespace std;

const int LEN = 20;    //  ID'en i nodenes max.tekstlengde.


struct Node  {
  char  ID[LEN];  //  Nodens ID/key/n›kkel/navn (en tekst).
  Node* left;     //  Peker til venstre subtre, evt. z-noden om det er tomt.
  Node* right;    //  Peker til h›yre subtre, evt. z-noden om det er tomt.
  Node (char* id, Node* l, Node* r)  { strcpy(ID, id);  left = l;  right = r; }
};

                   //  Globale variable:
Node* z   = new Node("NULL", NULL, NULL);  //  z-noden.
Node* rot = z;                             //  Rot-peker.

                   //  (Hjelpe)funksjon som avgj›r om "er mindre":
bool MindreEnn (char* s, char* t)  {
  int slen = strlen(s), tlen = strlen(t);  // Tar vare p† tekstenes lengde.

// Er mindre om: Lengden mindre, evt. om like lange og kommer alfabetisk f›r:
  if (slen < tlen  ||  ((slen == tlen)  &&  (strcmp(s, t) < 0))) 
     return true; 
  else 
     return false;
}


//  OPPGAVE 3B:              S›ker/leter i spesielt bin‘rt s›ketre:
Node* search(Node* p, char* t)  {
  while (p != z  &&  strcmp(p->ID, t))   //  Leter til finner eller HELT ned.
    p = MindreEnn(t, p->ID)? p->left : p->right;  // G†r til venstre/h›yre.
  return ((p != z) ? p :  NULL);         //  Funn: retur av node, ellers NULL.
}


//  OPPGAVE 3C:              Setter inn i spesielt bin‘rt s›ketre:
void insert(Node* p, char* t)  {
  Node* q;                   //  Hjelpe-peker som "henger ett hakk etter".
  while (p != z)  {          //  Ikke n†dd/bladd helt ned til der skal inn:
     q = p;                  //  Flytter peker etter.
     p = MindreEnn(t, p->ID)? p->left : p->right;  // G†r til venstre/h›yre.
  }
  p = new Node(t, z, z);     //  Oppretter ny node.
  if (rot == z)  rot = p;                     //  Inn som ny rot,
  else if (MindreEnn(t, q->ID)) q->left = p;  //     p† venstre side
  else q->right = p;                          //     eller til h›yre.
}


//  EXTRA:                   Traverserer og skriver treet preorder:
void display(Node* p)  {    
  if (p != z)  {
     cout << "\tID: " << p->ID << "   (" << p->left->ID
                               << ", "   << p->right->ID << ")\n";
     display(p->left);
     display(p->right);
  }
}


int main()  {
  insert(rot, "Marita");
  insert(rot, "Mari");
  insert(rot, "Marit");
  insert(rot, "Ola");
  insert(rot, "Olav");
  insert(rot, "Ole");
  insert(rot, "Frode");
  insert(rot, "Frank");
  insert(rot, "Frida");
  insert(rot, "Marianne");

  display(rot);

  if (search(rot, "Frode"))
     cout << "\nFant 'Frode'!\n\n";
  if (search(rot, "Fride"))
     cout << "\nFant 'Fride'!\n\n";

  return 0;
}
