//
//  Created by Adam Wojtasik on 31/01/2018.
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//

#ifndef _tournament_hpp_
#define _tournament_hpp_

//-----------------------------------------------------------------------------
// Metody pomocnicze:
//-----------------------------------------------------------------------------
// Jedna runda pojedynków - porównywane są pierwszy z ostatnim, drugi z przedostatnim itd.
// Mniejszy trafia w "lewą" czesc tablicy
//-----------------------------------------------------------------------------
template <typename RECORD>
inline Iterator Array<RECORD>::roundLT(Iterator first, Iterator last){
    for(; first < last; ++first, --last){
        this->swapIf_a_GT_b(this->array[first], this->array[last]);
    }

    if(first == last){
        --last;
        this->swapIf_a_GT_b(this->array[last], this->array[first]);
    }
    return last;
}
//-----------------------------------------------------------------------------
// Jedna runda pojedynków - porównywane są pierwszy z ostatnim, drugi z przedostatnim itd.
// Mniejszy trafia w "prawą" czesc tablicy
//-----------------------------------------------------------------------------
template <typename RECORD>
inline void Array<RECORD>::roundGT(Iterator first, Iterator last){
    for(; first < last; ++first, --last)
        this->swapIf_a_LT_b(this->array[first], this->array[last]);
}
//-----------------------------------------------------------------------------
// Jedna runda pojedynków - porównywane są pierwszy ze środkowym, drugi ze środkowym+1 itd.
// Mniejszy trafia w "lewą" czesc tablicy
//-----------------------------------------------------------------------------
template <typename RECORD>
inline Iterator Array<RECORD>::roundLTBis(Iterator first, Iterator last){
    Iterator curr = first+(last-first+1)/2;
    Iterator mid = curr;
    for(; first < mid; ++first, ++curr)
        this->swapIf_a_GT_b(this->array[first], this->array[curr]);

    --first;
    if(curr == last) this->swapIf_a_GT_b(this->array[first], this->array[last]);

    return first;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Turniej - wyłanianie najmniejszego
// Po danej rundzie najmniejszy na pewno trafił do lewej połówki tablicy.
// Kolejną rundę przeprowadza się wiec tylko dla tej połówki.
// Ostatecznie najmniejszy trafia na pierwszą pozycję w tablicy.
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::tournamentLeft(Iterator first, Iterator last){
    while(last > first){
        this->roundLT(first,last);
// obliczenie położenia środka tablicy (z uwzględnieniem ew. nieparzystości rozmiaru)
        last = first + ((last - first)/2);
    }
}
//-----------------------------------------------------------------------------
// Turniej - wyłanianie najwiekszego
// W danej rundzie najwiekszy na pewno trafił do prawej połówki tablicy.
// Kolejną runde przeprowadza się wiec tylko dla tej połówki.
// Ostatecznie największy trafia na ostatnia pozycję w tablicy.
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::tournamentRight(Iterator first, Iterator last){
    while(last > first){
        this->roundLT(first,last);
// obliczenie położenia środka tablicy (z uwzględnieniem ew. nieparzystości rozmiaru)
        first = last - ((last - first)/2);
    }
}
//-----------------------------------------------------------------------------
// Jedna runda pojedynków "deblowych" - porównywane są dwa pierwsze rekordy z dwoma ostatnimi,
// trzeci i czwarty z trzecim i czwartym od końca itd.
// Dwa z najmniejszymi kluczami z tych czterech trafiają w "lewą" czesc tablicy
template <typename RECORD>
inline Iterator Array<RECORD>::roundLTfour(Iterator first, Iterator last){
	--last;
    ++first;
    for(; first < last; first+=2, last-=2){
        this->swapIfLTfour(this->array[first-1], this->array[first],
                           this->array[last], this->array[last+1]);
    }

    Iterator ret;
    // Rozpatrzenie przypadków, gdy rozmiar tablicy jest nieparzysty i/lub niepodzielny przez 4
    switch(first-last){
        case 0: // nieparzysty, podzielny przez 4 z resztą 3
            ret = first-1;
            this->swapIfLTthree(this->array[ret], this->array[first], this->array[first+1]);
            break;
        case 1: // parzysty, podzielny przez 4 z resztą 2
            ret = first-1;
            this->swapIf_a_LT_b(this->array[ret], this->array[first]);
            break;
        case 2: // nieparzysty, podzielny przez 4 z resztą 1
            ret = first-2;
            this->swapIf_a_LT_b(this->array[ret], this->array[first-1]);
            break;
        default: // parzysty, podzielny przez 4 bez reszty
            ret = first-2;
            break;
    }
    return ret;
}
//-----------------------------------------------------------------------------
// Jedna runda pojedynków "deblowych" - porównywane są dwa pierwsze z dwoma pierwszymi w prawej połówce tablicy,
// trzeci i czwarty z trzecim i czwartym w prawej połówce, itd.
// Dwa mniejsze z tych czterech trafiają w "lewą" czesc tablicy
template <typename RECORD>
inline Iterator Array<RECORD>::roundLTfourBis(Iterator first, Iterator last){

    Iterator curr = first+1+(last-first)/2;
    for(; curr < last; first+=2, curr+=2){
        this->swapIfLTfour(this->array[first], this->array[first+1],
                           this->array[curr], this->array[curr+1]);
    }

    Iterator ret;
    // Rozpatrzenie przypadków, gdy rozmiar tablicy jest nieparzysty lub niepodzielny przez 4
    if(curr == last){
        ret = first;
        this->swapIfLTthree(this->array[ret], this->array[first+1], this->array[curr]);
    }
    else{
        ret = first-1;
        this->swapIf_a_LT_b(this->array[ret], this->array[first]);
    }

    return ret;
}


//-----------------------------------------------------------------------------
// Metody zasadnicze:
//-----------------------------------------------------------------------------
// podstawowe
//-----------------------------------------------------------------------------
// Sortowanie od najmniejszego do najwiekszego
// Kolejne turnieje umieszczają z lewej strony kolejny rekord z najmniejszym kluczem
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::tournamentSortLeft(Iterator first, Iterator last){
    while(first < last){
        tournamentLeft(first,last);
        ++first;
    }
}
//-----------------------------------------------------------------------------
// Sortowanie od najmniejszego do najwiekszego
// Kolejne turnieje umieszczają z prawej strony kolejny rekord z największym kluczem
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::tournamentSortRight(Iterator first, Iterator last){
    while(first < last){
        tournamentRight(first,last);
        --last;
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// z modyfikacjami polepszającymui wydajność algorytmu
//-----------------------------------------------------------------------------
// Sortowanie od najmniejszego do najwiekszego
// Kolejne turnieje umieszczają z lewej strony kolejny rekord z najmniejszym kluczem
// Modyfikacja 1: tablica zmniejszana jest gdy sasiednie klucze sa takie same
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::tournamentSortLeft_1(Iterator first, Iterator last){
    while(first < last){
        tournamentLeft(first,last);
        this->moveIndexRight(first);
        ++first;
    }
}
//-----------------------------------------------------------------------------
// Podstawowe jest sortowanie od najmniejszego do największego
// Modyfikacja 2: po pierwszej rundzie, rekord o największym kluczu jest na pewno w prawej cześci tablicy,
// wiec dla tej połówki przeprowadzany jest "odwrotny" turniej ustawiajacy największy na koncu tablicy
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::tournamentSortLeft_2(Iterator first, Iterator last){
    while(first < last){
// turniej podstawowy
        tournamentLeft(first,last);
        ++first;

// turniej dodatkowy dla "przegranych" w prawej połówce tablicy
        tournamentRight(last-((last-first)/2),last);
        --last;
    }
}
//-----------------------------------------------------------------------------
// Modyfikacja 1i2: zastosowano obydwie modyfikacje (1 i 2)
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::tournamentSortLeft_12(Iterator first, Iterator last){
    while(first < last){
        tournamentLeft(first,last);
        tournamentRight(last-((last-first)/2),last);

        this->moveIndexRight(first);
        this->moveIndexLeft(last);
        ++first;
        --last;
    }
}
//-----------------------------------------------------------------------------
// Modyfikacja Complex:
// - to samo co w modyfikacjach 1 i 2
// - dodatkowe turnieje w połówkach tablicy: szukanie największego w lewej (NL) i najmniejszego w prawej (NP),
//   Jeżeli NL <= NP, to oba te rekordy są na swoim ostatecznym miejscu, więc można dalej połówki sortować niezależnie
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::tournamentSortLeft_Complex(Iterator first, Iterator last){
	REKURENCJA_WEJSCIE

	bool flag = false;
    Iterator mid = 0;
    while(first < last){
// turniej podstawowy
        tournamentLeft(first,last);

// turniej dodatkowy dla "przegranych" w prawej polowce tablicy
        mid = last-((last-first)/2);
        tournamentRight(mid,last);

// przesuniecie iteratorow, gdy brzegowe klucze sa rowne
        this->moveIndexRight( first );
        this->moveIndexLeft ( last  );

// turnieje "w przeciwnym kierunku" w polowkach
        tournamentRight( first+1, mid-1  );
        tournamentLeft ( mid,     last-1 );

        this->moveIndexRight( first );
        this->moveIndexLeft ( last  );

        ++first;
        --last;

// sprawdzenie, czy sortowanie w polowkach stalo sie niezalezne
		if(this->array[mid-1] <= this->array[mid]){ flag = true; break; }

// zamiana na styku polowek (konieczna, gdy rozmiar tablicy jest nieparzysty - dla parzystego rozmiaru
// moze byc, choc nie jest krytyczna)
        swap(this->array[mid-1],this->array[mid]);
    }

    if(flag){
// sortowanie w polowkach jest niezalezne - mozna oddzielnie w nich sortowac
       tournamentSortLeft_Complex(first, mid-1);
       tournamentSortLeft_Complex(mid,   last);
   }

	REKURENCJA_WYJSCIE
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Sortowanie mieszane na bazie turnieju, z elementami selekcji i sortowania szybkiego
// plus wstawianie dla małych zbiorów
//-----------------------------------------------------------------------------
template <typename RECORD>
void Array<RECORD>::mixedSort(Iterator first, Iterator last){
    REKURENCJA_WEJSCIE

    // procedura nie ma sensu dla zbyt małych zbiorów
    if(last-first > 12){
        // runda turnieju deblowego przeprowadzona dwa razy (dwoma różnymi sposobami)
        Iterator mid = roundLTfour(first,last);
        Iterator mid1 = mid+1;
        roundLTfourBis(first,last);

        // selekcja największego klucza w lewej połówce tablicy (NL) i najmniejszego w prawej (NP)
        directSelectionLeft(first,mid);
        directSelectionRight(mid1,last);

        // jeżeli NL <= NP, to oba te rekordy są na swoim ostatecznym miejscu więc połówki tablicy można procedować osobno
        if(array[mid] <= array[mid1]){
            mixedSort(first, mid-1);
            mixedSort(mid1+1, last);
        }
        else{
            // wykonanie w obu połówkach tablicy filtrowania quicksortowego:
            // największy klucz lewej połówki jest pivotem dla połówki prawej
            // najmniejszy klucz z prawej połówki jest pivotem dla lewej
            swap(array[mid],array[mid1]);
            Iterator mid0 = partitioningHoareLast(first, mid);
            Iterator mid2 = partitioningHoareFirst(mid1, last);

            // uzyskany został podział tablicy na trzy niezależne części
            mixedSort(mid0+1, mid2-1);
            mixedSort(first,  mid0-1);
            mixedSort(mid2+1, last);
        }
    }
    else insertionSort(first,last);

    REKURENCJA_WYJSCIE
}
//-----------------------------------------------------------------------------

#endif
