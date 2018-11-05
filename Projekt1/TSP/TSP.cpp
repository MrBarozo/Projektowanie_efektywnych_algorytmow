#include "pch.h"
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int silnia(int n)
{
	if (n == 0) return 1;
	else return n * silnia(n - 1);
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
	string linia;
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
	int i_dystans_minimalny;
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
	liczba_permutacji = silnia(rozmiar_int);
	int **macierz = new int *[rozmiar_int];
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
	for (int i = 0; i < rozmiar_int; ++i) {
		std::getline(file, buffer);
		ss << buffer;
		for (int j = 0; j < rozmiar_int; ++j) {
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

	//Pomiar czasu	
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	start = read_QPC();
	//Rozpoczęcie kodu, którego czas wykonania mierzymy	##########################################################
				//BF
				int **tablica_permutacji = new int *[liczba_permutacji];
				for (int i = 0; i < liczba_permutacji; ++i)
				{
					tablica_permutacji[i] = new int[rozmiar_int];
				}

				int *tablica_wynikow = new int[liczba_permutacji];
				sort(tablica_int, tablica_int + rozmiar_int);
				int i = 0;
				do {
					for (int j = 0; j < rozmiar_int; ++j)
					{
						tablica_permutacji[i][j] = tablica_int[j];
					}
					i++;
				} while (next_permutation(tablica_int, tablica_int + rozmiar_int));

				//obliczanie dystansu dla kazdej z permutacji
				for (int j = 0; j < liczba_permutacji; j++)
				{
					for (int i = 0; i < rozmiar_int - 1; i++)
					{
						dystans = dystans + macierz[tablica_permutacji[j][i] - 1][tablica_permutacji[j][i + 1] - 1];
						if (macierz[tablica_permutacji[j][i] - 1][tablica_permutacji[j][i + 1] - 1] == 0) { dystans = -1; }
					}
					if (macierz[tablica_permutacji[j][rozmiar_int - 1] - 1][tablica_permutacji[j][0] - 1] == 0) { dystans = -1; }
					tablica_wynikow[j] = dystans + macierz[tablica_permutacji[j][rozmiar_int - 1] - 1][tablica_permutacji[j][0] - 1];
					if (tablica_wynikow[j] < dystans_minimalny && tablica_wynikow[j]>0)
					{
						dystans_minimalny = tablica_wynikow[j];
						i_dystans_minimalny = j;
					}
					dystans = 0;

				}

		//Zakończenie kodu, którego czas wykonania mierzymy	##########################################################
		elapsed = read_QPC() - start;
		//Odczyt czasu
		cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / frequency << endl;
		cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
		cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
		//Wyswietlenie wszystkich wynikow
		cout << "Dystans minimalny dla permutacji:";
			for (int j = 0; j < rozmiar_int; ++j)
		{
			cout << tablica_permutacji[i_dystans_minimalny][j] << ' ';
		}
			cout << endl  <<
			"\tDystans minimalny: " << dystans_minimalny<<endl;
		system("pause");
		/*cout << "Tablica permutacji" << endl;
		for (int i = 0; i < liczba_permutacji; ++i)
		{
			for (int j = 0; j < rozmiar_int; ++j)
			{
				cout << tablica_permutacji[i][j] << ' ';
			}
			if (tablica_wynikow[i] > 0)
			{
				cout << "Wynik =" << tablica_wynikow[i] << endl;
			}
			else 
			{
				cout << "Wynik = Brak połączenia";
			}
		}*/
		//uwolnienie pamieci
		for (int i(0); i < rozmiar_int; ++i)
			delete[] macierz[i];
		delete[] macierz;		
		delete[] tablica_int;
		for (int i(0); i < liczba_permutacji; ++i)
			delete[] tablica_permutacji[i];
		delete[] tablica_permutacji;
		delete[] tablica_wynikow;
		//uwolnienie pamieci
		system("PAUSE");
		return 0;
	}

