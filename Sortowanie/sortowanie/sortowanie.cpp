#include "pch.h"
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<time.h>
#include<string>
#include<iterator>
#include<algorithm>
#include<ctime>
#include<Windows.h>

using namespace std;

void random()
{


	int tablica[30000];
	int b = 29999;

	for (int a = 0; a <= b; a++)
	{
		tablica[a] = rand() % 1000 + 0;
		//cout << a << "." << tablica[a] << endl;
	}

	fstream plik;
	plik.open("Random.txt", ios::out);
	for (int i = 0; i <= b; i++) {

		plik << tablica[i] << endl;

	}

	plik.close();

}

struct lista
{
	int liczba;
	int klucz;
	lista *nast;
};

void wczytywanie_listy(lista *&glowa, int n)
{
	lista *aktualny, *ostatni;
	ostatni = aktualny = NULL;
	fstream plik;
	plik.open("Random.txt", ios::in);
	if (plik.good() == false)
	{
		cout << "Plik nie istnieje!";
		exit(0);
	}
	for (int i = 0; i < n; i++)
	{
		ostatni = aktualny;
		aktualny = new lista;
		aktualny->klucz = 0;
		aktualny->nast = NULL;
		aktualny->liczba = 0;
		plik >> aktualny->klucz;
		aktualny->nast = NULL;
		if (ostatni == NULL)
			glowa = aktualny;
		else
			ostatni->nast = aktualny;
	}
}

void quickSort(lista *&root)
{
	if (!root || !(root->nast))
		return;

	lista *lhs = NULL, **pplhs = &lhs;
	lista *rhs = NULL, **pprhs = &rhs;
	lista *pvt = root;
	root = root->nast;
	pvt->nast = NULL;

	while (root)
	{
		if (root->klucz < pvt->klucz)
		{
			*pplhs = root;
			pplhs = &(*pplhs)->nast;
		}
		else
		{
			*pprhs = root;
			pprhs = &(*pprhs)->nast;
		}
		root = root->nast;
	}

	*pplhs = *pprhs = NULL;

	quickSort(lhs);
	quickSort(rhs);

	while (*pplhs)
		pplhs = &(*pplhs)->nast;
	*pplhs = pvt;
	pvt->nast = rhs;

	root = lhs;
}


int menu()
{
	int wybor;
	cout << "  **********************" << endl;
	cout << "           MENU" << endl;
	cout << "  1 sortowanie babelkowe" << endl;
	cout << "  2 sortowanie szybkie " << endl;
	cout << "  3 zakoncz program\n" << endl;
	cout << "  **********************" << endl;
	cin >> wybor;
	return wybor;
}

void babelkowe_tablica(double tab[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j < n - i; j++)
		{
			if (tab[j - 1] > tab[j])
			{
				swap(tab[j - 1], tab[j]);
			}
		}
	}
}

void szybkie_tablica(double tab[], int lewy, int prawy)
{
	if (prawy <= lewy) return;

	int i = lewy - 1, j = prawy + 1,
		pivot = tab[(lewy + prawy) / 2];

	while (1)
	{
		while (pivot > tab[++i]);
		while (pivot < tab[--j]);
		if (i <= j)
			swap(tab[i], tab[j]);
		else
			break;
	}

	if (j > lewy)
		szybkie_tablica(tab, lewy, j);
	if (i < prawy)
		szybkie_tablica(tab, i, prawy);
}

void zapisz(double tab[], int n, int rozm)
{
	fstream plik;
	plik.open("posortowane.csv", ios::out | ios::app);
	plik << rozm << endl << endl;
	for (int i = 0; i < n; i++)
	{
		plik << tab[i] << endl;
	}
	plik << endl;
	plik.close();
}

void odczyt(double tab[], int n)
{
	fstream plik;
	plik.open("Random.txt", ios::in);
	if (plik.good() == false)
	{
		cout << "Plik nie istnieje!";
		exit(0);
	}
	for (int i = 0; i < n; i++)
	{
		plik >> tab[i];
	}
	plik.close();
}

void babelkowe_lista(lista *&glowa)
{
	lista* temp = NULL;
	lista* help = NULL;

	for (temp = glowa; temp != NULL; temp = temp->nast)
	{
		for (help = temp; help != NULL; help = help->nast)
		{
			if (help->klucz < temp->klucz)
			{
				int klucz = help->klucz;
				help->klucz = temp->klucz;
				temp->klucz = klucz;
			}
		}
	}
}

void config(int tab_l[], string tab_s[], string typ[])
{
	fstream plik;
	plik.open("config.txt", ios::in);
	if (plik.good() == false)
	{
		cout << "Plik nie istnieje!";
		exit(0);
	}
	for (int i = 0; i < 2; i++)
	{
		plik >> tab_s[i] >> tab_l[i];
	}
	plik >> tab_s[1] >> typ[0];

	plik.close();
}

void drukowanie_listy(lista *glowa)
{
	while (glowa != NULL)
	{
		cout << glowa->klucz << endl;
		glowa = glowa->nast;
	}
}

int main()
{
	while (1) {
		
		lista *glowa;
		double roznica;
		int rozmiar;
		int algorytm;
		string typ[1];
		int wymiary[2];
		string nazwy[2];
		config(wymiary, nazwy, typ);
		rozmiar = wymiary[0];
		algorytm = wymiary[1];

		cout.setf(ios::fixed);
		cout.precision(8);
		clock_t start, koniec;

		double *tablica_alg = new double[algorytm];
		double *tablica = new double[rozmiar];

		int menu_wybor = menu();
		switch (menu_wybor)
		{
		case 1:
			if (typ[0] == "tablica")
			{
				double suma=0;
				for (int i = 0; i < algorytm; i++)
				{
					
					odczyt(tablica, rozmiar);
					start = clock();
					babelkowe_tablica(tablica, rozmiar);
					koniec = clock();
					roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
					tablica_alg[i] = roznica;
					cout << "Czas : " << roznica << endl;
					suma = suma + tablica_alg[i];
					
				}
				cout << "Srednia: " << suma/5 << endl;
			}
			if (typ[0] == "lista")
			{
				double suma = 0;
				for (int i = 0; i < algorytm; i++)
				{
					wczytywanie_listy(glowa, rozmiar);
					start = clock();
					babelkowe_lista(glowa);
					koniec = clock();
					roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
					tablica_alg[i] = roznica;
					cout << "Czas : " << roznica << endl;
					suma = suma + tablica_alg[i];
				}
				cout << "Srednia: " << suma / 5 << endl;
			}
			break;

		case 2:
			if (typ[0] == "tablica")
			{
				double suma = 0;
				for (int i = 0; i < algorytm; i++)
				{
					odczyt(tablica, rozmiar);
					start = clock();
					szybkie_tablica(tablica, 0, rozmiar - 1);
					koniec = clock();
					roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
					tablica_alg[i] = roznica;
					cout << "Czas : " << roznica << endl;
					suma = suma + tablica_alg[i];
				}
				cout << "Srednia: " << suma / 5 << endl;
			}
			if (typ[0] == "lista")
			{
				double suma = 0;
				for (int i = 0; i < algorytm; i++)
				{
					wczytywanie_listy(glowa, rozmiar);
					start = clock();
					quickSort(glowa);
					koniec = clock();
					roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
					tablica_alg[i] = roznica;
					cout << "Czas : " << roznica << endl;
					suma = suma + tablica_alg[i];
				}
				cout << "Srednia: " << suma / 5 << endl;
			}
			break;
		case 3:
		{
			exit(0);
		}
		}

		zapisz(tablica_alg, algorytm, rozmiar);
	}
}
