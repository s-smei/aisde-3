/******************************************************************************/
/*                               AISDE-Lab                                    */
/******************************************************************************/
    //
    //  Adam Wojtasik
    //  partially based on code by Grzegorz Janczyk
    //
/*  Instytut Mikroelektroniki i Optoelektroniki                               */
/*  Politechnika Warszawska                                                   */
/*  ul. Koszykowa 75                                                          */
/*  00-662 WARSZAWA                                                           */
/*  tel. +48 22 234 72 07                                                     */
/*  www.imio.pw.edu.pl                                                        */
/******************************************************************************/


#ifndef _STATYSTYKA_H_
#define _STATYSTYKA_H_

#include <iostream>
using namespace std;
#include "error.h"
#include "control.h"
#include "iterator.h"
#include "object.h"

class Statystyka{

    clock_t startT;
    double numOfSeconds;

    unsigned long glebokoscRekurencji;        // biezaca glebokosc stosu aplikacji
    unsigned long glebokoscRekurencjiMax;     // maksymalna glebokosc stosu aplikacji
	unsigned long glebokoscRekurencjiBak;
	unsigned long glebokoscRekurencjiMaxBak;

public:
    Statystyka(){ srand((unsigned)seed); resetStat(); }

	void resetStat(){
        glebokoscRekurencji    = glebokoscRekurencjiBak    = 0L;
        glebokoscRekurencjiMax = glebokoscRekurencjiMaxBak = 0L;
		IMPLEMENTACJA_RESET
		ALGORYTM_RESET
    }
	void startStat(){
		glebokoscRekurencji    = glebokoscRekurencjiBak;
		glebokoscRekurencjiMax = glebokoscRekurencjiMaxBak;
		IMPLEMENTACJA_START
		ALGORYTM_START
	}
	void stopStat(){
		glebokoscRekurencjiBak    = glebokoscRekurencji;
		glebokoscRekurencjiMaxBak = glebokoscRekurencjiMax;
		IMPLEMENTACJA_STOP
		ALGORYTM_STOP
	}
	
	virtual ~Statystyka(){}

    void startTime (){ startT = clock(); }
    void stopTime  (){ numOfSeconds += (double)(clock()-startT)/(double)CLOCKS_PER_SEC; }
    void resetTime (){ numOfSeconds = 0.0; }

    void recurIn(){
        glebokoscRekurencji++;
        if(glebokoscRekurencjiMax < glebokoscRekurencji) glebokoscRekurencjiMax = glebokoscRekurencji;
    }
    void recurOut(){ glebokoscRekurencji--; }

    void raport(const char* nazwa){
        cout << "\n\n" << nazwa << "\n\n";
        cout << "Czas wykonania:                            " << numOfSeconds << endl;

        RAPORT_ALGORYTM
        RAPORT_IMPLEMENTACJA
        if(glebokoscRekurencjiMaxBak != 0) cout << "Rekurencja:  " << glebokoscRekurencjiMaxBak << endl;
    }

	void virtual wypiszNaKonsole  (bool = false)    { throw Error("Blad: Nie zdefiniowano funkcji wirtualnej wypiszNaKonsole"); }
 
    void virtual badanieAlgorytmow()                { throw Error("Blad: Nie zdefiniowano funkcji wirtualnej badanieAlgorytmow"); }

};

// Makra do obslugi statystyki


#define POMIAR_CZASU_START          (*this).startTime();
#define POMIAR_CZASU_STOP           (*this).stopTime();
#define POMIAR_CZASU_RESET          (*this).resetTime();

#define STATYSTYKA_START            (*this).startStat();
#define STATYSTYKA_STOP             (*this).stopStat();
#define STATYSTYKA_RESET            (*this).resetStat();

#if ALGORYTM_RAPORT
#define REKURENCJA_WEJSCIE          (*this).recurIn();
#define REKURENCJA_WYJSCIE          (*this).recurOut();
#else
#define REKURENCJA_WEJSCIE
#define REKURENCJA_WYJSCIE
#endif

#endif // defined(_STATYSTYKA_H_)
