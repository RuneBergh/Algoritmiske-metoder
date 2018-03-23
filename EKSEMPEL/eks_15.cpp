//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_15.CPP


//  Eksemplet viser traversering av en vektet graf, for † finne korteste
//  sti fra EN bestemt node til ALLE de andre nodene.

//  Poenget er funksjonen kalt "visit" (se ALLER siste funksjon).

//  ALL koden i filen er IDENTISK til EKS_14.CPP, bare at koden "t->w" i
//  "visit" er byttet ut med "val[k] + t->w".


#include <iostream>          //  cout
#include <fstream>           //  ifstream
#include <iomanip>           //  setw

using namespace std;


const int MAXNODE  =  100;   //  Max antall noder/vertex i grafen.
const int UNSEEN   =  -999;  //  "Stort" negativt tall.


struct Node  {               //  Kode fra s.421 i l‘reboka:
  int v, w;                  //     w = weight (vekt)
  Node* next;
};


class PQ  {                  //  Kode s.147 STERKT omskrevet, da
  private:                   //    arrayen hele tiden er voksende
    int* v;                  //    sortert etter prioritet.
    int* w;                  //   w[i] er den s† langt fundne kanten med
    int N;                   //      minst vekt ut fra noden v[i].
			     //   N = siste indeks brukt i "v" og "w".
  public:
    PQ(int max)
       {  v = new int[max];   w = new int[max];  N = 0;  }
    ~PQ()
       {  delete [] v;  delete [] w;  }

    bool empty()  {  return  N == 0;  }
    bool update(int ve, int we);
    int  remove();
    void display();
};


void adjlist();
int  index(char ch);
void search();
void visit(int k);
void display2();


Node* adj[MAXNODE], *z;      //  Kode fra s.421 i l‘reboka.
PQ pq(MAXNODE);              //  Lager prioritetsk›/heap (kode s.455).
int val[MAXNODE];            //  val[k] er kantens vekt mellom k
int dad[MAXNODE];            //     og dens far "dad[k]".
int V = 0;                   //  Antall noder/vertex i grafen.


int main() {
  adjlist();
  search();
  return 0;
}
			     //  Noden "ve" legges inn i arrayene dersom:
			     //     - den er ny    eller
			     //     - den har lavere vekt enn hittil antatt.
bool PQ::update(int ve, int we)  {
   int j, i = 1;

   while ((v[i] != ve)  &&  (i <= N))  i++;    //  Leter etter noden "ve".
   if ((i <= N)  &&  (we >= w[i]))             //  Er der: har allerede
      return false;                            //    mindre vekt/prioritet.
   if (i <= N)  {                              //  Er der: men har st›rre
      for (j = i;  j < N;  j++)                //     vekt, tas derfor ut:
	  {  v[j] = v[j+1];   w[j] = w[j+1];  }
      --N;
   }
   i = 1;
   while ((w[i] < we)  &&  (i <= N))  i++;    //  Leter etter plassen der
   ++N;                                       //    b›r smettes inn.
   for (j = N; j > i; j--)                    //  Flytter alle etter ett
      {  v[j] = v[j-1];  w[j] = w[j-1];  }    //    hakk lengre ut.
   v[i] = ve;  w[i] = we;                     //  Smetter innimellom.
   return true;
}


int PQ::remove()  {          //  Fjerner det f›rste elementet.
  int ve;
  ve = v[1];
  for (int i = 1;  i < N;  i++)     // Lar alle etter flytte EN plass fram.
      {  v[i] = v[i+1];   w[i] = w[i+1];  }
  --N;
  return ve;
}


void PQ::display()  {
  cout << "\tHeap:\t";
  for (int i = 1;  i <= N;  i++)
    cout << char(v[i]+'A'-1) << '-' << w[i] << "  ";
}


void display2()  {
  int i;
						 cout << "\n\ti:   ";
  for (i = 1;  i <= V;  i++)
      cout << setw(4) << char('A'+i-1) << ':';   cout << "\n\tval: ";
  for (i = 1;  i <= V;  i++)
      cout << setw(5) << val[i];                 cout << "\n\tdad: ";
  for (i = 1;  i <= V;  i++)
      cout << setw(5) << ((dad[i]) ? char('A'+dad[i]-1) : '0');
}


int  index(char ch)  {       //  Jfr.s.420 i l‘reboka (litt under midten).
  return ch - 'A' + 1;       //  Indeksen er tegnets nummer i alfabetet.
}

			                 //  Kode fra s.421 i l‘reboka:
void adjlist()  {            //  Oppretter nabo-lister ved † lese fra fil.
	  int j, x, y;
  Node* t;
  char v1, v2;
  int we;
  ifstream innfil("EKS_1415.DTA");

  z = new Node;   z->next = z;

  for (j = 1; j < MAXNODE;  j++)  adj[j] = z;     //  Lager tomme lister.

  innfil >> v1;              //  Leser (om mulig) nodenavn.
  while (!innfil.eof())  {
     innfil >> v2 >> we;     //  Leser andre nodens navn og kantens vekt.
     x = index(v1);   y = index(v2);   //  Omformer navn til tall.
     t = new Node;                     //  Hekter inn i hverandres lister:
	 t->v = x;  t->w = we;  t->next = adj[y];  adj[y] = t;
     t = new Node;
	 t->v = y;  t->w = we;  t->next = adj[x];  adj[x] = t;

     if (x > V)  V = x;      //  Oppdaterer "V" med den noden med
     if (y > V)  V = y;      //    st›rst indeks i hele grafen.
     innfil >> v1;           //  Leser (om mulig) nodenavn.
  }
}

			                 //  Kode fra s.424 i l‘reboka:
void search()  {             //  Traverserer hele grafen.
  int k;
  for (k = 1;  k <= V;  k++)   val[k] = UNSEEN;
  for (k = 1;  k <= V;  k++)
      if (val[k] == UNSEEN)  visit(k);
}

			                 //  Kode fra s.455 i l‘reboka:
void visit(int k)  {         //  Finner ETT minimums spenntre.
   Node* t;
                           char ch;
			                 //  Noden er ny og har dermed ingen "dad":
   if (pq.update(k, -UNSEEN) != 0)  dad[k] = 0;
   while (!pq.empty())  {    //  Fortsatt ubehandlede (p† "fringen"):
				  cout << "\n\nOPPSTART:";
						   pq.display();
						   display2();
						   cin >> ch;
       k = pq.remove();       //  Henter den f›rst p† heapen.
       val[k] = -val[k];      //  Omgj›r negativ "fringe" til positiv verdi.
				  cout << "\nK:  " << k;
				  cout << "\n1. fjernet:";
						   pq.display();
						   display2();
						   cin >> ch;
			                  //  "Fringen" er noden uten "dad":
       if (val[k] == -UNSEEN)  val[k] = 0;

       for (t = adj[k];  t != z;  t = t->next)   //  G†r gjennom alle naboer:
	       if (val[t->v] < 0)                    //  Naboen er p† "fringen"
						                         //    eller UNSEEN:

// DE TO NESTE SETNINGENE ER DE ENESTE SOM ER ENDRET I FORHOLD TIL EKS_14.CPP:
	          if (pq.update(t->v, val[k] + t->w))  {  //  Ny lavere prioritet:
		         val[t->v] = -(val[k] + t->w);        //    Oppdaterer med ny pri.
		         dad[t->v] = k;                       //    Oppdaterer med ny "far".
				           cout << "\nOppdatering:";
						   pq.display();
						   display2();
						   cin >> ch;
	      }
   }
}
