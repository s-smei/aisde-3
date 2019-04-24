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


#ifndef _KOPIEC_H_
#define _KOPIEC_H_

#include "tablica.h"

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

template <typename RECORD>
class Kopiec : public Array<RECORD>{
protected:

public:
    Kopiec<RECORD>(unsigned long LiczZbior) : Array<RECORD>(LiczZbior, 1){};
    ~Kopiec<RECORD>(){};

// ==========================================
// Metody traktujace drzewo jako kopiec
protected:
    Iterator leftChildHeap (Iterator i){ return i*2; };
    Iterator rightChildHeap(Iterator i){ return leftChildHeap(i)+1; };
    Iterator parentHeap    (Iterator i){ return i/2; };

    void     fixUpHeap(Iterator);             // Przywrocenie kopca (splyw do korzenia)
    void     fixDownHeap(Iterator, Iterator); // Przywrocenie kopca (splyw do liscia)

    void     bottomUpHeap(Iterator);          // Ukopcowanie danych (wstępujące)
    void     topDownHeap(Iterator);           // Ukopcowanie danych (zstępujące)

    void     heapSort_LeafRootExchange();     // Sortowanie przez kopcowanie (zamiana korzenia i liscia)
    void     heapSort_RootSeparation();       // Sortowanie przez kopcowanie (odcinanie korzenia) z kopcowaniem wstepujacym
private:
    void     auxSortSwap();                   // pomocnicza do sortowania z zamiana korzenia i liscia

public:
    void     wypiszNaKonsole(bool = false) { Statystyka::wypiszNaKonsole(); }
};

#include "kopiec.hpp"
#include "badanie_alg_sort-drzewa.hpp"



/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
// Kopiec z najprostrzym rekordem danych - liczbą typu integer

class KopiecINT : public Kopiec<ObjectINT>
{
public:
    KopiecINT(long liczZbior) : Kopiec<ObjectINT>(liczZbior){};

    void wypiszNaKonsole(bool = false);
};



#endif //_KOPIEC_H_
