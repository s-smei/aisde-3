//
//  Created by Adam Wojtasik on 31/01/2018.
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//
// UWAGA: zawartość tego pliku jest częścią definicji szablonu klasy Array<RECORD>
// - można tu umieszczać wyłącznie elementy definicji ciała klasy

#ifndef _TURNIEJ_H_
#define _TURNIEJ_H_

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Sortowanie turniejowe
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// pomocnicze:
// pojedyncza runda pojedynków
Iterator roundLT                    (Iterator, Iterator);
Iterator roundLTBis                 (Iterator, Iterator);
void     roundGT                    (Iterator, Iterator);
Iterator roundLTfour                (Iterator, Iterator);
Iterator roundLTfourBis             (Iterator, Iterator);

// turniej - wyłanianie zwycięzcy
void     tournamentLeft             (Iterator, Iterator);
void     tournamentRight            (Iterator, Iterator);

// procedury sortowania turniejowego
void     tournamentSortLeft         (Iterator, Iterator);
void     tournamentSortRight        (Iterator, Iterator);
void     tournamentSortLeft_1       (Iterator, Iterator);
void     tournamentSortLeft_2       (Iterator, Iterator);
void     tournamentSortLeft_12      (Iterator, Iterator);
void     tournamentSortLeft_Complex (Iterator, Iterator);

// procedury sortowania mieszanego: turniejowo-szybkiego
void     mixedSort                  (Iterator, Iterator);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif
