//
//  Created by Adam Wojtasik on 01/02/2018.
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//
// UWAGA: zawartość tego pliku jest częścią definicji szablonu klasy Array<RECORD>
// - można tu umieszczać wyłącznie elementy definicji ciała klasy

#ifndef scalanie_h
#define scalanie_h

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Sortowanie przez scalanie
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void mergeSortDescending       (Iterator, Iterator);
void mergeSortAscending        (Iterator, Iterator);
// pomocnicze:
void merge                     (Iterator, Iterator, Iterator);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif /* scalanie_h */

