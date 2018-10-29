#include "pch.h"
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
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
	//#########################################################################

	std::string buffer;
	std::ifstream file("Dane/test.txt");

	int counter = 0;
	std::stringstream ss;

	// NAME
	std::getline(file, buffer);
	ss << buffer;
	ss >> buffer; ss >> buffer;
	std::cout << buffer << '\n';
	ss.clear(); 


	// TYPE
	std::getline(file, buffer);
	ss << buffer;
	ss >> buffer; ss >> buffer;
	std::cout << buffer << '\n';
	ss.clear(); 

	// COMMENT
	std::getline(file, buffer);
	ss << buffer;
	ss >> buffer; ss.ignore(1);
	std::cout << ss.rdbuf() << '\n';
	ss.clear();

	// DIMENSION: 29
	std::getline(file, buffer);
	ss << buffer;
	ss >> buffer; ss >> buffer;
	rozmiar_int = atoi(buffer.c_str());
	std::cout << buffer << '\n';
	ss.clear(); 
	// EDGE_WEIGHT_TYPE: EXPLICIT
	std::getline(file, buffer);
	ss << buffer;
	ss >> buffer; ss >> buffer;
	std::cout << buffer << '\n';
	ss.clear(); 

	// EDGE_WEIGHT_FORMAT: FULL_MATRIX 
	std::getline(file, buffer);
	ss << buffer;
	ss >> buffer; ss >> buffer;
	std::cout << buffer << '\n';
	ss.clear();

	// DISPLAY_DATA_TYPE: TWOD_DISPLAY
	std::getline(file, buffer);
	ss << buffer;
	ss >> buffer; ss >> buffer;
	std::cout << buffer << '\n';
	ss.clear();

	// EDGE_WEIGHT_SECTION
	std::getline(file, buffer);
	int dimension = rozmiar_int; // <- podmien sobie
	for (int i = 0; i < dimension; ++i) {
		std::getline(file, buffer);
		ss << buffer;
		for (int j = 0; j < dimension; ++j) {
			ss >> buffer;
			std::cout << buffer << ' ';
		}
		std::cout << buffer << '\n';
		ss.clear();
	}
	// DISPLAY_DATA_SECTION
	std::getline(file, buffer);
	while (std::getline(file, buffer)) {
		if (buffer == "EOF") {
			break;
		}

		ss << buffer;

		ss >> buffer;
		std::cout << buffer << ' ';
		ss >> buffer;
		std::cout << buffer << ' ';
		ss >> buffer;
		std::cout << buffer << '\n';

		ss.clear();
	}
	
	//#########################################################################
	////plik.open("Dane/test.txt", ios::in);
	////if (plik.good() == false) { cout << "Plik nie istnieje!"; }
	////while (getline(plik, linia))
	////{
	////	switch (nr_Linii)
	////	{
	////	case 1: nazwa_pliku_txt = linia; break;		// NAME
	////	case 2: typ = linia; break;					//TYPE
	////	case 3: komentarz = linia; break;			//COMMENT
	////	case 4: rozmiar_tekst = linia; break;		//DIMENSION
	////	case 5: EDGE_WEIGHT_TYPE = linia; break;	//EDGE_WEIGHT_TYPE
	////	case 6: format_danych = linia; break;		//EDGE_WEIGHT_FORMAT
	////	case 7: DISPLAY_DATA_TYPE = linia; break;	//DISPLAY_DATA_TYPE
	////	case 8: EDGE_WEIGHT_SECTION = linia; break;	//EDGE_WEIGHT_SECTION
	////	}
	////	nr_Linii++;
	////}

	//////#######
	////	int buffor;
	////	string tekst_buffor;
	////	int w = rozmiar_int;
	////	int k = rozmiar_int;
	////	int **macierz = new int *[w]; //alokacja pamieci
	////	for (int i = 0; i < w; ++i)
	////	{
	////		macierz[i] = new int[k]; //alokacja pamieci
	////		
	////		for (int j = 0; j < k; ++j) //wpisanie wartosci do tablicy
	////		{
	////			plik >> tekst_buffor;
	////			cout << tekst_buffor<<"\n";
	////			//macierz[i][j] = buffor;
	////		}
	////	}
	////	//wypisz macierz[w][k]
	////	/*for (int i = 0; i < w; ++i, cout << endl)
	////		for (int j = 0; j < k; ++j)
	////			cout << macierz[i][j] << ' ';*/
	////	//zniszcz macierz
	////	//for (int i(0); i < w; ++i)
	////	//	delete[] macierz[i]; //uwolnienie pamieci
	////	//delete[] macierz; //uwolnienie pamieci
	////	//macierz = NULL;
	//////#######
	////	plik.close();

	////	/*for (int k = 0; k < rozmiar_int; k++)
	////	{
	////		for (int i = 0; i < rozmiar_int; i++)
	////		{
	////			cout << macierz[k][i];
	////		}

	////	}*/
	////	
		//Pomiar czasu	
		long long int frequency, start, elapsed;
		QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
		start = read_QPC();
		//Rozpoczęcie kodu, którego czas wykonania mierzymy	##########################################################
		cout << endl << nazwa_pliku_txt << endl;
		cout << typ << endl;
		cout << komentarz << endl;
		cout << "Rozmiar string:" << rozmiar << endl;
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

