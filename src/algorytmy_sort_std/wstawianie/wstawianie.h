//
//  Created by Adam Wojtasik on 01/02/2018.
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//
// UWAGA: zawartość tego pliku jest częścią definicji szablonu klasy Array<RECORD>
// - można tu umieszczać wyłącznie elementy definicji ciała klasy

#ifndef wstawianie_h
#define wstawianie_h

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Sortowanie przez wstawianie
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void insertionSort       (Iterator, Iterator, Iterator = 1);
// pomocnicze:
// wstawianie danego rekordu na odpowiednie miejsce (z buforem, bez strażnika)
// trzeci Iterator różny od 1 stosowany jest tylko przy sortowaniu Shella
Iterator searchDirect    (Iterator, Iterator, Iterator = 1);
Iterator searchBisection (Iterator, Iterator);
void     insert          (Iterator, Iterator, Iterator = 1);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif /* wstawianie_h */

