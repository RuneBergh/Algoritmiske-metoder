//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EXH94_4A.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     desember 1994, oppgave 4a.

//     Laget av Frode Haug, HIG, h›sten 1994.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


//  Linjer merket med "NYTT" er de omskrevet/nye ift. s.206 i l‘reboka.



void insert(itemType v, infoType info)  {
   struct node *p, *x;
   p = head;  x = head->r;
   while (x != z  &&  p->key != v)                        //  ENDRET
     {  p = x;  x = (v < x->key)  ?  x->l  :  x->r;  }
   if (p->key == v)                                       //  NYTT
      x = new node(v, info, z, p->r);                     //  NYTT
   else                                                   //  NYTT
      x = new node(v, info, z, z);
   if (v < p->key)  p->l = x;
   else             p->r = x;
}
