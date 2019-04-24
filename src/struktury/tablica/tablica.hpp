//
//  Created by aw on 4/25/17.
//  Copyright (c) 2017 Adam Wojtasik. All rights reserved.
//

#ifndef cwicz3_tablica_hpp
#define cwicz3_tablica_hpp

//------------------------------------------------------------------------------------------------------------
// konstruktor
template <typename RECORD>
Array<RECORD>::Array(long size, long first) :
  numOfRecords(size), firstRecordIndex(first), lastRecordIndex(size+first-1), arraySize(size+first), recordArrayBis(nullptr)
{
    if(size <= 0) throw ERR_Object;
    if(first > 1) throw ERR_Object;

    recordArray = new(nothrow) RECORD[arraySize];
    if(recordArray == nullptr) throw ERR_Object;
    array = recordArray;

    #if not SORTOWANIE_W_MIEJSCU
    recordArrayBis = new(nothrow) RECORD[arraySize];
    if(recordArrayBis == nullptr) throw ERR_Object;
    #endif
    arrayBis = recordArrayBis;
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
// wypełnianie pseudoprzypadkowymi danymi (wartości kluczy mogą się powtarzać)
// Uwaga: REKORD musi być klasą mającą metodę randomDataFill
//------------------------------------------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::fillWithRandomRecords(Iterator max)
{
	for(Iterator curr = firstRecordIndex; curr <= lastRecordIndex; ++curr) recordArray[curr].randomDataFill(max);
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
// wypełnianie pseudoprzypadkowymi danymi (wartości kluczy nie mogą się powtarzać)
// Uwaga: REKORD musi być klasą mającą metodę uniqueDataFill
//------------------------------------------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::fillWithUniqueRandomRecords()
{
    for(Iterator curr = firstIndex(); curr <= lastIndex(); ++curr) recordArray[curr].uniqueDataFill(curr-firstIndex());
    for(Iterator curr = firstIndex(); curr <= lastIndex(); ++curr){
        Iterator index1 = firstIndex() + (Iterator)((long)(((double)rand()/(double)RAND_MAX)*(double)numberOfRecords()));
        if(curr != index1) swap(recordArray[index1],recordArray[curr]);
    }
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
// Wypełnianie ciągiem kolejnych liczb naturalnych, począwszy od zera.
// Uwaga: REKORD musi być klasą mającą metodę uniqueDataFill
template <typename RECORD>
void Array<RECORD>::fillIncreasing()
{
    for(Iterator curr = firstIndex(); curr <= lastIndex(); ++curr) recordArray[curr].uniqueDataFill(curr-firstIndex());
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
// Wypełnianie malejącym ciągiem kolejnych liczb naturalnych, skończywszy na zerze.
// Uwaga: REKORD musi być klasą mającą metodę uniqueDataFill
template <typename RECORD>
void Array<RECORD>::fillDecreasing()
{
    for(Iterator curr = firstIndex(); curr <= lastIndex(); ++curr) recordArray[curr].uniqueDataFill(lastIndex()-firstIndex()-curr);
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
// odwrócenie kolejnosci w tablicy
//------------------------------------------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::swapArray(){
    for (Iterator first = firstRecordIndex, last = lastRecordIndex; first < last; ++first, --last)
        swap(array[first],array[last]);
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
// Przesuwanie iteratora w prawo, gdy kolejne klucze są takie same
//------------------------------------------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::moveIndexRight(Iterator& first){
	while(array[first] == array[first+1]){ ++first; if(first == lastIndex()) break; }
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
// Przesuwanie iteratora w lewo, gdy kolejne klucze są takie same
//------------------------------------------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::moveIndexLeft(Iterator& last){
    while(array[last] == array[last-1]){ --last; if(last == firstIndex()) break; }
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
// Selekcja dwa z czterech: dwa klucze mniejsze trafiają do a,b a dwa większe do c,d
//------------------------------------------------------------------------------------------------------------
template <typename RECORD>
inline void Array<RECORD>::swapIfLTfour(RECORD& a, RECORD& b, RECORD& c, RECORD& d){
    if(a > b){
        if(c > d){ if(a > d){ swap(a,d); if(b > c) swap(b,c); }}
        else{ if(a > c){ swap(a,c); if(b > d) swap(b,d); }}
    }
    else{
        if(c > d){ if(b > d){ swap(b,d); if(a > c) swap(a,c); }}
        else{ if(b > c){ swap(b,c); if(a > d) swap(a,d); }}
    }
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
// Selekcja najmniejszego z trzech: trafia on do a
//------------------------------------------------------------------------------------------------------------
template <typename RECORD>
inline void Array<RECORD>::swapIfLTthree(RECORD& a, RECORD& b, RECORD& c){
    if(b > c){ if(a > c) swap(a,c); }
    else{ if(a > b) swap(a,b); }
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
// Kopiowanie określonego zakresu rekordów z arrayBis do array
//------------------------------------------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::copyRecords(RECORD* source, RECORD* dest, Iterator first, Iterator last) {
  while(first <= last) {
    dest[first] = source[first];
    ++first;
  }
}
//------------------------------------------------------------------------------------------------------------


#endif
