//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H16_3.CPP

//  Løsningforslag til eksamen i Alg.met, desember 2016, oppgave nr.3.
//  Laget av Frode Haug, NTNU


#include <iostream>
using namespace std;

const int ANTNODER = 15;

struct Node  {
  int   ID;	        //  Nodens ID/key/nøkkel/navn (et tall).
  Node* prev_left;	//  Peker til forrige ELLER venstre subtre (evt. 'nullptr').
  Node* next_right;	//  Peker til neste ELLER høyre subtre (evt. 'nullptr').
  Node(int id) {  ID = id;  prev_left = next_right = nullptr;  }
};

Node* root = nullptr;	        // root-peker.


//  OPPGAVE 3A - Omformer rekursivt en toveis liste til et Balansert Binært Tre:

Node* omformListeTilBBT(int len) {
	if (len == 0) return nullptr;				//  Tom liste.
												//	Første listehalvdel blir
	Node* left = omformListeTilBBT(len / 2);	//	  venstre subtre:
												//  Rot/hodet for subtre blir
	Node* hode = root;							//    dit 'root' er i listen:
	hode->prev_left = left;						//  Kobler til venstre subtre.
	root = root->next_right;						//  'root' blar til neste node.
												//  Siste halvdel blir h.subtre:
	Node* right = omformListeTilBBT(len - (len / 2) - 1);
	hode->next_right = right;					//  Kobler til høyre subtre.
	return hode;								//  Returnerer bygd subtres rot.
}


//  OPPGAVE 3B - Omformer rekursivt et Binært Tre til en Toveis Liste
//               (der listen har rekkefølge som treet traversert inorder):

Node* omformBTTilListe(Node* n) {
	if (n->prev_left != nullptr) {			//  Venstre del/subtre finnes:
		Node* prev = omformBTTilListe(n->prev_left); //  Bygger venstre liste:
		while (prev->next_right != nullptr)	//  Finner forrige i inorder (noden
			prev = prev->next_right;			//    lengst til høyre i v.subtre,
											//    dvs. sist i venstre liste).
		prev->next_right = n;				//  Kobler denne til som n's
		n->prev_left = prev;					//    venstre node i toveis liste.
	}
	if (n->next_right != nullptr) {			//  Høyre del/subtre finnes:
		Node* next = omformBTTilListe(n->next_right); //  Bygger høyre liste:
		while (next->prev_left != nullptr)	//  Finner neste i inorder (noden
			next = next->prev_left;			//    lengst til venstre i h.subtre,
											//    dvs.først i høyre liste).
		next->prev_left = n;					//  Kobler denne til som n's
		n->next_right = next;				//    høyre node i toveis liste.
	}
	return n;
}


// ---------------------------------------------------------------------------
									//  Bygger ei toveis liste med 
void lagToveisListe() {				//    ID'er lik  1 ... ANTNODER:
	Node *node, *hale = nullptr;    //  'root' blir pekende til listens start.
	for (int i = 1; i <= ANTNODER; i++)  {
		node = new Node(i);
		if (root == nullptr)
			root = hale = node;
		else  {
			node->prev_left = hale;
			hale->next_right = node;
			hale = node;
		}
	}
}

void skrivListe(Node* n) {			// Traverserer og skriver ei liste:
	while (n != nullptr) {
		cout << ' ' << n->ID;
		n = n->next_right;
	}
}
									//  Traverserer og skriver et tre på
void skrivPreorder(Node* n) {		//    ulike måter (jfr. s.60 i læreboka):
	if (n != nullptr) {
		cout << ' ' << n->ID;
		skrivPreorder(n->prev_left);
		skrivPreorder(n->next_right);
	}
}

void skrivInorder(Node* n) {
	if (n != nullptr) {
		skrivInorder(n->prev_left);
		cout << ' ' << n->ID;
		skrivInorder(n->next_right);
	}
}

void skrivPostorder(Node* n) {
	if (n != nullptr) {
		skrivPostorder(n->prev_left);
		skrivPostorder(n->next_right);
		cout << ' ' << n->ID;
	}
}


int main()  {
	lagToveisListe();						//  'root' peker til listestart.
	skrivListe(root);		cout << "\n\n";

	root = omformListeTilBBT(ANTNODER);		//  OPPGAVE 3A - 'root' peker til
											//			      binært trees rot.
	skrivPreorder(root);	cout << '\n';	//  Skriver treet på tre ulike
	skrivInorder(root);		cout << '\n';	//    måter for å sjekke/"se"
	skrivPostorder(root);	cout << "\n\n";	//	  hvordan det har blitt.


	root = omformBTTilListe(root);			//  OPPGAVE 3B - 'root' peker et
											//                sted inni lista.
											//  Blar til listens begynnelse:
	while (root->prev_left != nullptr)  root = root->prev_left;
	skrivListe(root);

	cout << "\n\nGjør om liste til tre med BARE høyre barn:\n";
	Node* p = root;
	while (p != nullptr)
	  {  p->prev_left = nullptr;  p = p->next_right;  	}
	skrivPreorder(root);	cout << '\n';	//  Skriver treet på tre ulike
	skrivInorder(root);		cout << '\n';	//    måter for å sjekke/"se"
	skrivPostorder(root);	cout << '\n';	//	  hvordan det har blitt.
	cout << "Gjør om totalt høyreskjeivt tre til liste:\n";
	root = omformBTTilListe(root);
	while (root->prev_left != nullptr)  root = root->prev_left;
	skrivListe(root);

	cout << "\n\nGjør om liste til tre med BARE venstre barn:\n";
	while (root->next_right != nullptr)
	  {  p = root;  root = root->next_right; p->next_right = nullptr;  }
	skrivPreorder(root);	cout << '\n';	//  Skriver treet på tre ulike
	skrivInorder(root);		cout << '\n';	//    måter for å sjekke/"se"
	skrivPostorder(root);	cout << '\n';	//	  hvordan det har blitt.
	cout << "Gjør om totalt venstreskjeivt tre til liste:\n";
	root = omformBTTilListe(root);
	while (root->prev_left != nullptr)  root = root->prev_left;
	skrivListe(root);		cout << "\n\n";

	return 0;
}
