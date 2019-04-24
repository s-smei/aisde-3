//
//  Created by aw on 4/25/17.
//  Copyright (c) 2017 Adam Wojtasik. All rights reserved.
//
// UWAGA: zawartość tego pliku jest częścią definicji szablonu klasy Array<RECORD>
// - można tu umieszczać wyłącznie elementy definicji ciała klasy
#ifndef _sortowanie_h
#define _sortowanie_h

#include "selekcja.h"
#include "szybkie.h"
#include "wstawianie.h"
#include "wstawianieShell.h"
#include "scalanie.h"
#include "babelkowe.h"
#include "turniej.h"


//--------------------------------------------------------------------
virtual void     heapSort_LeafRootExchange(){}
virtual void     heapSort_RootSeparation(){}
virtual void     countingSort(Iterator,Iterator){}

#endif
