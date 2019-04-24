//
//  Created by Adam Wojtasik on 31/01/2018.
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//

#ifndef selekcja_hpp
#define selekcja_hpp

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Sortowanie przez selekcję
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-----------------------------------------------------------------------------
// Metody pomocnicze:
//-----------------------------------------------------------------------------
// przegląd bezpośredni prawej części tablicy - wybór indeksu aktualnie najmniejszego klucza;
// zamiana wybranego rekordu z pierwszym następuje po zakończeniu przeglądu
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::directSelectionRight(Iterator start, Iterator last)
{
    Iterator curr = start;
    for(Iterator j = start+1; j <= last; ++j){
        if(array[curr] > array[j]) curr = j;
    }
    if(curr != start) swap(array[start],array[curr]);
}
//-----------------------------------------------------------------------------
// przegląd bezpośredni lewej części tablicy - wybór indeksu aktualnie największego klucza;
// zamiana wybranego rekordu ze startowym następuje po zakończeniu przeglądu
template <typename RECORD>
void Array<RECORD>::directSelectionLeft(Iterator first, Iterator start)
//-----------------------------------------------------------------------------
{
    Iterator curr = start;
    for(Iterator j = start-1; j >= first; --j){
        if(array[curr] < array[j]) curr = j;
    }
    if(curr != start) swap(array[start],array[curr]);
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Metody zasadnicze:
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::selectionSort(Iterator first, Iterator last)
{
#if SELEKCJA_START_OD_PRAWEJ
    for(; last > first; --last) {
#if SELEKCJA_INDEX
        directSelectionLeft(first,last);
#else
        for(Iterator j = last-1; j >= first; --j){
            swapIf_a_LT_b(array[last],array[j]);
        }
#endif
    }
#else
    for(; first < last; ++first) {
#if SELEKCJA_INDEX
        directSelectionRight(first,last);
#else
        for(Iterator j = first+1; j <= last; j++){
            swapIf_a_GT_b(array[first],array[j]);
        }
#endif
    }
#endif
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif /* selekcja_hpp */
