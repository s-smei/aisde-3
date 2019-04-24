/******************************************************************************/
/*                               AISDE-Lab                                    */
/******************************************************************************/
    //
    //  Adam Wojtasik
    //  slightly based on code by Grzegorz Janczyk
    //
/*  Instytut Mikroelektroniki i Optoelektroniki                               */
/*  Politechnika Warszawska                                                   */
/*  ul. Koszykowa 75                                                          */
/*  00-662 WARSZAWA                                                           */
/*  tel. +48 22 234 72 07                                                     */
/*  www.imio.pw.edu.pl                                                        */
/******************************************************************************/


#ifndef _TABLICA_H_
#define _TABLICA_H_

#include <cstring>

#include "iterator.h"
#include "statystyka.h"
#include "generator.h"



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <typename RECORD>
class Array : public Statystyka{

// struktura wewnętrzna danych
private:
    RECORD*         recordArray;
    RECORD*         recordArrayBis;
    const long      arraySize;

    const Iterator  firstRecordIndex;
    const Iterator  lastRecordIndex;
    const long      numOfRecords;

//-----------------------------------------
// reprezentacja robocza danych - dostępna z wnętrza procedur implementujących algorytmy
protected:
// roboczy wskaźnik na tablicę, w której przeprowadzane są operacje
    RECORD*         array;
    RECORD*         arrayBis;

// dostęp publiczny
public:
    Iterator lastIndex()      { return lastRecordIndex; }
    Iterator firstIndex()     { return firstRecordIndex; }
    Iterator numberOfRecords(){ return numOfRecords; }

    void refreshArrayPointer(){ array = recordArray; }

    void fillWithRandomRecords(Iterator);
    void fillWithUniqueRandomRecords();

    void fillIncreasing();
    void fillDecreasing();

	void copyRecords(RECORD*, RECORD*, Iterator, Iterator);

//-----------------------------------------

// konstrukcja, destrukcja, dostęp
public:
    Array(long,long = 0);
    virtual ~Array(){
        delete[] recordArray;
        delete[] recordArrayBis;
    }

//----------------------------------------------
    void virtual badanieAlgorytmow();
	void virtual wypiszNaKonsole(bool = false){
		for(Iterator i = this->firstIndex(); i <= this->lastIndex(); ++i) this->array[i].display(0);
		cout << "\n************************\n\n";
	}

//----------------------------------------------
// metody pomocnicze
public:

// zamiana miejscami rekordów pierwszego i drugiego
    void swap(RECORD& a, RECORD& b){ RECORD tmp; tmp = a; a = b; b = tmp; }

// warunkowa zamiana miejscami rekordów (klucz drugi < klucz pierwszy)
    bool swapIf_a_GT_b(RECORD& a, RECORD& b){ if(a > b){ swap(a,b); return true; } else return false; }

// zamiana parami: na pozycjach a, b umieszczane są dwa miniejsze klucze, a na pozycjach c, d - dwa większe
// Uwaga: nie ma tu pełnego sortowania
    void swapIfLTfour(RECORD& a, RECORD& b, RECORD& c, RECORD& d);

// wybór najmniejszego klucza z trzech - trafia na pozycję a
// Uwaga: nie ma tu pełnego sortowania
    void swapIfLTthree(RECORD& a, RECORD& b, RECORD& c);

// warunkowa zamiana miejscami rekordów (klucz drugi > klucz pierwszy)
    bool swapIf_a_LT_b(RECORD& a, RECORD& b){ if(a < b){ swap(a,b); return true; } else return false; }

// odwrócenie kolejnosci w całej tablicy
    void swapArray();

// Przesuwanie iteratora w prawo, gdy kolejne klucze są takie same
    void moveIndexRight(Iterator&);
// Przesuwanie iteratora w lewo, gdy kolejne klucze są takie same
    void moveIndexLeft(Iterator&);

// Metody sortowania
#include "sortowanie.h"
};

#include "tablica.hpp"
#include "sortowanie.hpp"
#include "badanie_alg_sort-std.hpp"
#include "badanie_alg_sort-drzewa.hpp"

// End of Array template class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#if REKORD_Z_JEDNYM_KLUCZEM
class ArrayINT : public Array<ObjectINT>
{
public:
	ArrayINT(long liczZbior) : Array<ObjectINT>(liczZbior){};
#else
class ArrayINT : public Array<ObjectDoubleINT>
{
public:
	ArrayINT(long liczZbior) : Array<ObjectDoubleINT>(liczZbior){};
#endif
	
#include "zliczanie.h"
};
#include "zliczanie.hpp"

#endif //_TABLICA_H_
