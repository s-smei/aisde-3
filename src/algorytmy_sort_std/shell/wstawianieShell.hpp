//
//  Created by Adam Wojtasik on 03/02/2018.
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//

#ifndef wstawianieShell_hpp
#define wstawianieShell_hpp

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Sortowanie Shella
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-----------------------------------------------------------------------------
// Sortowanie Shella z wykorzystaniem wstawiania
// Sortowanie zaczynane z prawej strony tablicy (od największych)
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::insertionSortShell(Iterator first, Iterator last, SequenceGenerator* ciag)
{
    Iterator h;
    do{
        h = ciag->remove();
#if WSTAWIANIE_START_OD_PRAWEJ
        for (Iterator start = last; start >= last-h; --start) insertionSort(first, start, h);
#else // START_OD_LEWEJ
        for(Iterator start = first; start <= h; ++start) insertionSort(start, last, h);
#endif
    } while (h != 1);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Pomocnicze:
//-----------------------------------------------------------------------------
// Poszukiwanie miejsca do wstawienia metodą bisekcji, wersja dla sortowania Shella
//-----------------------------------------------------------------------------
template <typename RECORD>
#if WSTAWIANIE_START_OD_PRAWEJ
inline Iterator Array<RECORD>::searchBisectionShell(Iterator start, Iterator last, Iterator h)
{
    Iterator lower = 0;
    Iterator upper = (last-start)/h;
    while(true){
        Iterator curr = (upper+lower)/2;
        if(curr == lower){
            if(array[start] > array[start+upper*h]) lower = upper;
            break;
        }
        if(array[start] <= array[start+curr*h]) upper = curr;
        else lower = curr;
    }
    return start + lower*h;
#else
inline Iterator Array<RECORD>::searchBisectionShell(Iterator first, Iterator start, Iterator h)
{
    Iterator upper = 0;
    Iterator lower = (start-first)/h;
    while(true){
        Iterator curr = (upper+lower)/2;
        if(curr == upper){
            if(array[start] < array[start-lower*h]) upper = lower;
            break;
        }
        if(array[start] >= array[start-curr*h]) lower = curr;
        else upper = curr;
    }
    return start - upper*h;
#endif
}
//-----------------------------------------------------------------------------


#endif /* wstawianieShell_hpp */
