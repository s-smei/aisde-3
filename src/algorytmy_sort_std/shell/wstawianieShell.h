//
//  Created by Adam Wojtasik on 03/02/2018.
//  Copyright © 2018 Institute of Microelectronics and Optoelectronics. All rights reserved.
//

#ifndef wstawianieShell_h
#define wstawianieShell_h

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Sortowanie Shella - przez wstawianie
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void     insertionSortShell   (Iterator, Iterator,SequenceGenerator*);

// pomocnicze:
Iterator searchBisectionShell (Iterator, Iterator, Iterator);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif /* wstawianieShell_h */
