/******************************************************************************/
/*                               AISDE-Lab                                    */
/******************************************************************************/
//  Autor: Adam Wojtasik

/*  Instytut Mikroelektroniki i Optoelektroniki                               */
/*  Politechnika Warszawska                                                   */
/*  ul. Koszykowa 75                                                          */
/*  00-662 WARSZAWA                                                           */
/*  tel. +48 22 234 72 07                                                     */
/*  www.imio.pw.edu.pl                                                        */
/******************************************************************************/

#ifndef _CONTROL_DRZEWA_H_
#define _CONTROL_DRZEWA_H_

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Flagi sterujące algorytmami bazującymi na drzewach binarnych
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===============================================================================
// Flagi wyboru zadania
// UWAGA: w poniższych falgach może być tylko JEDNO tak
#define BADANIE_KOPCA        nie
#define BADANIE_TURNIEJU     nie
#define BADANIE_HUFFMANA     tak
#define BADANIE_BST          nie


//===============================================================================
// Flagi sterujące sortowaniem przez kopcowanie
#define KOPCOWANIE_ZSTEPUJACE   tak   // nie – ukopcowywanie algorytmem wstepującycm
                                      // tak – ukopcowywanie algorytmem zstepującycm

#define KOPCOWANIE_ODWROCENIE   tak   // tak – odwrócenie kolejności w tablicy po sortowaniu przez kopcowanie

#define KOPCOWANIE_POPRAWKA     nie   // tak – poprawka przyspieszająca w sortowaniu z odcinaniem korzenia: odcinanie więcej
                                      //       niż tylko korzenia, jeżeli kolejne rekordy w tablicy mają taką samą co korzeń wartość klucza


//===============================================================================
// Flagi sterujące kompresją z użyciem drzewa Huffmana
#define ROZMIAR_BAJTU   8               // w bitach
#define NAZWA_PLIKU     "hamlet.txt"


//===============================================================================

#endif
