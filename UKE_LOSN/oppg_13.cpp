//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_13.CPP

//   L›sningsforslag til oppgave nr.13  i  Algoritmiske metoder.


//  Programmet viser koden fra sidene 147, 150, 152 og 153 i l‘reboka.
//  I tillegg er det laget kode for "Delete/Extract" og "Change".


#include <iostream>        //  cout

using namespace std;


const int itemMAX = 100000;   //  St›rste tall i heapen ('sentinel key').
int LEN = 21;                 //  Max. antall tegn i heapen (indeks 1-20).


typedef int itemType;


class PQ  {                            //  Hovedrisset: Jfr.s.147 i l‘reboka.
private:
	itemType* a;
	int N;

	void upheap(int k)  {              //  Jfr.s.150 i l‘reboka.
		itemType v;
		v = a[k];  a[0] = itemMAX;
		while (a[k / 2] <= v)  {
		  a[k] = a[k / 2];  k = k / 2;
		}
		a[k] = v;
	}

	void downheap(int k)  {            //  Jfr.s.152 i l‘reboka.
		int j;  itemType v;
		v = a[k];
		while (k <= N / 2)  {
			j = 2 * k;
			if (j < N  &&  a[j] < a[j + 1])  j++;
			if (v >= a[j]) break;
			a[k] = a[j];  k = j;
		}
		a[k] = v;
	}

public:
	PQ(int max)  { a = new itemType[max];  N = 0; }
	~PQ()        { delete[] a; }

	void display()	{
		for (int i = 1; i <= N; i++)  cout << a[i] << ' ';
	}

	void insert(itemType v)  {            //  Jfr.s.150 i l‘reboka.
		a[++N] = v;  upheap(N);
	}

	itemType remove()  {                  //  Jfr.s.153 i l‘reboka.
		itemType v = a[1];
		a[1] = a[N--];
		downheap(1);
		return v;
	}

	itemType replace(itemType v)  {     //  Jfr.s.153 i l‘reboka.
		a[0] = v;
		downheap(0);
		return a[0];
	}

	void extract(int k)  {             //  Sletter element nr.'k' fra heapen.
		itemType v = a[k];             //  Tar vare p† det slettede.
		a[k] = a[N--];                 //  Flytter siste inn p† k's plass.
		if (v <= a[k]) upheap(k);      //  Det "nye" st›rre: flytter oppover,
		else           downheap(k);    //  ellers: flytter nedover.
	}

	void change(int k, int p)  {       //  Endrer prioritet p† nr.'k' med 'p'.
		a[k] += p;                     //  "Tillegg" p† prioritet.
		if (p >= 0)  upheap(k);        //  Prioritet ›ker:  flytte oppover.
		else         downheap(k);      //  Prioritet avtar: flytte nedover.
	}    
};



int main()  {
  PQ heap(LEN);              //  Heapen.
  char ch;

  cout << "\n\nViser bruken av HEAP.";
			                 //  9 linjer fra oppg.1 s.162 i l‘reboka:
  heap.insert(1);     cout << "\nInsert 1 :     ";  heap.display();  cin >> ch;
  heap.insert(5);     cout << "\nInsert 5 :     ";  heap.display();  cin >> ch;
  heap.insert(2);     cout << "\nInsert 2 :     ";  heap.display();  cin >> ch;
  heap.insert(6);     cout << "\nInsert 6 :     ";  heap.display();  cin >> ch;
  heap.replace(4);    cout << "\nReplace 4:     ";  heap.display();  cin >> ch;
  heap.insert(8);     cout << "\nInsert 8 :     ";  heap.display();  cin >> ch;
  heap.remove();      cout << "\nRemove   :     ";  heap.display();  cin >> ch;
  heap.insert(7);     cout << "\nInsert 7 :     ";  heap.display();  cin >> ch;
  heap.insert(3);     cout << "\nInsert 3 :     ";  heap.display();  cin >> ch;

			                 //  Tester to selvlagde funksjoner:
  heap.change(4, 5);  cout << "\nChange #4 +5:  ";  heap.display();  cin >> ch;
  heap.change(1,-4);  cout << "\nChange #1 -4:  ";  heap.display();  cin >> ch;
  heap.extract(2);    cout << "\nExtract #2:    ";  heap.display();  cin >> ch;
  heap.extract(2);    cout << "\nExtract #2:    ";  heap.display();  cin >> ch;
  heap.extract(1);    cout << "\nExtract #1:    ";  heap.display();  
  cout << "\n\n";
  return 0;
}
