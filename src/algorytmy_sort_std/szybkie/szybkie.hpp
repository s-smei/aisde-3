//
//  Created by Adam Wojtasik on 31/01/2018.
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//

#ifndef szybkie_hpp
#define szybkie_hpp

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Sortowanie szybkie
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-----------------------------------------------------------------------------
// Metody pomocnicze do filtrowania - zwracają indeks podziału tablicy na dwie części
//-----------------------------------------------------------------------------
// Schemat działania wg Hoare'a
//-----------------------------------------------------------------------------
// filtrowanie z użyciem pivota wziętego z ostatniego rekordu tablicy;
template <typename RECORD>
inline Iterator Array<RECORD>::partitioningHoareLast(Iterator first, Iterator last) {
    Iterator currLast = last;

    if(first < last){
        Iterator currFirst = first;

        while(true){
            // poszukiwanie pierwszego rekordu z kluczem większym od pivota (lub mu równym)
            while(array[currFirst] < array[last]) ++currFirst;
            if(currFirst == currLast) break;

            // poszukiwanie ostatniego rekordu z kluczem mniejszym od pivota
            --currLast;
            while(currLast > currFirst){
                if(array[currLast] < array[last]) break;
                --currLast;
            }
            if(currFirst == currLast) break;

            swap(array[currFirst],array[currLast]);
            ++currFirst;
        }
        if(currLast != last) swap(array[currLast],array[last]);
    }
    return currLast;
}
//-----------------------------------------------------------------------------
// filtrowanie z użyciem pivota wziętego z pierwszego rekordu tablicy
template <typename RECORD>
inline Iterator Array<RECORD>::partitioningHoareFirst(Iterator first, Iterator last) {
    swap(array[first],array[last]);
    return partitioningHoareLast(first,last);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Schemat działania wg Lomuto
//-----------------------------------------------------------------------------
// filtrowanie z użyciem pivota wziętego z ostatniego rekordutablicy
template <typename RECORD>
inline Iterator Array<RECORD>::partitioningLomutoLast(Iterator first, Iterator last) {

    // poszukiwanie pierwszego rekordu z kluczem większym od pivota
    Iterator curr = first;
    for(; curr <= last; ++curr)
        if(array[curr] > array[last]) break;

    Iterator mid = curr-1; // wskazuje ostatni "mały" (granica "małych" i "dużych")
    for(; curr <= last; ++curr){
        if(array[curr] <= array[last])
            swap(array[curr],array[++mid]);
    }
    return mid;
}
//-----------------------------------------------------------------------------
// filtrowanie z użyciem pivota wziętego z pierwszego rekordu tablicy
template <typename RECORD>
inline Iterator Array<RECORD>::partitioningLomutoFirst(Iterator first, Iterator last) {
    swap(array[first],array[last]);
    return partitioningLomutoLast(first,last);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Metoda pomocnicza: znajdowanie mediany (lekko poprawiony algorytm Hoare'a)
//-----------------------------------------------------------------------------
template <typename RECORD>
inline Iterator Array<RECORD>::calcMedianaHoare(Iterator first, Iterator last) {

    // dla nieparzystych zbiorów element środkowy
    // dla parzystych zbiorów tzw. mediana dolna
    Iterator mediana = first+(last-first)/2; // +1 gdyby szukać mediany górnej
    Iterator medLower = first;
    Iterator medUpper = last;
    Iterator curr;

    // tak długo, aż kolejny pivot nie znajdzie się w miejscu przewidywanym dla mediany
    do{
        curr = partitioningHoareLast(medLower, medUpper);
        if(mediana > curr) medLower = curr+1;
        else medUpper = curr-1;

    } while(mediana != curr);

    return mediana;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Metody zasadnicze: wersje rekurencyjne
//-----------------------------------------------------------------------------
// - metoda Hoare'a
// - pivot w ostatnim rekordzie
// - faktor wyłączający quickSort dla małych zbiorów
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::quickSortHoareFactor(Iterator first, Iterator last, const Iterator factor) {
REKURENCJA_WEJSCIE

    if(last-first > factor){
        // podział tablicy (filtrowanie)
        Iterator mid = partitioningHoareLast(first, last);
        // sortowanie podtablic
        quickSortHoareFactor(first, mid-1, factor);
        quickSortHoareFactor(mid+1, last, factor);
    }
    else insertionSort(first, last);

REKURENCJA_WYJSCIE
}
//-----------------------------------------------------------------------------
// wersja bez faktora
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::quickSortHoare(Iterator first, Iterator last) { quickSortHoareFactor(first, last, 0); }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// - metoda Lomuto
// - pivot w ostatnim rekordzie
// - faktor wyłączający quickSort dla małych zbiorów
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::quickSortLomutoFactor(Iterator first, Iterator last, const Iterator factor) {
REKURENCJA_WEJSCIE

    if(last-first > factor){
        // podział tablicy (filtrowanie)
        Iterator mid = partitioningLomutoLast(first, last);
        // sortowanie podtablic
        quickSortLomuto(first, mid-1);
        quickSortLomuto(mid+1, last);
    }
    else insertionSort(first, last);

REKURENCJA_WYJSCIE
}
//-----------------------------------------------------------------------------
// wersja bez faktora
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::quickSortLomuto(Iterator first, Iterator last) { quickSortLomutoFactor(first, last, 0); }
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// - metoda Hoare'a
// - pivot: mediana z ostatnich rekordów tablicy
// - faktor wyłączający quickSort dla małych zbiorów
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::quickSortHoareMedianaFactor(Iterator first, Iterator last, Iterator medianaSpread, const Iterator factor) {
    REKURENCJA_WEJSCIE

    if(last-first > factor){
        bool flag = true;
        if(last-first+1 <= medianaSpread){
            medianaSpread = last-first+1;
            flag = false;
        }
        // ustalenie pivota
        Iterator pivot = calcMedianaHoare(last-medianaSpread+1, last);

        // podział tablicy (filtrowanie)
        // UWAGA: wykorzystywane tu są właściwości zastosowanego algorytmu znajdowania mediany - fragment tablicy od last-medianaSpread+1
        // do last został przez procedurę calcMedianaHoare już uporządkowany względem jej elementu środkowego pivot zawierającego medianę.
        // Nie ma więc potrzeby w kolejnym kroku filtrowania rozpatrywania rekordów o indeksach większych od pivot.
        // Krok ten natomiast nie jest w całości potrzebny jeśli mediana była liczona z całej tablicy, bo filtrowanie odbyło się wewnątrz calcMedianaHoare.
        if(flag) pivot = partitioningHoareLast(first, pivot);

        // sortowanie podtablic
        quickSortHoareMedianaFactor(first, pivot-1, medianaSpread, factor);
        quickSortHoareMedianaFactor(pivot+1, last, medianaSpread, factor);
    }
    // sortowanie małego zbioru
    else insertionSort(first, last);

    REKURENCJA_WYJSCIE
}
//-----------------------------------------------------------------------------
// wersja bez faktora
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::quickSortHoareMediana(Iterator first, Iterator last, const Iterator mediana) { quickSortHoareMedianaFactor(first, last, mediana, 0); }
//-----------------------------------------------------------------------------


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif /* szybkie_hpp */
