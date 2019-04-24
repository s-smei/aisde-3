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

#ifndef _ERROR_H_
#define _ERROR_H_

#include <iostream>
#include <string>

enum Except{
    ERR_No,
    ERR_Unknown,
    ERR_ByteSize,
    ERR_Text,
    ERR_Stack,
    ERR_Queue,
    ERR_PQ,
    ERR_Memory,
    ERR_Object,
    ERR_File,
    ERR_Data,
    ERR_EmptyStack,
    ERR_NoIndex,
	ERR_LargePrint
};

class Error{
    Except err;
    std::string text;

public:
    Error(Except e) : err(e){ if(e == ERR_Text) text = "unknown error"; }
    Error(const char* txt) : err(ERR_Text), text(txt) {}

    void message(){
        switch(err){
            case ERR_No:         std::cout << "No error"       << std::endl; break;
            case ERR_Unknown:    std::cout << "Unknown error"  << std::endl; break;
            case ERR_Stack:      std::cout << "Stack error"    << std::endl; break;
            case ERR_Queue:      std::cout << "Queue error"    << std::endl; break;
            case ERR_PQ:         std::cout << "PQ error"       << std::endl; break;
            case ERR_Memory:     std::cout << "Memory error"   << std::endl; break;
            case ERR_File:       std::cout << "File error"     << std::endl; break;
            case ERR_Object:     std::cout << "Object error"   << std::endl; break;
            case ERR_Data:       std::cout << "Data error"     << std::endl; break;
			case ERR_EmptyStack: std::cout << "Stack is empty" << std::endl; break;
            case ERR_ByteSize:   std::cout << "Incorrect byte size (Huffman)" << std::endl; break;
            case ERR_NoIndex:    std::cout << "NUMER_INDEKSU is not defined in 'control.h'" << std::endl; break;
			case ERR_LargePrint: std::cout << "Data too large for displaying" << std::endl; break;
            case ERR_Text:       std::cout << text << std::endl; break;
        };
    };
};

#endif
