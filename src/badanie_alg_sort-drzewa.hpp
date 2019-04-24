/******************************************************************************/
/*                               AISDE-Lab                                    */
/******************************************************************************/
    //
    //  Adam Wojtasik
    //  based on code by Grzegorz Janczyk
    //
/*  Instytut Mikroelektroniki i Optoelektroniki                               */
/*  Politechnika Warszawska                                                   */
/*  ul. Koszykowa 75                                                          */
/*  00-662 WARSZAWA                                                           */
/*  tel. +48 22 234 72 07                                                     */
/*  www.imio.pw.edu.pl                                                        */
/******************************************************************************/

#ifndef _drzewa_badanie_h
#define _drzewa_badanie_h
#if not CWICZENIE_2

//===============================================================================
// Badanie algorytmów sortowania metodami drzewiastymi
template <typename RECORD>
void Array<RECORD>::badanieAlgorytmow(){

#if WYPISZ_NA_KONSOLE
	wypiszNaKonsole();
#endif

    STATYSTYKA_START
    POMIAR_CZASU_RESET

    POMIAR_CZASU_START

//********************************************************************************
// UWAGA! W tym pliku może być odkomentowana tylko JEDNA linia wyboru rodzaju sortowania
//********************************************************************************

#if BADANIE_KOPCA
   heapSort_LeafRootExchange();
//    heapSort_RootSeparation();
	
//	swapArray();
	
#elif BADANIE_TURNIEJU
    this->tournamentSortLeft(this->firstIndex(), this->lastIndex());
//    this->tournamentSortRight(this->firstIndex(), this->lastIndex());
//    this->tournamentSortLeft_1(this->firstIndex(), this->lastIndex());
//    this->tournamentSortLeft_2(this->firstIndex(), this->lastIndex());
//    this->tournamentSortLeft_12(this->firstIndex(), this->lastIndex());
//    this->tournamentSortLeft_Complex(this->firstIndex(), this->lastIndex());

// Sortowanie mieszane turniejowo-szybkie
//    this->mixedSort(this->firstIndex(), this->lastIndex());
#endif

    POMIAR_CZASU_STOP
	STATYSTYKA_STOP

#if WYPISZ_NA_KONSOLE
    wypiszNaKonsole();
#endif
	Statystyka::raport("Sortowanie z użyciem drzewa");
}

#endif
#endif
