//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_17.CPP

//  Eksemplet viser hvordan finne Transitive Closure og
//  All Shortets Paths for en graf representert ved en nabomatrise.
//  Dette er en ren avskrift av koden s.475 og 477 i l‘reboka.
//  Utskriften fra programmet blir figurene  32.3-4  og  32.6-7.
//  Forklaringer p† s.475-476 og s.477-478 i l‘reboka.


#include <iostream>          //  cout
#include <iomanip>           //  setw

using namespace std;


const int  V = 13;           // Antall noder i grafen (A-M)

			                 //     A  B  C  D  E  F  G  H  I  J  K  L  M
int graph_32_1[V+1][V+1]  =  { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		             /* A */   { 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
		             /* B */   { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		             /* C */   { 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		             /* D */   { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		             /* E */   { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		             /* F */   { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
		             /* G */   { 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0 },
		             /* H */   { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 },
		             /* I */   { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
		             /* J */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
		             /* K */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
		             /* L */   { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1 },
		             /* M */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 } };

			                 //     A  B  C  D  E  F  G  H  I  J  K  L  M
int graph_32_5[V+1][V+1]  =  { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                     /* A */   { 0, 0, 1, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0 },
					 /* B */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 /* C */   { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 /* D */   { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
					 /* E */   { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 /* F */   { 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
					 /* G */   { 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
					 /* H */   { 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 0, 0, 0, 0 },
					 /* I */   { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
					 /* J */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 2 },
					 /* K */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 /* L */   { 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1 },
					 /* M */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 } };


void display(int a[V+1][V+1], int N)  {
  int i, j;
  for (i = 1;  i <= N;  i++)  {
      cout << "\n\t";
      for (j = 1;  j <= N;  j++)
	      cout << setw(3) << a[i][j];
  }
}


int main()  {
  int j, x, y;
  char ch;
				                       //  "Transitive Closure"
  for (y = 1;  y <= V;  y++)           //      (avskrift av koden s.475):
      for (x = 1;  x <= V;  x++)
	      if (graph_32_1[x][y])
	         for (j = 1;  j <= V;  j++)  {
		         if (graph_32_1[y][j] &&  !graph_32_1[x][j])  {
		            graph_32_1[x][j] = 1;
//  Ekstra utskrift:
//		      cout << "\n\nFra: "  << char(x+'A'-1) << " (X: " << x << ")"
//			       << "\t\tTil: "  << char(j+'A'-1) << " (J: " << j << ")"
//			       << "\t\tVia: "  << char(y+'A'-1) << " (Y: " << y << ")";
//		      display(graph_32_1, V);
//		      cin >> ch;
		      }
	     }
  display(graph_32_1, V);
  cout << "\n\n\nFerdig med † finne 'Transitive Closure'.\n\n\n\n";  cin >> ch;


				                       //  "All Shortest Paths"
  for (y = 1;  y <= V;  y++)           //      (avskrift av koden s.477):
      for (x = 1;  x <= V;  x++)
    	  if (graph_32_5[x][y])
	         for (j = 1;  j <= V;  j++)  {
		         if (graph_32_5[y][j] > 0)
		            if (!graph_32_5[x][j]  ||
		                (graph_32_5[x][y]+graph_32_5[y][j] < graph_32_5[x][j]))  {
		                   graph_32_5[x][j] = graph_32_5[x][y]+graph_32_5[y][j];
//  Ekstra utskrift:
//		      cout << "\n\nFra: "  << char(x+'A'-1) << " (X: " << x << ")"
//			       << "\t\tTil: "  << char(j+'A'-1) << " (J: " << j << ")"
//			       << "\t\tVia: "  << char(y+'A'-1) << " (Y: " << y << ")";
//		      display(graph_32_5, V);
//		      cin >> ch;
		      }
	     }
  display(graph_32_5, V);
  cout << "\n\n\nFerdig med † finne 'All Shortest Paths'.\n\n";
  return 0;
}
