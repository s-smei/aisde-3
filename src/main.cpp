/******************************************************************************/
/******************************************************************************/
/*                               AISDE-Lab                                    */
/******************************************************************************/
    //
    //  Adam Wojtasik
    //  based on code by Grzegorz Janczyk
    //
/*  Instytut Mikroelektroniki i Optoelektroniki                               */
/*  Politechnika Warszawska                                                   */
/*  ul. Koszykowa 75                                                          */
/*  00-662 WARSZAWA                                                           */
/*  tel. +48 22 234 72 07                                                     */
/*  www.imio.pw.edu.pl                                                        */
/******************************************************************************/

#define _MAIN_CPP_
#include "tablica.h"
#include "kopiec.h"
#include "bst.h"
#include "huffman.h"

ArrayINT*   tablicaINT = nullptr;

KopiecINT*  kopiecINT  = nullptr;
BstHeadINT* bstINT     = nullptr;
Huffman*    huffman    = nullptr;

/******************************************************************************/


int main(){
	try{
    if (seed == 0) throw Error(ERR_NoIndex);
/******************************************************************************/
#if CWICZENIE_2
/******************************************************************************/
//------------------------------------------------------------------------------
    tablicaINT = new(nothrow) ArrayINT(licznosc);
    if(tablicaINT == nullptr) throw Error(ERR_Object);

#if   CIAG_WEJSCIOWY_ROSNACY
        tablicaINT->fillIncreasing();
#elif CIAG_WEJSCIOWY_MALEJACY
        tablicaINT->fillDecreasing();
#elif KLUCZE_UNIKATOWE
        tablicaINT->fillWithUniqueRandomRecords();
#else
        tablicaINT->fillWithRandomRecords(MAX_WARTOSC_KLUCZA);
#endif

    tablicaINT->badanieAlgorytmow();
    delete(tablicaINT);
//------------------------------------------------------------------------------

/******************************************************************************/
#else // CWICZENIE_3
/******************************************************************************/
#if BADANIE_KOPCA
    kopiecINT = new(nothrow) KopiecINT(licznosc);
    if(kopiecINT == nullptr) throw Error(ERR_Object);

#if KLUCZE_UNIKATOWE
        kopiecINT->fillWithUniqueRandomRecords();
#else
        kopiecINT->fillWithRandomRecords(MAX_WARTOSC_KLUCZA);
#endif
    kopiecINT->badanieAlgorytmow();
    delete(kopiecINT);

#elif BADANIE_TURNIEJU
    tablicaINT = new(nothrow) ArrayINT(licznosc);
    if(tablicaINT == nullptr) throw Error(ERR_Object);

#if CIAG_WEJSCIOWY_ROSNACY
	 tablicaINT->fillIncreasing();
#elif CIAG_WEJSCIOWY_MALEJACY
	 tablicaINT->fillDecreasing();
#elif KLUCZE_UNIKATOWE
	 tablicaINT->fillWithUniqueRandomRecords();
#else
	 tablicaINT->fillWithRandomRecords(MAX_WARTOSC_KLUCZA);
#endif

	 tablicaINT->badanieAlgorytmow();
	 delete(tablicaINT);

#elif BADANIE_HUFFMANA
	setByteSize(ROZMIAR_BAJTU);

	huffman = new(nothrow) Huffman(NAZWA_PLIKU);
	if(huffman == nullptr) throw Error(ERR_Object);
	huffman->evaluate();
	huffman->createTree();

	huffman->wypiszNaKonsole();
    HuffmanData::printSizeDiff();
	delete(huffman);

#elif BADANIE_BST
    bstINT = new(nothrow) BstHeadINT(licznosc);
    if(bstINT == nullptr) throw Error(ERR_Object);
	bstINT->fillWithUniqueRandomRecords();
	bstINT->createTree();

	bstINT->testTree();

	delete(bstINT);

#endif
/******************************************************************************/

#endif
    }
    catch(Error& err){
        err.message();
    }
    catch(...){
        Error(ERR_Unknown).message();
    }
};
/******************************************************************************/
