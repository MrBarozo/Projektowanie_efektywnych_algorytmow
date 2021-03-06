#include "pch.h"
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdio.h>

using namespace std;

int **macierz;
//BF
int *minimalna_sciezka;
int silnia(int n)
{
	if (n == 0) return 1;
	else return n * silnia(n - 1);
}
//DP
int *macierz_odwiedzonych;
int liczba_miast;
int koszt = 0;

void MacierzOdwiedzin(int _liczba_miast)
{
	liczba_miast = _liczba_miast;
	for (int i = 0; i < liczba_miast; i++)
	{
		for (int j = 0; j < liczba_miast; j++)
		macierz_odwiedzonych[i] = 0;
	}
}

int poprzednie(int maisto)
{
	int najblizsze = INT_MAX;
	int minimum = INT_MAX, kmin= INT_MAX;

	for (int i = 0; i < liczba_miast; i++)
	{
		if ((macierz[maisto][i] != 0) && (macierz_odwiedzonych[i] == 0))
			if (macierz[maisto][i] + macierz[i][maisto] < minimum)
			{
				minimum = macierz[i][maisto] + macierz[maisto][i];
				kmin = macierz[maisto][i];
				najblizsze = i;
			}
	}

	if (minimum != INT_MAX)
		koszt += kmin;

	return najblizsze;
}

void minimalny_koszt(int city)
{
	int najblizsze_miasto;

	macierz_odwiedzonych[city] = 1;

	cout << city + 1 << "->";
	najblizsze_miasto = poprzednie(city);

	if (najblizsze_miasto == INT_MAX)
	{
		najblizsze_miasto = 0;
		cout << najblizsze_miasto + 1;
		koszt += macierz[city][najblizsze_miasto];

		return;
	}

	minimalny_koszt(najblizsze_miasto);
}

//Funkcja QueryPerformanceCounter() pozwala na dokładniejszy pomiar czasu od funkcji clock().
long long int read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}

int main(void) {
	//zmienne-poczatek
	fstream plik;
	string nazwa_pliku_txt;
	string typ;
	string komentarz;
	string rozmiar_tekst;
	string EDGE_WEIGHT_TYPE;
	string format_danych;
	string DISPLAY_DATA_TYPE;
	string EDGE_WEIGHT_SECTION;
	string rozmiar;
	int rozmiar_int;
	int dystans_minimalny = INT_MAX;
	int dystans = 0;
	int liczba_permutacji;
	//zmienne-koniec
	//#########################################################################
	//Wczytywanie pliku:
	std::string buffer;
	std::ifstream file("Dane/test.txt");
	int counter = 0;
	std::stringstream ss;

	// NAME
	std::getline(file, buffer);	ss << buffer; ss >> buffer; ss >> buffer;
	nazwa_pliku_txt = buffer; std::cout << buffer << '\n';	ss.clear();

	// TYPE
	std::getline(file, buffer);	ss << buffer; ss >> buffer; ss >> buffer;
	typ = buffer; std::cout << buffer << '\n'; ss.clear();

	// COMMENT
	std::getline(file, buffer);	ss << buffer; ss >> buffer; ss.ignore(1);
	std::cout << ss.rdbuf() << '\n'; komentarz = buffer; ss.clear();

	// DIMENSION
	std::getline(file, buffer);	ss << buffer; ss >> buffer; ss >> buffer;
	rozmiar_int = atoi(buffer.c_str());	std::cout << buffer << '\n'; ss.clear();

	//alokacja pamieci
	macierz = new int *[rozmiar_int];
	for (int i = 0; i < rozmiar_int; ++i)
	{
		macierz[i] = new int[rozmiar_int];
	}

	int *tablica_int = new int[rozmiar_int];
	for (int i = 0; i < rozmiar_int; i++)
	{
		tablica_int[i] = i + 1;
	}
	//alokacja pamieci - koniec
	// EDGE_WEIGHT_TYPE: EXPLICIT
	std::getline(file, buffer);	ss << buffer; ss >> buffer; ss >> buffer;
	std::cout << buffer << '\n'; EDGE_WEIGHT_TYPE = buffer; ss.clear();

	// EDGE_WEIGHT_FORMAT: FULL_MATRIX 
	std::getline(file, buffer);	ss << buffer; ss >> buffer; ss >> buffer;
	std::cout << buffer << '\n'; format_danych = buffer; ss.clear();

	// DISPLAY_DATA_TYPE: TWOD_DISPLAY
	std::getline(file, buffer);	ss << buffer; ss >> buffer; ss >> buffer;
	std::cout << buffer << '\n'; DISPLAY_DATA_TYPE = buffer; ss.clear();

	// EDGE_WEIGHT_SECTION
	std::getline(file, buffer);
	for (int i = 0; i < rozmiar_int; ++i) 
	{
		std::getline(file, buffer);
		ss << buffer;
		for (int j = 0; j < rozmiar_int; ++j) 
		{
			ss >> buffer;
			macierz[i][j] = atoi(buffer.c_str());
		}
		ss.clear();
	}
	cout << "Wyswietlenie macierzy" << endl;
	for (int i = 0; i < rozmiar_int; ++i, cout << endl)
		for (int j = 0; j < rozmiar_int; ++j)
			cout << macierz[i][j] << ' ';
	cout << endl;
	system("pause");
	system("cls");
	cout << endl << endl << "#########	MENU	###########" << endl << endl;
	cout << "Wybierz algorytm:" << endl << endl;
	cout << "1) Przeglad zupelny BF" << endl;
	cout << "2) Programowanie dynamiczne" << endl;
	int menu;
	cout << endl;
	cin >> menu;
	system("cls");
	if (menu == 1)
	{
		//Pomiar czasu	
		long long int frequency, start, elapsed;
		QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
		start = read_QPC();
		//Rozpoczęcie kodu, którego czas wykonania mierzymy	##########################################################
		//BF
		minimalna_sciezka = new int[rozmiar_int];
		for (int i = 0; i < rozmiar_int; i++)
		{
			minimalna_sciezka[i] = tablica_int[i];
		}
		liczba_permutacji = silnia(rozmiar_int);
		sort(tablica_int, tablica_int + rozmiar_int);
		do {
			for (int j = 0; j < rozmiar_int-1; ++j)
			{
				dystans = dystans + macierz[tablica_int[j] - 1][tablica_int[j + 1] - 1];
				if (macierz[tablica_int[j] - 1][tablica_int[j + 1] - 1] == 0) { dystans = -1; }
			}
			if (macierz[tablica_int[rozmiar_int - 1] - 1][tablica_int[0] - 1] == 0) { dystans = -1; }
			dystans = dystans + macierz[tablica_int[rozmiar_int - 1] - 1][tablica_int[0] - 1];
			if (dystans < dystans_minimalny && dystans>0)
			{
				dystans_minimalny = dystans;
				for (int i = 0; i < rozmiar_int; i++)
				{
					minimalna_sciezka[i] = tablica_int[i];
				}
				
			}
			dystans = 0;		
		} while (next_permutation(tablica_int, tablica_int + rozmiar_int));
			
		//Zakończenie kodu, którego czas wykonania mierzymy	##########################################################
		elapsed = read_QPC() - start;
		system("cls");
		//Odczyt czasu
		cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / frequency << endl;
		cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
		cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
		//Wyswietlenie wszystkich wynikow
		cout << "Dystans minimalny dla permutacji:";
		for (int j = 0; j < rozmiar_int; ++j)
		{
			cout << minimalna_sciezka[j] << "->";
		}
		cout << minimalna_sciezka[0];
		cout << endl <<	"\tDystans minimalny: " << dystans_minimalny << endl;
				
	}
	if (menu == 2)
	{
		//Pomiar czasu	
		long long int frequency, start, elapsed;
		QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
		start = read_QPC();
		//Rozpoczęcie kodu, którego czas wykonania mierzymy	#################################################################
		macierz_odwiedzonych = new int[rozmiar_int];
		MacierzOdwiedzin(rozmiar_int);

		cout << "\n\nThe Path is:\n";
		minimalny_koszt(0); //Zakładamy ze miasto startowe to miasto 0
				//Zakończenie kodu, którego czas wykonania mierzymy	##########################################################
		elapsed = read_QPC() - start;
		
		//Odczyt czasu
		cout << "\nMinimum cost is " << koszt << endl << endl;
		cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / frequency << endl;
		cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
		cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
		

	}

		//uwolnienie pamieci
		for (int i=0; i < rozmiar_int; ++i)
			delete[] macierz[i];
		delete[] macierz;		
		delete[] tablica_int;
		//uwolnienie pamieci
		system("PAUSE");
		return 0;
	}

