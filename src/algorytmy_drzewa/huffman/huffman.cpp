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

#include <fstream>
#include <string>
#include <math.h>

using namespace std;

#include "huffman.h"
long HuffmanData::inSize = 0L;
long HuffmanData::outSize = 0L;


//--------------------------------------------------------
void Huffman::evaluate(){
    for(Iterator i = this->firstIndex(); i <= this->lastIndex(); i++) this->array[i].setByte((unsigned int)i);
// zliczanie wystąpień
    for(long i = 0; i < dataTableSize; i++) this->array[dataTable[i].get()]++;

// sortowanie
// 1. przestawianie na poczatek tablicy bajtow, dla ktorych licznosc jest rowna 0
    Iterator iCurr = 0L;
    while(this->array[iCurr].getCount() == 0) iCurr++;
    Iterator iZero = iCurr;
    while(true){
        while(iZero <= this->lastIndex()){
            if(this->array[iZero].getCount() == 0) break;
            iZero++;
        }
        if(iZero > this->lastIndex()) break;
        swap(this->array[iZero], this->array[iCurr]);
        iCurr++;
    }

// 2. sortowanie reszty
    selectionSort(iCurr, lastIndex());
}
//--------------------------------------------------------


//--------------------------------------------------------
void Huffman::createTree(){
    Iterator i = 0;
    while(this->array[i].getCount() == 0) i++;
    i++;
    for(; i <= this->lastIndex(); i++){
        this->array[i] + this->array[i-1];
        insert(i,this->lastIndex());
    }
}
//--------------------------------------------------------


//--------------------------------------------------------
// wczytywanie danych z pliku
Huffman::Huffman(string filename) : Array<HuffmanData>(pow(2,HuffmanByte::getByteSize())-1){
    ifstream file;
    file.open(filename.c_str());
    if(!file.good()) throw Error(ERR_File);

    file.seekg(0, ios::end);
    long textSize = (long)file.tellg();
    unsigned char* text = new(nothrow) unsigned char[textSize];
    if(text == nullptr) throw Error(ERR_Memory);
    file.seekg(0, ios::beg);

    for(long i = 0; i < textSize; i++)text[i] = file.get();
    file.close();

    createDataTable(text,textSize);
    delete[] text;
}

//--------------------------------------------------------
// procedura przepisuje bit po bicie dane z tablicy wejsciowej do tablicy wyjsciowej
// tworzac "bajty" o zadanym rozmiarze bitowym
void Huffman::createDataTable(unsigned char* source,long sizeSource){

    if(HuffmanByte::getByteSize() == HuffmanByte::stdByteSize){
        // proste czytanie danych - bez operacji na bitach, bo dane wyjsciowe maja standardowy rozmiar (8 bitow)
        dataTable = new(nothrow) HuffmanByte[sizeSource];
        if(dataTable == nullptr) throw Error(ERR_Memory);
        dataTableSize = sizeSource;
        for(long i = 0; i < sizeSource; i++) dataTable[i].set(source[i]);
    }
    else{ // dane zamieniane na "bajty" o innych rozmiarach niż 8
        dataTableSize = ((double)HuffmanByte::stdByteSize/(double)HuffmanByte::getByteSize())*(double)sizeSource;
        if((double)dataTableSize < ((double)HuffmanByte::stdByteSize/(double)HuffmanByte::getByteSize())*(double)sizeSource) dataTableSize++;

        dataTable = new(nothrow) HuffmanByte[dataTableSize];
        if(dataTable == nullptr) throw Error(ERR_Memory);

        long currOutByteIndex = 0L;
        HuffmanByte currOutByte;
        int  currPosition = HuffmanByte::getByteSize()-1;

        for(long i = 0; i < sizeSource; i++){
            for(int j = HuffmanByte::stdByteSize-1; j >= 0; j--){
                if((source[i]&(0x01<<j)) != 0) currOutByte.setOneToBit(currPosition);
                if(currPosition == 0){
                    dataTable[currOutByteIndex] = currOutByte;
                    currOutByte.setZero();
                    currOutByteIndex++;
                    currPosition = HuffmanByte::getByteSize()-1;
                }
                else currPosition -= 1;
            }
        }
    }
}
//--------------------------------------------------------


void Huffman::wypiszNaKonsole(bool){
    this->array[this->lastIndex()].display("");
}
