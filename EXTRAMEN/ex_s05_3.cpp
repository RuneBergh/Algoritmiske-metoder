//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S05_3.CPP

//     L›sningsforslag til kontinuasjonseksamen i 
//     "Algoritmiske metoder", oppgave nr.3, 9.august 2005.

//     Laget av Frode Haug, HiG, juni 2005.




//  OPPGAVE A:
//  ==========
//  Beskrivelse:
//       Hvis node 'i' har foreldre (dad) 'j', s† representeres det ved
//          foreldre[i] = j.
//       Hvis node 'i' er en rotnode, s† representeres det ved
//          foreldre[i] = -1.
//       (Alt dette blir meget likt tankehgangen som er brukt ifm.
//       Union-Find i l‘reboka s.441-445.)
//
//  Arrayens innhold i dette konkrete eksemplet:
//                 Indeks:   0   1   2   3   4   5   6   7   8   9
//      int foreldre[] =  {  9,  4,  1, -1, -1,  7,  1, -1,  1,  7  };




      
//  OPPGAVE B:
//  ==========

     void vei_mot_rot(int node)  {
        cout << "Fra node: " << node;
        while (foreldre[node] != -1)  {
            node = foreldre[node];
            cout << "  til node: " << node;
        }
        cout << " som er rot.";
     }





//  OPPGAVE C:
//  ==========

     void vei_fra_rot(int node)  {
       if (foreldre[node] == -1)
          cout << "Fra rot: " << node;
       else  {
          vei_fra_rot(foreldre[node]);
          cout << "  til node: " << node;
       }
     }
