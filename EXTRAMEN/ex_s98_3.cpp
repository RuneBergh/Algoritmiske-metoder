//  Fil:  FRODEH \ ALG_MET1 \ EXTRAMEN \EX_S98_3.CPP

//     L›sningsforslag til kontinuasjonseksamen i
//     "Algoritmiske metoder I", oppgave nr.3,  17.august 1998.

//     Laget av Frode Haug,  HIG,  august 1998.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



//  Oppgave 3A:
                             //  Funksjon som speilvender treet med rot i "t":
void speilvend(node* t)  { 
  if (t != NULL)  {          //  Dersom noden i det hele tatt finnes:
     node* p;                //  Hjelpepeker til † bytte subtr‘rne.
     p = t->right;           //  Bytter h›yre
     t->right = t->left;     //    og venstre
     t->left = p;            //    subtre.
     speilvend(t->left);     //  Speilvender ogs†
     speilvend(t->right);    //    begge subtr‘rne.
  }
}



//  Oppgave 3B:              // Funksjon som sjekker om to tr‘r er identiske,
                             //   dvs. at b†de tr‘rnes struktur og innhold i 
                             //   korresponderende noder er likt.
bool identisk(node* t, node* u)  {
   if (t == NULL  ||  u == NULL)  {    //  MINST en av nodene er NULL:
      if (t == u)  return true;        //  Begge er NULL, dvs. identiske.
      else  return false;              //  Bare en er NULL, dsv. IKKE identiske.
   } else  {                           //  Ingen av nodene er NULL:
      if (t->id != u->id)  return false;  //  Nodenes innhold (id) er ulikt.
      if (identisk(t->left,  u->left)  &&             // B†de h›yre og venstre
          identisk(t->right, u->right))  return true; //  subtre er identiske.
      else  return false;                  //  Subtr‘rne er IKKE identiske.      
   }
}
