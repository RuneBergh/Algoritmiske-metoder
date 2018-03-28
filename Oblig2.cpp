//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_06.CPP

//        Eksemplet viser bruk av rekursjon for permutering av en array.
//        Egen forklaring p� filen PERMUTERING.HTML.


#include <iostream>
using namespace std;


const int N = 15;                       //  Arrayens lengde.

int length;

char *arr ;                            //  Global array av int'er.

char *orgarr;

void les(const char* t, char* s, const int LEN) {
    do {
        cout << '\t' << t << ": ";  //  Skriver ledetekst.
        cin.getline(s, LEN);        //  Leser inn tekst.
    } while (strlen(s) == 0);       //  Sjekker at tekstlengden er ulik 0.
}


bool erVokal(char a)
{

char vokal[6]={'A', 'E', 'I', 'O', 'U', 'Y'};
for (int i =0; i<6 ; i++)
  {
    if( a ==vokal[i] ) return true;
  }
  return false;
}

bool navnOK(char *a, int len)
{

if (a[0] == a[1]) return false;  //to like i starten


for( int i=1; i < length; i++) 
  {  // går igjenom hele arrayen  
          
     if (erVokal(a[i-1]) && erVokal(a[i]))  // hvis begge er vokaler
      {  
         if(a[i-1]==a[i])    // to like vokaler
            { 
              return false;
            }                
    
         if (i >= 2 && erVokal(a[i-2]))            //tre like vokaler
          {
             return false;
          }
      }
  if (i>=2 && !erVokal(a[i]) && !erVokal(a[i-1]) && !erVokal(a[i-2])  )
    {
      if ( a[i]==a[i-1]==a[i-2]) return false;    //om det er tre like konsonanter
      if (i>=3 && !erVokal(a[i-3])) return false;   //om det kommer fire konsonanter etter hverandre
    }

}


return true;




}

void display(char *a)  {               //  Viser arrayens innhold.
  cout << "\n";
  for (int i = 0;  i < length;  i ++)
    cout << a[i] << ' ';
}


void bytt(char & a1, char & a2)  {       //  Bytter om to array-elementer.
  int aa = a1;
      a1 = a2;
      a2 = aa;
}


void roterVenstre(char *a, char i)  {   //  Roterer elementer mot venstre.
  int x, k;
  x = a[i];                            //  Tar vare p� f�rste.
  for (k = i+1;  k < length;  k++)          //  Roterer:
    a[k-1] = a[k];
  a[length-1] = x;                          //  Legger f�rst inn bakerst.
}

bool erbyttet(char * a, int i, int t)
{
  {
    for (int j=i+1;j<=t;j++)   // finne indeks til i og j
    {
      if (a[i]==a[j])
      return true;
    }
  }

return false;
}

void perm(int i)  {
  int t;
  char was[length];
   for(int j = 0; j <= 255; j++)
    was[j] = 0;
  
  
  if (i == length-1)                        //  N�dd en ny permutasjon:
   {   if(navnOK(arr,i))
    { display(arr);}                     //  Skriver ut arrayens innhold.
  }else {     
                              //  Skal permutere:
     perm(i+1);                        //  Beholder n�v�rende nr.'i'.
	 			                       //    Permuterer resten.
     for (t = i+1; t < length; t++)  {
       
       bytt(arr[i], arr[t]);         //  Bytter nr.'i' etter tur med alle
			 if (!erbyttet(arr, i, t)  &&  navnOK(arr, i))
       {	                       //    de andre etterf�lgende.
	     perm(i+1);  
       }                 //  For hver av ombyttene: permuterer
     }                                 //    resten av de N� etterf�lgende.
     roterVenstre(arr, i);             //  Gjenoppretter opprinnelig array.
            
  
  } 
}


int main()  {
 // for (int i = 0;  i < N;  i++)        //  Fyller array med: 1, 2, 3, ..., N
 //     arr[i] = 'a'+i;
 
 char buffer[N];
 les("Les inn array", buffer, N);  
  length =   strlen(buffer);             
  arr = new char[strlen(buffer) + 1];  strcpy(arr, buffer);
  orgarr = new char[strlen(arr) + 1];  strcpy(orgarr, arr);
 for (int i =0;i<length;i++)
   arr[i] = toupper(arr[i]);


  perm(0);                             //  Lager/skriver permutasjon av ALLE
				                       //    sifrene/arrayelementene.
  cout << '\n';
  display(arr);                        //  Skriver array etter at ferdig (for
  cout << "\n\n";                      //   � se om orginal er gjenopprettet).
  return 0;      
}
