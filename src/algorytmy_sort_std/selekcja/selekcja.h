//
//  Created by Adam Wojtasik on 31/01/2018.
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//

// UWAGA: zawartość tego pliku jest częścią definicji szablonu klasy Array<RECORD>
// - można tu umieszczać wyłącznie elementy definicji ciała klasy

#ifndef selekcja_h
#define selekcja_h

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Sortowanie przez selekcję
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void selectionSort        (Iterator, Iterator);
// pomocnicze:
// selekcja bezpośrednia - wybrany rekord trafia na skrajne miejsce w tablicy (wersje z buforem)
void directSelectionLeft  (Iterator, Iterator); // szukanie po lewej, wstawienie na koniec tablicy
void directSelectionRight (Iterator, Iterator); // szukanie po prawej, wstawienie na początek tablicy
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif /* selekcja_h */
