#include "pch.h"
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

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
	int nr_Linii = 1;
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
	//zmienne-koniec

	plik.open("Dane/test.txt", ios::in);
	if (plik.good() == false) { cout << "Plik nie istnieje!"; }
	while (getline(plik, linia))
	{
		switch (nr_Linii)
		{
		case 1: nazwa_pliku_txt = linia; break;		// NAME
		case 2: typ = linia; break;					//TYPE
		case 3: komentarz = linia; break;			//COMMENT
		case 4: rozmiar_tekst = linia; break;		//DIMENSION
		case 5: EDGE_WEIGHT_TYPE = linia; break;	//EDGE_WEIGHT_TYPE
		case 6: format_danych = linia; break;		//EDGE_WEIGHT_FORMAT
		case 7: DISPLAY_DATA_TYPE = linia; break;	//DISPLAY_DATA_TYPE
		case 8: EDGE_WEIGHT_SECTION = linia; break;	//EDGE_WEIGHT_SECTION
		}
		nr_Linii++;
	}
		rozmiar = rozmiar_tekst.substr(rozmiar_tekst.find(" ") + 1, rozmiar_tekst.length() -rozmiar_tekst.find(" "));
		rozmiar_int = atoi(rozmiar.c_str());
	//#######
		int buffor;
		int w = rozmiar_int;
		int k = rozmiar_int;
		int **macierz = new int *[w]; //alokacja pamieci
		for (int i = 0; i < w; ++i)
		{
			macierz[i] = new int[k]; //alokacja pamieci
			
			for (int j = 0; j < k; ++j) //wpisanie wartosci do tablicy
			{
				plik >> buffor;
				macierz[i][j] = buffor;
			}
		}
		//wypisz macierz[w][k]
		for (int i = 0; i < w; ++i, cout << endl)
			for (int j = 0; j < k; ++j)
				cout << macierz[i][j] << ' ';
		//zniszcz macierz
		//for (int i(0); i < w; ++i)
		//	delete[] macierz[i]; //uwolnienie pamieci
		//delete[] macierz; //uwolnienie pamieci
		//macierz = NULL;
	//#######
		plik.close();

		for (int k = 0; k < rozmiar_int; k++)
		{
			for (int i = 0; i < rozmiar_int; i++)
			{
				cout << macierz[k][i];
			}

		}
		
		//Pomiar czasu	
		long long int frequency, start, elapsed;
		QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
		start = read_QPC();
		//Rozpoczęcie kodu, którego czas wykonania mierzymy	##########################################################
		cout << endl << nazwa_pliku_txt << endl;
		cout << typ << endl;
		cout << komentarz << endl;
		cout << "Rozmiar string:" << rozmiar << endl;
		cout << "Rozmiar INT:" << rozmiar_int << endl;
		cout << EDGE_WEIGHT_TYPE << endl;
		cout << format_danych << endl;
		cout << DISPLAY_DATA_TYPE << endl;
		cout << EDGE_WEIGHT_SECTION << endl;




		//Zakończenie kodu, którego czas wykonania mierzymy	##########################################################
		elapsed = read_QPC() - start;
		//Odczyt czasu
		cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / frequency << endl;
		cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
		cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
		system("PAUSE");



		return 0;

	}

