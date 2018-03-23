//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H01_3.CPP

//     L›sningsforslag til eksamen i
//     "Algoritmiske metoder I", oppgave nr.3, 11.desember 2001.

//     Laget av Frode Haug, HIG, januar 2002.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



/*
   OPPGAVE A:
      N†r "right" brukes som peker til neste i preorder rekkef›lge,
      s† er dette markert vha. stiplet linje.
      At "neste_i_preorder" er lik 'true' er markert med 'x' ved nodens id/bokstav.

			   A
		       /       \
		      B    ....>C
		       \   :  /   \
			Dx : Ex...>Fx
		       / : :      / :
		      G<.. :     Hx<:
		     / \   :      :
		    Ix  Jx..      :..> z / NULL
		     :..^
*/


#include <iostream>          //  cout
using namespace std;


			//  STRUCT:
struct node  {
  char id;                   // Nodens ID/navn.
  node *left, *right;        // Pekere til venstre/h›yre subtre, evnt.
			     //   right peker til neste i preorder rekkef›lge.
  bool neste_i_preorder;     // = 'false' dersom h›yre subtre finnes,
			     // = 'true' dersom tomt h›yre subtre og at right dermed
			     //         peker til neste node i preorder rekkef›lge.
  node(char i, node* l, node* r)
    {  id = i, left = l;  right = r;  neste_i_preorder = false; }
};

			//  GLOBALE VARIABLE:
node* root;                  //  Peker til hele treets rot.
node* forrige;               //  Global hjelpepeker til den forrige
			     //    noden i preorder rekkef›lge.
node* z = new node('X', NULL, NULL);  //  Oppretter den globale z-noden.

			//  FUNKSJONER (DEKLARASJON OG DEFINISJON):
node* lag_tre();             // Deklarasjon av funksjon som bygger et tre.

			     //  OPPGAVE B:
node* neste(node* x)  {      //  Returnerer ALLTID peker til
			     //    den NESTE i preorder rekkef›lge.
 if (x->left != z)           //  Om venstre barn/subtre finnes:
    return x->left;          //  Returner dette.
 else                        //  Ellers, kan man ALLTID trygt returnere
    return x->right;         //  h›yre subtre ELLER NESTE preorder-node !
}                            //  NB: Trenger alts† faktisk ikke sjekke
			     //      hva "neste_i_preorder" er/inneholder !


			     //  OPPGAVE D:
			     //  G†r rekursivt gjennom hele treet under "rot",
void sett_neste(node* rot)  {  //  og setter korrekt verdi i alle nodenes
			     //    "right" og "neste_i_preorder".
  if (rot != z)  {           //  F†r inne et reelt (ikke-tomt) tre
     if (forrige != z)  {    //  Rot er IKKE den f›rste i preorder rekkef›lgen:

	if (forrige->right == z)  {       //  Forrige har ingen h›yre, derfor
	   forrige->right = rot;          //    er n†v‘rende/aktuell node dens
           forrige->neste_i_preorder = true; //   neste til preorder rekkef›lge.
	}
     }

     forrige = rot;          //  Setter forrige til † v‘re noden selv.
     sett_neste(rot->left);  //  Gj›r evnt. rekursivt det samme for
			     //    begge sine to subtr‘r:
			     //  Men h›yre tas kun dersom det er et REELT tre:
     if (rot->neste_i_preorder == false) sett_neste(rot->right);


//  HELE innmaten inni ytre if-setning KUNNE ogs† i sin helhet ha v‘rt
//  erstattet med koden nedenfor. Forskjellen ligger prim‘rt i at ovenfor
//  peker "forrige" HELE tiden den sist bes›kte noden. Nedenfor peker
//  "forrige" til den siste bes›kte noden som IKKE hadde noe reelt h›yre
//  barn, og derfor skal ha/f† sin right-peker og "neste_i_preorder"
//  oppdatert/endret.
/*
     if (forrige != z)  {          //  Forrige var en uten reelt h›yre tre.
	forrige->right = rot;      //  Forriges h›yre peker p† n†v‘rende node.
	forrige = z;               //  Nullstiller "forrige".
     }

     if (rot->right == z)  {       //  Har ikke et reelt h›yre tre:
	if (rot->left == z)        //  Venstre er heller ikke reelt.
	   forrige = rot;          //  Tar vare p† n†v‘rende node som forrige.
	else                       //  Venstre tre er reelt/finnes:
	   rot->right = rot->left; //  H›yre peker ta til venstre.
        rot->neste_i_preorder = true; //  I begge tilfeller settes at h›yre
     }                             //    er brukt til † peke p† neste preorder.
				   //  Gj›r evnt. rekursivt det samme for
     sett_neste(rot->left);	   //    begge sine to subtr‘r:
			      //  Men h›yre tas kun dersom det er et REELT tre:
     if (rot->neste_i_preorder == false) sett_neste(rot->right);
*/
  }
}

			//  HOVEDPROGRAMMET:
int main()  {
  node* p;                   //  Hjelpepeker for † traversere treet (preorder).

  forrige = z;               //  "Forrige"-peker initieres til z.
  root = lag_tre();          //  Bygger et test-tre (som i oppgaveteksten).

  cout << "FR 'right' settes til † peke p† NESTE I PREORDER rekkef›lge:";
  for ( p = root;  p != z;  p = neste(p) )  // Traverserer treet
      cout << "\nID:  " << p->id            //   (s† langt man kommer).
	   << "\t\tNeste_i_preorder:  "
           << (p->neste_i_preorder ? '1' : '0');


  sett_neste(root);          //  Oppdaterter alle "right"-pekere
			     //    og "neste_i_preorder" korrekt.
  if (forrige != z)          //  M† evnt. spesialbehandle den SISTE noden i
     forrige->neste_i_preorder = true; //  preorder rekkef›lge. Denne har allerede
				    //  right == z, men m† sette at dette betyr
				    //  slutten p† preorder rekkef›lge.
				    // NB: Dette er UAKTUELT om benytter den
				    // alternative koden inne i "sett_neste" !
  cout << "\n\nETTER at right' er satt til † peke p† NESTE I PREORDER rekkef›lge:";
  for ( p = root;  p != z;  p = neste(p) )  // Traversere HELE treet.
      cout << "\nID:  " << p->id
           << "\t\tNeste_i_preorder:  "
           << (p->neste_i_preorder ? '1' : '0') << "\n\n";
  return 0;
}


/*
   OPPGAVE C:
      Vi kan f.eks. ha f›lgende situasjon nederst p† en gren:
		   .
		    .
		     .
		      Y
		       \
			X
		      /   \
		     A     B

      'X' sin etterf›lger i POSTORDER rekkef›lge er 'Y'.
      Siden 'X' har et reelt h›yre subtre, og det ikke er lov til
      † legge inn andre pekere i nodene, s† er det ikke mulig † f†
      ivaretatt at vi har en peker til neste i postorder rekkef›lge !
      S† lenge vi heller ikke har noen peker til treets rot,
      s† er det ikke mulig † finne 'Y' i det hele tatt !
      Dvs. v†r ide/teori/algoritme lar seg ikke uten videre overf›re
      fra preorder til postorder rekkef›lge.
*/


node * lag_tre()  {     // Funksjon som bygger et tre likt med det i oppgaven.
  node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;
  a = new node('A', z, z);     b = new node('B', z, z);    //  Lager nodene.
  c = new node('C', z, z);     d = new node('D', z, z);
  e = new node('E', z, z);     f = new node('F', z, z);
  g = new node('G', z, z);     h = new node('H', z, z);
  i = new node('I', z, z);     j = new node('J', z, z);
  a->left = b;    a->right = c;                            //  Bygger treet.
		  b->right = d;
  c->left = e;    c->right = f;
  d->left = g;
  f->left = h;
  g->left = i;    g->right = j;
  return a;                        //  Returnerer peker til rota ('a').
}
