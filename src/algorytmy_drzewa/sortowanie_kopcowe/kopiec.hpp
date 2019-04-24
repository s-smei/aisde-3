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

#ifndef _heap_hpp_
#define _heap_hpp_

#include "control.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Sortowanie przez kopcowanie
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-----------------------------------------------------------------------------
// Metody pomocnicze:
//-----------------------------------------------------------------------------
// Przywrocenie kopca (splyw do korzenia)
template <typename RECORD>
void Kopiec<RECORD>::fixUpHeap(Iterator child){
    while(child > 1){
        Iterator father = parentHeap(child);

        if(this->array[father] <= this->array[child]) break;

        this->swap(this->array[child], this->array[father]);
        child = father;
    };
};
//-----------------------------------------------------------------------------
// Przywrocenie kopca (splyw do liscia)
//-----------------------------------------------------------------------------
template <typename RECORD>
void Kopiec<RECORD>::fixDownHeap(Iterator father, Iterator last){
    Iterator child = leftChildHeap(father);

    while(child <= last){
        // Wybór "mniejszego" liścia
        if(child < last){
            if(this->array[child+1] < this->array[child]) ++child;
        }

        if(this->array[father] <= this->array[child]) break;
        this->swap(this->array[father], this->array[child]);

        father = child;
        child = leftChildHeap(father);
    }
}
//-----------------------------------------------------------------------------
// Ukopcowanie danych (wstępujące)
//-----------------------------------------------------------------------------
template <typename RECORD>
void Kopiec<RECORD>::bottomUpHeap(Iterator last){
    for(Iterator k = last/2; k >= 1; --k) fixDownHeap(k,last);
}
//-----------------------------------------------------------------------------
// Ukopcowanie danych (zstępujące)
//-----------------------------------------------------------------------------
template <typename RECORD>
void Kopiec<RECORD>::topDownHeap(Iterator last){
    for(Iterator k = 2; k <= last; ++k) fixUpHeap(k);
}
//-----------------------------------------------------------------------------
// Metoda pomocnicza do sortowania z zamiana korzenia z lisciem
//-----------------------------------------------------------------------------
template <typename RECORD>
void Kopiec<RECORD>::auxSortSwap(){
    Iterator curr = this->lastIndex();
    while(curr > 1){
        this->swap(this->array[1],this->array[curr]);
        --curr;
        fixDownHeap(1,curr);
    }
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Metody zasadnicze
//-----------------------------------------------------------------------------
// Sortowanie przez kopcowanie (zamiana korzenia z lisciem)
//-----------------------------------------------------------------------------
template <typename RECORD>
void Kopiec<RECORD>::heapSort_LeafRootExchange(){

// Ukopcowanie danych
#if KOPCOWANIE_ZSTEPUJACE
    topDownHeap(this->lastIndex());
#else // KOPCOWANIE_WSTEPUJACE
    bottomUpHeap(this->lastIndex());
#endif

// Sortowanie
    auxSortSwap();

#if KOPCOWANIE_ODWROCENIE
    this->swapArray();
#endif
}
//-----------------------------------------------------------------------------
// Sortowanie przez kopcowanie (odcinanie korzenia)
//-----------------------------------------------------------------------------
template <typename RECORD>
void Kopiec<RECORD>::heapSort_RootSeparation(){
    for(Iterator curr = this->lastIndex(); curr > 1; this->array++, --curr){
// Ukopcowanie danych
#if KOPCOWANIE_ZSTEPUJACE
        topDownHeap(curr);
#else // KOPCOWANIE_WSTEPUJACE
        bottomUpHeap(curr);
#endif

#if KOPCOWANIE_POPRAWKA
// poprawka przyspieszająca: odcinanie więcej niż tylko początkowego rekordu,
// jeżeli kolejne rekordy w tablicy mają taką samą wartość klucza co korzeń
        while(this->array[1] == this->array[2]){
            --curr;
            if(curr == 2) break;
            this->array++;
        }
#endif
	}

    this->refreshArrayPointer();

#if KOPCOWANIE_ODWROCENIE
    this->swapArray();
#endif
}
//-----------------------------------------------------------------------------

#endif
