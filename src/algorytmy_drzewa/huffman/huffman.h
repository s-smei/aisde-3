/******************************************************************************/
/******************************************************************************/
/*                               AISDE-Lab                                    */
/******************************************************************************/
    //
    //  Adam Wojtasik
    //
/*  Instytut Mikroelektroniki i Optoelektroniki                               */
/*  Politechnika Warszawska                                                   */
/*  ul. Koszykowa 75                                                          */
/*  00-662 WARSZAWA                                                           */
/*  tel. +48 22 234 72 07                                                     */
/*  www.imio.pw.edu.pl                                                        */
/******************************************************************************/

#ifndef _huffman_h_
#define _huffman_h_
#include <string>

#include "tablica.h"
#include "huffmanData.h"

class Huffman : public Array<HuffmanData>{
    long         dataTableSize;
    HuffmanByte* dataTable;

public:
    Huffman(string);
    ~Huffman(){ delete[] dataTable; }


public:
    void createDataTable(unsigned char*,long);

    void evaluate();
    void createTree();

    void wypiszNaKonsole(bool = false);
};

#endif
