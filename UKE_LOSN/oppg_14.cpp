//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_14.CPP


//  ***************************************************************
//  ***************************************************************
//  ***                                                         ***
//  ***  NB:  Deler av koden virker KUN under/p† BORLAND 4.5 !  ***
//  ***                                                         ***
//  ***************************************************************
//  ***************************************************************


//  L›sningsforslag til oppgave nr.14  i  Algoritmiske metoder.


//  Programmet leser 5000 usorterte tall fra fila OPPG_14.DTA.
//  Disse sorteres vha. ulike metoder (selection, insertion,
//  bubble sort, shellsort, quicksort, (heapsort) og mergesort).
//  Tiden for hver av dem tas og skrives ut.


//  FOR GRAFISK FREMSTILLING:  SE EKS_13.CPP 


#include <fstream>           //  ifstream
#include <conio.h>           //  getch, clrscr
#include "watch.h"           //  Verkt›ykasse for † lese klokka og
			                 //    tidsdifferanser.
using namespace std;

typedef int itemType;
const int MAX = 5000;        //  Tallene legges i indeks 1-5000.
itemType tall[MAX+1];

			     //  Leser tall fra fil inn i 'a':
void lesFraFil(int a[], int n)  {
  ifstream innfil("OPPG_14.DTA");
  for (int i = 1;  i <= n;  i++)
      innfil >> a[i];
  a[0] = -1;                 //  Setter 'sentinel key'.
}


void swap(itemType a[], int i, int j)  {    //  Jfr. s.95 i l‘reboka.
  itemType    t = a[i];
	   a[i] = a[j];
	   a[j] = t;
}


void selection(itemType a[], int N)  {      //  Jfr. s.98 i l‘reboka.
  int i, j, min;
  for (i = 1; i < N;  i++)  {
      min = i;
      for (j = i+1;  j <= N;  j++)
	  if (a[j] < a[min]) min = j;
      swap(a, min, i);
  }
}


void insertion(itemType a[], int N)  {      //  Jfr. s.100 i l‘reboka.
  int i, j;  itemType v;
  for (i = 2;  i <= N;  i++)  {
      v = a[i];  j = i;
      while (a[j-1] > v)  {
	a[j] = a[j-1];
	j--;
      }
      a[j] = v;
  }
}


void bubble(itemType a[], int N)  {         //  Jfr. s.101 i l‘reboka.
  int i, j;
  for (i = N;  i >= 1;  i--)
      for (j = 2;  j <= i;  j++)
	  if (a[j-1] > a[j])  swap(a, j-1, j);
}


void shellsort(itemType a[], int N)  {      //  Jfr. s.109 i l‘reboka.
  int i, j, h;   itemType v;

  for (h = 1;  h <= N/9;  h = 3*h+1)  ;
  for ( ;  h > 0;  h /= 3)
      for (i = h+1;  i <= N;  i++)  {
	  v = a[i];  j = i;
	  while ( j > h  &&  a[j-h] > v)  {
		a[j] = a[j-h];
		j -= h;
	  }
	  a[j] = v;
      }
}


void quicksort(itemType a[], int l, int r)  {   //  Jfr. s.118 i l‘reboka.
  int i, j;   itemType v;
  if (r > l)  {
     v = a[r];
     i = l-1;  j = r;
     for ( ; ; )  {
	 while (a[++i] < v)  ;
	 while (a[--j] > v)  ;
	 if (i >= j)  break;
	 swap(a, i, j);
     }
     swap(a, i, r);
     quicksort(a, l, i-1);
     quicksort(a, i+1, r);
  }
}


itemType b[MAX+1];

void mergesort(itemType a[], int l, int r)  {   //  Jfr. s.166 i l‘reboka.
  int i, j, k, m;
  if (r > l)  {
     m = (r+l)/2;
     mergesort(a, l, m);
     mergesort(a, m+1, r);
     for (i = m+1;  i > l;  i--)  b[i-1]   = a[i-1];
     for (j = m;    j < r;  j++)  b[r+m-j] = a[j+1];
     for (k = l;    k <=r;  k++)
	 a[k] =  (b[i] <= b[j]) ? b[i++] : b[j--];
  }
}




void main()  {
  Watch watch;

  cout << "\n\nSelection sort:  ";
       lesFraFil(tall, MAX);    watch.start();
       selection(tall, MAX);
       watch.stop();  watch.usedTime();

  cout << "\n\nInsertion sort:  ";
       lesFraFil(tall, MAX);    watch.start();
       insertion(tall, MAX);
       watch.stop();  watch.usedTime();

  cout << "\n\nBubble sort:     ";
       lesFraFil(tall, MAX);    watch.start();
       bubble(tall, MAX);
       watch.stop();  watch.usedTime();

  cout << "\n\nShellsort:       ";
       lesFraFil(tall, MAX);    watch.start();
       shellsort(tall, MAX);
       watch.stop();  watch.usedTime();

  cout << "\n\nQuicksort:       ";
       lesFraFil(tall, MAX);    watch.start();
       quicksort(tall, 1, MAX);
       watch.stop();  watch.usedTime();

  cout << "\n\nHeapsort:        Ikke implementert";
//       lesFraFil(tall, MAX);    watch.start();
//       heapsort(tall, MAX);               //  Jfr.s.156, 152 og 147.
//       watch.stop();  watch.usedTime();

  cout << "\n\nMergesort:       ";
       lesFraFil(tall, MAX);    watch.start();
       mergesort(tall, 1, MAX);
       watch.stop();  watch.usedTime();
  getch();
}
