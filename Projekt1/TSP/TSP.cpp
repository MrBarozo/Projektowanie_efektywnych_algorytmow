#include "pch.h"
#include <windows.h>
#include <iostream>
#include <iomanip>

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

int main(void)
{
	//Pomiar czasu
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	start = read_QPC();
	//Rozpoczęcie kodu, którego czas wykonania mierzymy	##########################################################


	Sleep(12345); 


	//Zakończenie kodu, którego czas wykonania mierzymy	##########################################################
	elapsed = read_QPC() - start; 
	//Odczyt czasu
	cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / frequency << endl;
	cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
	cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
	system("PAUSE");
	return 0;
}

