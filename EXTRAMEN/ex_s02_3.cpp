//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S02_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder I",
//     15.august 2002, oppgave 3.

//     Laget av Frode Haug, HiG, juli 2002.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



/*
   OPPGAVE A:
   ==========
      HELE utskrifts-sekvensen blir:
          A1 B1 B2 D1 G1 I1 I2 G2 J1 J2 D2 A2 C1 E1 E2 C2 F1 H1 H2 F2
                               |----> oppgaven

      Om vi fjerner alle inneholdende "2" st†r vi igjen med sekvensen
      som tilsvarer PREORDER traversering av treet.

      Om vi fjerner alle inneholdende "1" st†r vi igjen med sekvensen
      som tilsvarer INORDER traversering av treet.




   OPPGAVE B:
   ==========

   Del 1:
      Ved † bruke kun "left" og "right" har vi IKKE mulighet til † komme
      oppover i treet !
      Om "neste" f.eks. f†r 'D' og '2' som input, skal den returnere 'A'.
      Dette er umulig, da den bare kjenner seg selv og noden 'G'.


   Del 2:
      N†r "right" brukes som peker til neste i dobbeltorder rekkef›lge,
      s† er dette markert vha. stiplet linje.
      At "rightref" er lik 1 er markert med 'x' ved nodens id/bokstav.

                          A
                     /    ^    \
                   B   ...:       C
                     \ :        / ^ \
                      Dx<.     Ex.:  Fx.....> z-noden (NULL)
                     /   :          / ^ 
                ...>G    :         Hx.:
                :  / \   :       
                :.Ix  Jx.:                   
*/


#include <iostream>          //  cout
using namespace std;


			//  STRUCT:
struct node  {
  char id;                   // Nodens ID/navn.
  node *left, *right;        // Pekere til venstre/h›yre subtre, evnt.
			     //   right peker til neste i preorder rekkef›lge.
  int rightref;              // = 0 dersom h›yre subtre finnes,
			     // = 1 dersom tomt h›yre subtre og at right dermed
                             //     peker til neste node i dobbeltorder-rekkef›lgen.
  node(char i, node* l, node* r)
    {  id = i, left = l;  right = r;  rightref = 0; }
};

			//  GLOBALE VARIABLE:
node* G[10];            //  Direkte pekere til ALLE nodene i treet.
node* z = new node('z', NULL, NULL);  //  Oppretter den globale z-noden.

			//  FUNKSJONER (DEKLARASJON OG DEFINISJON):
void lag_tre();              // Deklarasjon av funksjon som bygger et tre.
void dobbeltorder(node* t);  // Deklarasjon av funksjon som foretar en
                             //   dobbeltorder-traversering.

                                 //  OPPGAVE B - Del 3:
                                 //  ==================
node* neste(node* x, int d)  {   //  Returnerer ALLTID peker til
                                 //    den NESTE i dobbeltorder-rekkef›lgen.
  if (d == 1)  {                 //  Etter 1.bes›ket:
     if (x->left != z)           //    Dersom noden har et venstre subtre,
        return x->left;          //    s† er det dette som skal bes›kes,
     else                        //    eller s† skal man bes›ke
       return x;                 //    noden selv en gang til.
  } else     //  if (d == 2)     //  Etter 2.bes›ket:  
    return x->right;             //    Returnerer UANSETT h›yre subtre !
}


			//  HOVEDPROGRAMMET:
int main()  {

  lag_tre();                 //  Bygger et test-tre (som i oppgaveteksten).

  dobbeltorder(G[0]);        //  Traverserer treet dobbeltorder.
                             //  Utskrifter av hva som er nodenes "neste"
  for (int i = 0;  i <= 9;  i++)    // n†r d=1 eller d=2:
      cout << '\n' << G[i]->id << "'s neste n†r  d=1: " << neste(G[i], 1)->id
           <<                     "\n\t  n†r  d=2: "    << neste(G[i], 2)->id;
  cout << "\n\n";
  return 0;
}


void dobbeltorder(node* t)  {
  if (t != z)  {             //  Treet er ikke tomt.
     cout << t->id << "1 ";  //  Bes›ker/skriver noden for f›rste gang.
     dobbeltorder(t->left);  //  Traverserer venstre subtre dobbeltorder.
     cout << t->id << "2 ";  //  Bes›ker/skriver noden for andre gang.
                             //      Modifisering ift. oppgaveteksten, 
     if (t->rightref == 0)   //      for KUN † bes›ke EKTE h›yre subtr‘r.
     dobbeltorder(t->right); //  Traverserer h›yre subtre dobbeltorder.
  }
}


void lag_tre()  {     // Funksjon som bygger et tre likt med det i oppgaven.
  G[0] = new node('A', z, z);  G[1] = new node('B', z, z);  //  Lager nodene.
  G[2] = new node('C', z, z);  G[3] = new node('D', z, z);
  G[4] = new node('E', z, z);  G[5] = new node('F', z, z);
  G[6] = new node('G', z, z);  G[7] = new node('H', z, z);
  G[8] = new node('I', z, z);  G[9] = new node('J', z, z);
  G[0]->left = G[1];    G[0]->right = G[2];             //  Bygger treet.
		        G[1]->right = G[3];
  G[2]->left = G[4];    G[2]->right = G[5];
  G[3]->left = G[6];
  G[5]->left = G[7];
  G[6]->left = G[8];    G[6]->right = G[9];

  G[3]->rightref = 1;   G[3]->right = G[0];             // Setter "rightref"
  G[4]->rightref = 1;   G[4]->right = G[2];             //   og "right" i alle
  G[5]->rightref = 1;   G[5]->right = z;                //   relevante noder.
  G[7]->rightref = 1;   G[7]->right = G[5];
  G[8]->rightref = 1;   G[8]->right = G[6];
  G[9]->rightref = 1;   G[9]->right = G[3];
}
