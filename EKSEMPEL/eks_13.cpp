//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_13.CPP


//  ***************************************************************
//  ***************************************************************
//  ***************************************************************
//  ***                                                         ***
//  ***                                                         ***
//  ***                                                         ***
//  ***      NB:  VIRKER KUN UNDER/Pè BORLAND 4.5 !!!!!!!!      ***
//  ***                                                         ***
//  ***                                                         ***
//  ***                                                         ***
//  ***************************************************************
//  ***************************************************************
//  ***************************************************************


// Program: Sortdemo.cpp
// Av     : Thordur Arnason, 2AA
// Dato   : 25.09-15.10.95
// Versjon: 1.13
// Komm.  : Programmet sorterer en array vha. selection sort, insertion
//        : sort, bubble sort, shellsort, rekursiv quicksort, quicksort
//        : med insertion og median-of-three, heapsort og mergesort.
//        : Dette vises grafisk som i lërebokas figurer:
//        : 8.3, 8.4, 8.5, 8.10, 9.6, 11.11 og 12.5.


//********************************************INCLUDE

#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <time.h>    
#include <graphics.h>

//********************************************KONSTANTER

const int MAXL = 479;
const int MAXV = 479;
const int M = 10;
const int SENTMIN = -1;


//********************************************FUNKSJONSDEKLARASJON

int finnTot();
int finnAkk();
void ig();
int sjekk(int n);
void hfyllarr();
void fyllarr();
void tegnskjerm(int t);
void oppdater();
void bytt(int mi, int ni);
void selectsort();
void insertionsort();
void bubblesort();
void shellsort();
void quicksort(int a[], int l, int r);
void insertion(int a[],int l, int r);  
void medianOfThree(int a[], int l, int r);  
void quicksortII(int a[], int l, int r);  
void downheap(int N, int k);
void heapsort(int N);
void mergesort(int l, int r);
//********************************************GLOBALE VARIABLE

int harr[MAXL],arr[MAXL],gmode,driver,b[MAXL];

//********************************************MAIN

int main()
   {
   char c;

   hfyllarr();
   do
      {
topp:
      clrscr();
      cout << "\n\t**************************************************";
      cout << "\n\t[S]election sort";
      cout << "\n\t[I]nsertion sort";
      cout << "\n\t[B]ubble sort";
      cout << "\n\tS[h]ell sort";
      cout << "\n\t[Q]uick sort";
      cout << "\n\tQ[u]ick sort med median of three og insertion sort";
      cout << "\n\tH[e]ap sort";
      cout << "\n\t[M]erge sort";
      cout << "\n\t[A]vslutt";
      cout << "\n\t**************************************************";
      cout << "\n\tVelg en bokstav (S,I,B,H,Q,U,E,M,A) :";
      c = getche();
      switch (c)
	     {
	     case 'S': 
	     case 's':  ig();fyllarr();selectsort();break; 
	     case 'I':
	     case 'i':  ig();fyllarr();arr[0]=SENTMIN;insertionsort();break;
	     case 'B':
	     case 'b':  ig();fyllarr();bubblesort();break;
	     case 'H':
	     case 'h':  ig();fyllarr();shellsort();break;
	     case 'Q':
	     case 'q':  ig();fyllarr();quicksort(arr,1,MAXL);break;
	 case 'U':
	     case 'u':  ig();fyllarr();quicksortII(arr,1,MAXL);break;
	 case 'E':
	     case 'e':  ig();fyllarr();heapsort(MAXL);break;
	 case 'M':
	     case 'm':  ig();fyllarr();mergesort(1,MAXL);break;
	     case 'A':
	     case 'a':  ig();break;
	 default :  goto topp;
	     }
      if (c != 'a' && c != 'A')
	 {
	     tegnskjerm(WHITE);
	     getch();
	     tegnskjerm(BLACK);
	     closegraph();
	     clrscr();
	     }
      }
   while ((c != 'a')&&(c !='A'));
   closegraph();
   clrscr();
   return 0;
   }

//********************************************FUNKSJONSDEFINISJON

int finnTot()
   {
   int teller;
   int akk;
   for (teller = 1; teller <= MAXL; teller++)
      akk += teller;
   return akk;      
   }

int finnAkk()
   {
   int teller;
   int akk;
   for (teller = 1; teller <= MAXL-1; teller++)
      akk += arr[teller];
   return akk;      
   }

void ig()
   {
   driver = DETECT;
   initgraph(&driver,&gmode,"\\bc45\\bgi");
   setgraphmode(VGAHI);
   }                                                                                                                    


int sjekk(int n, int p)
   {
   for (int teller = 1; teller <= MAXL; teller++)
      {
      if (teller == p) n++;
      if (harr[teller] == n) return 1;
      }
   return 0;
   }

void hfyllarr()                                  // Fyller arr med tilfeldige 
   {                                             // verdier mellom 1 og MAXV
   int teller = 0;
   for (int i = 1; i <= MAXL; i++)               
	 harr[i] = 0;
   randomize();
   clrscr();
   cout << "\n\tVENT LITT!!";
   cout << "\n\tFinner " << MAXL << " unike verdier.";
   for (i = 1; i <= MAXL; i++)               
      {
      do
	 {                                                          
	 harr[i] = (random(MAXV));
	 gotoxy(26,5);
	 if (teller == 0 || teller == 4) cout << "|";
	 if (teller == 1 || teller == 5) cout << "/";
	 if (teller == 2 || teller == 6) cout << "-";
	 if (teller == 3 || teller == 7) cout << "\\";
	 if (teller == 7) teller = 0;
	 teller++;
	 if (i == MAXL) arr[MAXL] = finnTot()-finnAkk();
	 }
      while (sjekk(harr[i],i));
      gotoxy(30,5);cout << i << "/" << MAXL;
      }
   }

void fyllarr()                                  
   {                                            
   for (int i = 1; i <= MAXL; i++)
      arr[i]=harr[i];
   }

void tegnskjerm(int t)                                      
   {
   for (int i = 1; i <= MAXL; i++)
      {
      putpixel(((640-MAXL)/2)+i,480-arr[i],t);
      }
   }

void oppdater()
   {
   tegnskjerm(WHITE);
   tegnskjerm(BLACK);
   }

void bytt(int mi, int ni)
   {
   int xtra;

   xtra = arr[mi];
   arr[mi] = arr[ni];
   arr[ni] = xtra;
   }

void selectsort()
   {
   int i,j,min;
   for (i = 1; i < MAXL; i++)
      {
      oppdater();
      min = i;
      for (j = i+1; j <= MAXL; j++)
	 if (arr[j] < arr[min]) min = j;
      bytt(min,i);
      }
   }

void insertionsort()
   {
   int i,j,v;
   for (i = 1;i <= MAXL; i++)
      {
      oppdater();      
      v = arr[i]; j = i;
      while (arr[j-1] > v)
	 {
	     arr[j] = arr[j-1]; j--;
	     }
      arr[j] = v;
      }
   }

void bubblesort()
   {
   int i,j;
   for (i = MAXL; i >= 1; i--)
      {
      oppdater();      
      for (j = 1; j <= i; j++)
	 if(arr[j-1] > arr[j]) bytt(j-1,j);      
      }
   }

void shellsort()
   {
   int i,j,h,v,teller;
   for ( h = 0; h <= MAXL/9; h = 3*h+1);
   for ( ; h > 0; h /= 3)
      {
      
      for (i = h+1; i <= MAXL; i += 1)
	 {
	 if (teller++ >= 2)
	    {
	    oppdater();
	    teller = 0;
	    }
	 v = arr[i]; j = i;
	     while (j>h && arr[j-h]>v)
		{
		arr[j] = arr[j-h];
		j -= h;
		}
	 arr[j] = v;
	     }
      }
   }

void quicksort(int a[], int l, int r)
   {
   int i,j,v;
   if (r > l)
      {
      oppdater();      
      v = a[r]; i = l-1; j = r;
      for (;;)
	 {
	 while (a[++i] < v);
	 while (a[--j] > v);
	 if (i >= j) break;
	 bytt(i,j);
	 }
      bytt(i,r);
      if (i-1>l) quicksort(a,l,i-1);
      if (r>i+1) quicksort(a,i+1,r);
      }
   }

void insertion(int a[],int l, int r)  
   {   
   int i, j ,v;

   int sk = a[l-1];           //  Lagrer unna elementet utenfor til venstre.
   a[l-1] = -1;               //  Legger inn 'sentinel key' pÜ dens plass.
   for (i = l+1;  i <= r;  i++)  
       {                              // GÜr kun gjennom subarrayen:
       v = a[i];  j = i;              //   |
       while (a[j-1] > v)             //   |  Identisk med koden s.100.
	     {  a[j] = a[j-1];  j--;  }   //   |
       a[j] = v;                      //   |
       }                              //   |
   a[l-1] = sk;                       //  Legger tilbake opprinnelig element.
   }

void medianOfThree(int a[], int l, int r)  
   {
   int m = (l+r)/2;                     //  Finner midtposisjonen.
   if (a[l] > a[m])  bytt(l, m);        //  |
   if (a[l] > a[r])  bytt(l, r);        //  |  Sorterer de tre elementene:
   if (a[m] > a[r])  bytt(m, r);        //  |
   bytt(m, r-1);                        //  Legger det midtre inn NEST SIST.
   }


void quicksortII(int a[], int l, int r)  
   {                                    //  Jfr.s.118 i lëreboka.
   int i, j, v;
   int k;                                //  Hjelpevariabel for tegnutskrift.
   oppdater();
   if (r-l <= M)                 //  Har en subarray av lengde mindre eller lik M.
      insertion(a, l, r);        //  Kjõrer insertion pÜ denne delen.
   else  
      {                          //  Subarrayen er stõrre enn M:
      medianOfThree(a, l, r);  //  Soterer fõrste, midtre og siste element.
      v = a[r-1];                //  'v' = partisjonselementet. Dvs. det midle
					     //   elementet av det lengst til venstre,
					     //   hõyre og midten (nÜr disse er sortert).
					     //   Dette ligger NEST SIST i (sub)arrayen.
      i = l;  j = r-1;           //Initierer begge til grensene av det omrÜdet
					     // som skal omflyttes.
      for ( ; ; )  
	 {                       //  Looper til break'er ut.
					     //  NB:  'i' og 'j' õkes/minskes FùR bruk.
					     //  Derfor er de initiert utenfor grensene.
					     //  De stopper dessuten pÜ de aktuelle
					     //  indekser UTEN Ü "hoppe" en for langt.
	     while (a[++i] < v)  ;   //  Looper til stõrre (eller lik) 'v'.
	     while (a[--j] > v)  ;   //  Looper til mindre (eller lik) 'v'.
	     if (i >= j)  break;     //  Tellerne har passert hverandre:  break'er.
	     bytt(i, j);             //  Bytter elementene 'i' og 'j'.
	 }
      bytt(i, r-1);              //  Smetter inn partisjonselementet pÜ plass 'i'.
      quicksortII(a, l, i-1);    //  Gjentar for alt til venstre for 'a[i]'.
      quicksortII(a, i+1, r);    //  Gjentar for alt til hõyre for 'a[i]'.
      }
   }

void downheap(int N, int k)
   {
   int j, v;
   v = arr[k];
   while (k <= N/2)
      {
      j = k+k;
      if (j<N && arr[j]<arr[j+1]) j++;
      if (v >= arr[j]) break;
      arr[k] = arr[j]; k = j;
      }
   arr[k] = v;
   }

void heapsort(int N)
   {
   int k;

   for (k = N/2; k >= 1; k--)
      {oppdater(); downheap(N,k);}
   while (N > 1)
      { 
      oppdater();
      bytt(1,N); 
      downheap(--N,1);
      }
   }

void mergesort(int l, int r)
   {
   int i,j,k,m;

   if (r > l)
      {
      m = (r+l)/2;
      mergesort(l,m);
      mergesort(m+1,r);
      for (i = m+1; i > l; i--) b[i-1] = arr[i-1];
      for (j = m; j < r; j++) b[r+m-j] = arr[j+1];
      for (k = l; k <= r; k++)
	 arr[k] = (b[i]<b[j])? b[i++] : b[j--];
      oppdater();
      }
   }
