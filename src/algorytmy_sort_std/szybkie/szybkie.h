//
//  Created by Adam Wojtasik on 31/01/2018.
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//

// UWAGA: zawartość tego pliku jest częścią definicji szablonu klasy Array<RECORD>
// - można tu umieszczać wyłącznie elementy definicji ciała klasy

#ifndef szybkie_h
#define szybkie_h

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Sortowanie szybkie
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void quickSortHoare              (Iterator, Iterator);
void quickSortHoareFactor        (Iterator, Iterator, const Iterator);
void quickSortHoareMediana       (Iterator, Iterator, const Iterator);
void quickSortHoareMedianaFactor (Iterator, Iterator, Iterator, const Iterator);

void quickSortLomuto             (Iterator, Iterator);
void quickSortLomutoFactor       (Iterator, Iterator, const Iterator);

// pomocnicze:
Iterator partitioningHoareLast        (Iterator, Iterator);
Iterator partitioningHoareFirst       (Iterator, Iterator);

Iterator partitioningLomutoFirst      (Iterator, Iterator);
Iterator partitioningLomutoLast       (Iterator, Iterator);

Iterator calcMedianaHoare             (Iterator, Iterator);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif /* szybkie_h */
