//-----------------------------------------------------------------------------
// Uruchomienie danego sortowania polega na odkomentowaniu odpowiedniej linijki (dla sortowania Shella trzech linijek)
// Należy też ustalić wersję algorytmu przez ustawienie flag w pliku control_sort-std.h
//-----------------------------------------------------------------------------
//******************************************************************************************************
// UWAGA! W tym pliku może być odkomentowana tylko JEDNA linia wyboru rodzaju sortowania
//******************************************************************************************************


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UWAGA: należy bezwzględnie zadbać o zgodność flag sterowania w pliku control_sort-std.h z rodzajem wybranego sortowania
// Nieprawidłowe wartości flag mogą dać nieprzewidywalne rezultaty
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UWAGA: niektóre algorytmy korzystają z procedur składowych innych algorytmów (lub nawet z całych algorytmów)
// zatem flagi w pliku control.h mogą wpływać na różne algorytmy, nie tylko na algorytmy związane z nazwą flagi
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#ifndef _badanie_algorytmow_
#define _badanie_algorytmow_
#if CWICZENIE_2

#include "generator.h"

template <typename RECORD>
void Array<RECORD>::badanieAlgorytmow(){
#if WYPISZ_NA_KONSOLE
    wypiszNaKonsole();
#endif
    STATYSTYKA_START
    POMIAR_CZASU_RESET


    POMIAR_CZASU_START

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Sortowanie przez selekcję
//-----------------------------------------------------------------------------
this->selectionSort(this->firstIndex(), this->lastIndex());

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Sortowanie przez wstawianie
//-----------------------------------------------------------------------------
//    this->insertionSort(this->firstIndex(), this->lastIndex());

/*
    SequenceGenerator* ciag = new KnuthSequenceGenerator(lastIndex());
//  SequenceGenerator* ciag = new SedgewickSequenceGenerator(lastIndex());
//  SequenceGenerator* ciag = new TokudaSequenceGenerator(lastIndex());
//  SequenceGenerator* ciag = new CustomSequenceGenerator(lastIndex());

    this->insertionSortShell(this->firstIndex(), this->lastIndex(), ciag);
    delete ciag;
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Sortowanie szybkie
//-----------------------------------------------------------------------------
//    this->quickSortLomuto(this->firstIndex(), this->lastIndex());
//
//    this->quickSortHoare(this->firstIndex(), this->lastIndex());
//    this->quickSortHoareFactor(this->firstIndex(), this->lastIndex(), 9);
//    this->quickSortHoareMedianaFactor(this->firstIndex(), this->lastIndex(), 3, 0);
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Sortowanie przez scalanie
//-----------------------------------------------------------------------------
//    this->mergeSort(this->firstIndex(), this->lastIndex());
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Sortowanie bąbelkowe
//-----------------------------------------------------------------------------
//    this->bubbleSort(this->firstIndex(), this->lastIndex());
//    this->shakerSort(this->firstIndex(), this->lastIndex());
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Sortowanie przez zliczanie
//-----------------------------------------------------------------------------
//   this->countingSort(this->firstIndex(), this->lastIndex());
//-----------------------------------------------------------------------------

	
    POMIAR_CZASU_STOP
	STATYSTYKA_STOP

#if WYPISZ_NA_KONSOLE
    wypiszNaKonsole();
#endif
    Statystyka::raport("Badanie algorytmów sortowania");
}

#endif
#endif // _badanie_algorytmow_
