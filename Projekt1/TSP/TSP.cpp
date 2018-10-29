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
	//Wczytywanie pliku:
	std::string buffer;
	std::ifstream file("Dane/test.txt");
	int counter = 0;
	std::stringstream ss;

	// NAME
	std::getline(file, buffer);
	ss << buffer;
	ss >> buffer; ss >> buffer;
	nazwa_pliku_txt = buffer;
	std::cout << buffer << '\n';
	ss.clear(); 
	
	// TYPE
	std::getline(file, buffer);
	ss << buffer;
	ss >> buffer; ss >> buffer;
	typ = buffer;
	std::cout << buffer << '\n';
	ss.clear(); 

	// COMMENT
	std::getline(file, buffer);
	ss << buffer;
	ss >> buffer; ss.ignore(1);
	std::cout << ss.rdbuf() << '\n';
	komentarz = buffer;
	ss.clear();

	// DIMENSION
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
	//std::getline(file, buffer);
	//while (std::getline(file, buffer)) {
	//	if (buffer == "EOF") {
	//		break;
	//	}

	//	ss << buffer;

	//	ss >> buffer;
	//	std::cout << buffer << ' ';
	//	ss >> buffer;
	//	std::cout << buffer << ' ';
	//	ss >> buffer;
	//	std::cout << buffer << '\n';

	//	ss.clear();
	//}	
		//Pomiar czasu	
		long long int frequency, start, elapsed;
		QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
		start = read_QPC();
		//Rozpoczęcie kodu, którego czas wykonania mierzymy	##########################################################




		//Zakończenie kodu, którego czas wykonania mierzymy	##########################################################
		elapsed = read_QPC() - start;
		//Odczyt czasu
		cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / frequency << endl;
		cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
		cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
		system("PAUSE");
		return 0;
	}

