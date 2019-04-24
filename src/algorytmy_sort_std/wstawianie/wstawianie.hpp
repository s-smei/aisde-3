//
//  Created by Adam Wojtasik on 01/02/2018.
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//

#ifndef wstawianie_hpp
#define wstawianie_hpp

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Sortowanie przez wstawianie
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Uwaga: Na liście argumentów trzeci Iterator (h) wykorzystywany jest w sortowaniu Shella
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Metody pomocnicze:
//-----------------------------------------------------------------------------
// Poszukiwanie miejsca metodą przeglądu bezpośredniego
//-----------------------------------------------------------------------------
template <typename RECORD>
#if WSTAWIANIE_START_OD_PRAWEJ
inline Iterator Array<RECORD>::searchDirect(Iterator curr, Iterator last, Iterator h)
{
    Iterator ret = curr+h;
    for(; ret <= last; ret+=h) if(array[ret] >= array[curr]) break;
    return ret-h;
#else // START_OD_LEWEJ
inline Iterator Array<RECORD>::searchDirect(Iterator first, Iterator curr, Iterator h)
{
    Iterator ret = curr-h;
    for(; ret >= first; ret-=h) if(array[ret] <= array[curr]) break;
    return ret+h;
#endif
}
//-----------------------------------------------------------------------------
// Poszukiwanie miejsca metodą bisekcji
//-----------------------------------------------------------------------------
template <typename RECORD>
#if WSTAWIANIE_START_OD_PRAWEJ
inline Iterator Array<RECORD>::searchBisection(Iterator start, Iterator last)
{
    Iterator lower = start;
    Iterator upper = last;
    while(true){
        Iterator curr = (upper+lower)/2;
        if(curr == lower){
            if(array[start] > array[upper]) lower = upper;
            break;
        }
        if(array[start] <= array[curr]) upper = curr;
        else lower = curr;
    }
    return lower;
#else  // wstawianie START_OD_LEWEJ
inline Iterator Array<RECORD>::searchBisection(Iterator first, Iterator start)
{
    Iterator lower = first;
    Iterator upper = start;
    while(true){
        Iterator curr = (upper+lower)/2;
        if(curr == lower){
            if(array[start] < array[lower]) upper = lower;
            break;
        }
        if(array[start] >= array[curr]) lower = curr;
        else upper = curr;
    }
    return upper;
#endif
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Wstawianie rekordu na odpowiednie miejsce
//-----------------------------------------------------------------------------
template <typename RECORD>
    // Poszukiwanie miejsca do wstawienia
#if WSTAWIANIE_START_OD_PRAWEJ
inline void Array<RECORD>::insert(Iterator curr, Iterator last, Iterator h)
{
    // Szukanie miejsca do wstawienia rekordu
#if WSTAWIANIE_BISEKCJA
#if WSTAWIANIE_SHELL
    Iterator dest = searchBisectionShell(curr, last, h);
#else
    Iterator dest = searchBisection(curr, last);
#endif
#else
    Iterator dest = searchDirect(curr, last, h);
#endif
    // Przesuwanie rekordów
    if(dest != curr){
        RECORD bufor = array[curr];
        for(Iterator iter = curr; iter < dest; iter+=h) array[iter] = array[iter+h];
        array[dest] = bufor;
    }
#else  // wstawianie START_OD_LEWEJ
inline void Array<RECORD>::insert(Iterator first, Iterator curr, Iterator h)
{
    // Szukanie miejsca do wstawienia rekordu
#if WSTAWIANIE_BISEKCJA
#if WSTAWIANIE_SHELL
    Iterator dest = searchBisectionShell(first, curr, h);
#else
    Iterator dest = searchBisection(first, curr);
#endif
#else
    Iterator dest = searchDirect(first, curr, h);
#endif
    // Przesuwanie rekordów
    if(dest != curr){
        RECORD bufor = array[curr];
        for(Iterator iter = curr; iter > dest; iter-=h) array[iter] = array[iter-h];
        array[dest] = bufor;
    }
#endif
}
//-----------------------------------------------------------------------------


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Procedury sortowania przez wstawianie w wersji dla sortowania Shella
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-----------------------------------------------------------------------------
// Metoda zasadnicza
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::insertionSort(Iterator first, Iterator last, Iterator h)
{
#if WSTAWIANIE_START_OD_PRAWEJ
    for(Iterator curr = last-h; curr >= first; curr-=h) insert(curr, last, h);
#else // START_OD_LEWEJ
    for(Iterator curr = first+h; curr <= last; curr+=h) insert(first, curr, h);
#endif
}
//-----------------------------------------------------------------------------

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif /* wstawianie_hpp */
